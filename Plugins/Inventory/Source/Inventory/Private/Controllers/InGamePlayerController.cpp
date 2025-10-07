// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/InGamePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interaction/Inv_Highligtable.h"
#include "InventoryManagement/Components/Inv_InventoryComponent.h"
#include "Items/Components/Inv_ItemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/HUD/Inv_HUDWidget.h"


AInGamePlayerController::AInGamePlayerController() :
	InteractionTraceLength(500.f)
{
	PrimaryActorTick.bCanEverTick = true;
	ItemTraceChannel = ECC_GameTraceChannel1;
}

void AInGamePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TraceForItem();
}

void AInGamePlayerController::ToggleInventory()
{
	if (!InventoryComponent.IsValid()) return;
	InventoryComponent->ToggleInventoryMenu();
}

void AInGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (!IsValid(Subsystem)) return;
	
	for (const auto& MappingContext : DefaultIMCs)
	{
		Subsystem->AddMappingContext(MappingContext,0);
	}

	InventoryComponent = FindComponentByClass<UInv_InventoryComponent>();

	CreateHUDWidget();
}

void AInGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(PrimaryInteractAction,ETriggerEvent::Started, this, &ThisClass::OnInteractActionStarted);
		EnhancedInputComponent->BindAction(ToggleInventoryAction,ETriggerEvent::Started, this, &ThisClass::ToggleInventory);
	}
}

void AInGamePlayerController::CreateHUDWidget()
{
	if (!IsLocalController()) return;

	CachedHUDWidget = CreateWidget<UInv_HUDWidget>(this, HUDWidgetClass);
	if (IsValid(CachedHUDWidget))
	{
		CachedHUDWidget->AddToViewport();
	}
}

void AInGamePlayerController::OnInteractActionStarted()
{
	UE_LOG(LogTemp, Warning, TEXT("Interact Triggered."));

	if (!CurrentInteractionTraceHitActor.IsValid()) return;

	UInv_ItemComponent* ItemComp = CurrentInteractionTraceHitActor->FindComponentByClass<UInv_ItemComponent>();
	if (!IsValid(ItemComp)) return;

	InventoryComponent->TryAddItem(ItemComp);
}

void AInGamePlayerController::TraceForItem()
{
	
	if (!IsValid(GEngine) || !IsValid(GEngine->GameViewport)) return;

	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);

	const FVector2D ViewportCenter = ViewportSize / 2.f; // / is overloaded for component-wise division

	FVector TraceStart;
	FVector Forward;
	
	//filling in TraceStart and Forward
	if (!UGameplayStatics::DeprojectScreenToWorld(this, ViewportCenter, TraceStart, Forward)) return;

	const FVector TraceEnd = TraceStart + Forward * InteractionTraceLength;

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ItemTraceChannel);
	
	LastInteractionTraceHitActor = CurrentInteractionTraceHitActor;
	CurrentInteractionTraceHitActor = HitResult.GetActor();

	//if actor became invalid - hide pickup message
	if (!CurrentInteractionTraceHitActor.IsValid())
	{
		if (IsValid(CachedHUDWidget)) CachedHUDWidget->HidePickupMessage();
	}

	//if this actor equals prev actor - do nothing
	if (CurrentInteractionTraceHitActor == LastInteractionTraceHitActor) return;
	
	//we just hit actor we were not tracing prev frame(not the LastInteractionTraceHitActor)
	if (CurrentInteractionTraceHitActor.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Started Tracing new Actor."));

		if (UActorComponent* Highlightable = CurrentInteractionTraceHitActor->FindComponentByInterface(UInv_Highligtable::StaticClass()))
		{
			IInv_Highligtable::Execute_Highlight(Highlightable);
		}
		
		//let's see if this is actually an item that we can pick up (if it has an UInv_ItemComponent)
		UInv_ItemComponent* ItemComponent = CurrentInteractionTraceHitActor->FindComponentByClass<UInv_ItemComponent>();
		if (!IsValid(ItemComponent)) return;

		//show pickup message
		if (IsValid(CachedHUDWidget)) CachedHUDWidget->ShowPickupMessage(ItemComponent->GetPickupMessage());
	}

	//we just stopped tracing prev. object
	if (LastInteractionTraceHitActor.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Stopped Tracing last Actor."));

		if (UActorComponent* Highlightable = LastInteractionTraceHitActor->FindComponentByInterface(UInv_Highligtable::StaticClass()))
		{
			IInv_Highligtable::Execute_UnHighlight(Highlightable);
		}
	}
}

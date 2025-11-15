// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentManagement/Components/Inv_EquipmentComponent.h"

#include "EquipmentManagement/EquipActor/Inv_EquipActor.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "InventoryManagement/Components/Inv_InventoryComponent.h"
#include "InventoryManagement/Utils/Inv_InventoryStatics.h"
#include "Items/Inv_InventoryItem.h"
#include "Items/Fragments/Inv_ItemFragment.h"


void UInv_EquipmentComponent::SetOwningSkeletalMesh(USkeletalMeshComponent* InSkeletalMesh)
{
	OwningSkeletalMesh = InSkeletalMesh;
}

void UInv_EquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
	
	InitPlayerController();
}

void UInv_EquipmentComponent::InitPlayerController()
{
	if (OwningPlayerController = Cast<APlayerController>(GetOwner()); OwningPlayerController.IsValid())
	{
		if (ACharacter* PlayerPawn = Cast<ACharacter>(OwningPlayerController->GetPawn()); IsValid(PlayerPawn))
		{
			OwningSkeletalMesh = PlayerPawn->GetMesh();
			
			InitInventoryComponent();
		}
		else
		{
			OwningPlayerController->OnPossessedPawnChanged.AddDynamic(this, &ThisClass::OnPossessedPawnChange); //this is called in case of multiplayer
		}
	}
}

void UInv_EquipmentComponent::OnPossessedPawnChange(APawn* OldPawn, APawn* NewPawn)
{
	if (ACharacter* PlayerPawn = Cast<ACharacter>(OwningPlayerController->GetPawn()); IsValid(PlayerPawn))
	{
		OwningSkeletalMesh = PlayerPawn->GetMesh();
			
		InitInventoryComponent();
	}
}

void UInv_EquipmentComponent::OnItemEquipped(UInv_InventoryItem* EquippedItem)
{
	if (!IsValid(EquippedItem)) return;

	if (!OwningPlayerController->HasAuthority()) return;

	FInv_ItemManifest& ItemManifest = EquippedItem->GetItemManifestMutable();

	FInv_EquipmentFragment* EquipmentFragment = ItemManifest.GetFragmentOfTypeMutable<FInv_EquipmentFragment>();
	if (!EquipmentFragment) return;

	//First call OnEquip on EquipmentFragment (apply effect)
	EquipmentFragment->OnEquip(OwningPlayerController.Get());

	//Second call SpawnAttachedActor on EquipmentFragment and store SpawnedEquipActor (show visual representation of the equippable in the world)
	if (OwningSkeletalMesh.IsValid())
	{
		AInv_EquipActor* SpawnedEquipActor = SpawnEquipActor(EquipmentFragment, ItemManifest, OwningSkeletalMesh.Get());
		
		EquippedActors.Add(SpawnedEquipActor);
	}
	
}

void UInv_EquipmentComponent::OnItemUnequipped(UInv_InventoryItem* UnequippedItem)
{
	if (!IsValid(UnequippedItem)) return;

	if (!OwningPlayerController->HasAuthority()) return;

	FInv_ItemManifest& ItemManifest = UnequippedItem->GetItemManifestMutable();

	FInv_EquipmentFragment* EquipmentFragment = ItemManifest.GetFragmentOfTypeMutable<FInv_EquipmentFragment>();
	if (!EquipmentFragment) return;

	//First call OnUnequip on EquipmentFragment (remove applied effect)
	EquipmentFragment->OnUnequip(OwningPlayerController.Get());

	//Second call DestroyEquipActor on EquipmentFragment and remove SpawnedEquipActor from the array (remove visual representation of the equippable in the world)
	if (AInv_EquipActor* EquippedActor = FindEquippedActorByTag(EquipmentFragment->GetEquipmentType()); IsValid(EquippedActor))
	{
		EquippedActors.Remove(EquippedActor);
		
		EquippedActor->Destroy();
		
		//EquipmentFragment->DestroyAttachedActor();
	}
}

AInv_EquipActor* UInv_EquipmentComponent::SpawnEquipActor(FInv_EquipmentFragment* EquipmentFragment,
	const FInv_ItemManifest& Manifest, USkeletalMeshComponent* AttachMesh)
{
	AInv_EquipActor* SpawnedEquipActor = EquipmentFragment->SpawnAttachedActor(AttachMesh);
	SpawnedEquipActor->SetEquipmentType(EquipmentFragment->GetEquipmentType());
	SpawnedEquipActor->SetOwner(GetOwner());
	EquipmentFragment->SetEquippedActor(SpawnedEquipActor);

	return SpawnedEquipActor;
}

AInv_EquipActor* UInv_EquipmentComponent::FindEquippedActorByTag(const FGameplayTag& InGameplayTag)
{
	auto* FoundEquipActor = EquippedActors.FindByPredicate([&InGameplayTag](AInv_EquipActor* EquippedActor)
		{
			return EquippedActor->GetEquipmentType().MatchesTagExact(InGameplayTag);
		}
	);
	
	return FoundEquipActor ? *FoundEquipActor : nullptr;
}

void UInv_EquipmentComponent::InitInventoryComponent()
{
	InventoryComponent = UInv_InventoryStatics::GetInventoryComponent(OwningPlayerController.Get());
	if (!InventoryComponent.IsValid()) return;

	//Bind Item Equipped
	if (!InventoryComponent->OnItemEquipped.IsAlreadyBound(this, &ThisClass::OnItemEquipped))
	{
		InventoryComponent->OnItemEquipped.AddDynamic(this, &ThisClass::OnItemEquipped);
	}

	//Bind Item Unequipped
	if (!InventoryComponent->OnItemUnequipped.IsAlreadyBound(this, &ThisClass::OnItemUnequipped))
	{
		InventoryComponent->OnItemUnequipped.AddDynamic(this, &ThisClass::OnItemUnequipped);
	}
}


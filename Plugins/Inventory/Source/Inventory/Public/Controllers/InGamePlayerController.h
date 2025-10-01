// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InGamePlayerController.generated.h"

class UInv_InventoryComponent;
class UInv_HUDWidget;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class INVENTORY_API AInGamePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AInGamePlayerController();
	
	void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ToggleInventory();
	
protected:
	void BeginPlay() override;
	void SetupInputComponent() override;


private:
	void CreateHUDWidget();

	void TraceForItem();
	
	void OnInteractActionStarted();

	TWeakObjectPtr<UInv_InventoryComponent> InventoryComponent;
	
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TArray<TObjectPtr<UInputMappingContext>> DefaultIMCs;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> PrimaryInteractAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> ToggleInventoryAction;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TSubclassOf<UInv_HUDWidget> HUDWidgetClass;

	UPROPERTY(Transient)
	TObjectPtr<UInv_HUDWidget> CachedHUDWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	double InteractionTraceLength;

	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	TEnumAsByte<ECollisionChannel> ItemTraceChannel;

	TWeakObjectPtr<AActor> CurrentInteractionTraceHitActor;
	TWeakObjectPtr<AActor> LastInteractionTraceHitActor;
};

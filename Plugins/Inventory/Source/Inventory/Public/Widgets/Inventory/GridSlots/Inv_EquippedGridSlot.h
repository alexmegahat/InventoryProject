// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Inv_GridSlot.h"
#include "Inv_EquippedGridSlot.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEquippedGridSlotClicked, UInv_EquippedGridSlot*, GridSlot, const FGameplayTag&, EquipmentTypeTag);

/**
 * Special class for handling character equipment.
 */
UCLASS()
class INVENTORY_API UInv_EquippedGridSlot : public UInv_GridSlot
{
	GENERATED_BODY()

public:
	//~Begin UInv_GridSlot Interface
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	//~End UInv_GridSlot Interface

	FOnEquippedGridSlotClicked OnEquippedGridSlotClicked;

	FGameplayTag& GetEquipmentTypeTag() { return EquipmentTypeTag; }

private:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	FGameplayTag EquipmentTypeTag;
};

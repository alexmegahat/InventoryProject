// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inv_SlottedItem.h"
#include "GameplayTagContainer.h"
#include "Inv_EquippedSlottedItem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquippedSlottedItemClicked, UInv_EquippedSlottedItem*, EquippedSlottedItem);

/**
 *  Equipped Slotted Item class
 */
UCLASS()
class INVENTORY_API UInv_EquippedSlottedItem : public UInv_SlottedItem
{
	GENERATED_BODY()
public:
	void SetEquipmentTypeTag(const FGameplayTag& InEquipmentTypeTag) { EquipmentTypeTag = InEquipmentTypeTag; };
	FGameplayTag GetEquipmentTypeTag() const { return EquipmentTypeTag; };

	//~Begin UUserWidget Interface
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	//~End UUserWidget Interface

	FOnEquippedSlottedItemClicked OnEquippedSlottedItemClicked;
	
private:
	UPROPERTY()
	FGameplayTag EquipmentTypeTag;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Inventory/GridSlots/Inv_EquippedGridSlot.h"

#include "InventoryManagement/Utils/Inv_InventoryStatics.h"
#include "Widgets/Inventory/HoverItem/Inv_HoverItem.h"

void UInv_EquippedGridSlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (!GetbIsAvailable()) return;
	
	if (UInv_HoverItem* HoverItem = UInv_InventoryStatics::GetHoverItem(GetOwningPlayer()); IsValid(HoverItem))
	{
		// check for a partial match with the EquipmentTypeTag
		// because more specific tag (like item type tag) checking against a more broad tag (like EquipmentTypeTag) will return true.
		if (HoverItem->GetItemType().MatchesTag(EquipmentTypeTag))
		{
			SetGridSlotState(EInv_GridSlotState::Occupied);
		}
	}
}

void UInv_EquippedGridSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	if (!GetbIsAvailable()) return;
	
	if (UInv_HoverItem* HoverItem = UInv_InventoryStatics::GetHoverItem(GetOwningPlayer()); IsValid(HoverItem))
	{
		// check for a partial match with the EquipmentTypeTag
		// because more specific tag (like item type tag) checking against a more broad tag (like EquipmentTypeTag) will return true.
		if (HoverItem->GetItemType().MatchesTag(EquipmentTypeTag))
		{
			SetGridSlotState(EInv_GridSlotState::Unoccupied);
		}
	}
}

FReply UInv_EquippedGridSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	OnEquippedGridSlotClicked.Broadcast(this, EquipmentTypeTag);
	return FReply::Handled();
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Inventory/GridSlots/Inv_GridSlot.h"
#include "Items/Inv_InventoryItem.h"
#include "IAutomationReport.h"
#include "Components/Image.h"

void UInv_GridSlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	OnGridSlotHovered.Broadcast(TileIndex, InMouseEvent);
}

void UInv_GridSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	OnGridSlotUnhovered.Broadcast(TileIndex, InMouseEvent);
}

FReply UInv_GridSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	OnGridSlotClicked.Broadcast(TileIndex, InMouseEvent);
	
	return FReply::Handled();
}

void UInv_GridSlot::SetGridSlotState(const EInv_GridSlotState InNewState)
{
	GridSlotState = InNewState;

	if (const FSlateBrush* Brush = StateBrushes.Find(InNewState))
	{
		Image_GridSlot->SetBrush(*Brush);
	}
	else
	{
		ensureMsgf(false, TEXT("Missing brush for %s"),
		  *UEnum::GetValueAsString(InNewState));
	}
}

void UInv_GridSlot::SetInventoryItem(UInv_InventoryItem* Item)
{
	InventoryItem = Item;
}

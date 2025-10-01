// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Inventory/Spacial/Inv_InventoryGrid.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Widgets/Inventory/GridSlots/Inv_GridSlot.h"
#include "Widgets/Utils/Inv_WidgetUtils.h"

void UInv_InventoryGrid::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ConstructGrid();
}

void UInv_InventoryGrid::ConstructGrid()
{
	//determine the array size right from the start (performance)
	GridSlots.Reserve(Rows * Columns);

	for (int32 j = 0; j<Rows; ++j)
	{
		for (int32 i = 0; i<Columns; ++i)
		{
			UInv_GridSlot* GridSlot = CreateWidget<UInv_GridSlot>(this, GridSlotClass);
			
			CanvasPanel->AddChildToCanvas(GridSlot);

			//get index in the array, corresponding to 2D coords i and j
			const FIntPoint Pos = FIntPoint(i, j);
			int32 Index = UInv_WidgetUtils::GetIndexFromPosition(Pos, Columns);
			GridSlot->SetTileIndex(Index);

			UCanvasPanelSlot* GridCanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(GridSlot);
			GridCanvasPanelSlot->SetSize(FVector2D(TileSize));
			GridCanvasPanelSlot->SetPosition(Pos * TileSize);

			GridSlots.Add(GridSlot);
		}
	}
}

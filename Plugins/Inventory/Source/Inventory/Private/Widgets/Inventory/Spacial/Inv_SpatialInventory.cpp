// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Inventory/Spacial/Inv_SpatialInventory.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Widgets/Inventory/Spacial/Inv_InventoryGrid.h"

void UInv_SpatialInventory::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Button_Equippables->OnClicked.AddDynamic(this, &ThisClass::ShowEquippables);
	
	Button_Craftables->OnClicked.AddDynamic(this, &ThisClass::ShowCraftables);

	Button_Consumables->OnClicked.AddDynamic(this, &ThisClass::ShowConsumables);
	
	ShowEquippables();
}

void UInv_SpatialInventory::ShowEquippables()
{
	SetActiveGrid(Grid_Equippables, Button_Equippables);
}

void UInv_SpatialInventory::ShowCraftables()
{
	SetActiveGrid(Grid_Craftables, Button_Craftables);
}

void UInv_SpatialInventory::ShowConsumables()
{
	SetActiveGrid(Grid_Consumables, Button_Consumables);
}

void UInv_SpatialInventory::SetActiveGrid(UInv_InventoryGrid* Grid, UButton* DisableButton)
{
	Button_Equippables->SetIsEnabled(true);
	Button_Craftables->SetIsEnabled(true);
	Button_Consumables->SetIsEnabled(true);
	DisableButton->SetIsEnabled(false);

	Switcher->SetActiveWidget(Grid);
}

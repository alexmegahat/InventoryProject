// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inv_GridSlot.generated.h"

class UImage;

UENUM(BlueprintType)
enum class EInv_GridSlotState : uint8
{
	Unoccupied,
	Occupied,
	Selected,
	GrayedOut
};

/**
 * 
 */
UCLASS()
class INVENTORY_API UInv_GridSlot : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetTileIndex(int32 InNewIndex) {TileIndex = InNewIndex;}
	int32 GetTileIndex() const {return TileIndex;}

	EInv_GridSlotState GetGridSlotState() const { return GridSlotState; };
	void SetGridSlotState(const EInv_GridSlotState InNewState);

private:
	int32 TileIndex;
	
	//******* Bound Widgets *******//
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_GridSlot;

	
	//******* Bound Widgets *******//

	UPROPERTY(EditDefaultsOnly, Category="Style")
	TMap<EInv_GridSlotState, FSlateBrush> StateBrushes;
	
	//current grid slot state
	EInv_GridSlotState GridSlotState;
	
};

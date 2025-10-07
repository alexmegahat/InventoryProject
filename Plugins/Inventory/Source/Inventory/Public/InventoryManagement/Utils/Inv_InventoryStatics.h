// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Widgets/Utils/Inv_WidgetUtils.h"
#include "Inv_InventoryStatics.generated.h"

class UInv_ItemComponent;
enum class EInv_ItemCategory : uint8;
class UInv_InventoryComponent;
/**
 * 
 */
UCLASS()
class INVENTORY_API UInv_InventoryStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	static UInv_InventoryComponent* GetInventoryComponent(const APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	static EInv_ItemCategory GetItemCategoryFromItemComponent(const UInv_ItemComponent* ItemComponent);

	//T - array's type, FuncT - function
	template<typename T, typename FuncT>
	static void ForEach2D(TArray<T>& Array, int32 Index, const FIntPoint& Range2D, int32 GridColumns, const FuncT& Function);
};

template<typename T, typename FuncT>
void UInv_InventoryStatics::ForEach2D(TArray<T>& Array, int32 Index, const FIntPoint& Range2D, int32 GridColumns, const FuncT& Function)
{
	//iterate over the item height
	for (int32 j = 0; j<Range2D.Y; ++j)
	{
		//iterate over the item width
		for (int32 i = 0; i<Range2D.X; ++i)
		{
			//get position for the index
			const FIntPoint Coords = UInv_WidgetUtils::GetPositionFromIndex(Index, GridColumns) + FIntPoint(i, j);
			
			const int32 TileIndex = UInv_WidgetUtils::GetIndexFromPosition(Coords, GridColumns);

			if (Array.IsValidIndex(TileIndex))
			{
				Function(Array[TileIndex]);
			}
		}
	}
}
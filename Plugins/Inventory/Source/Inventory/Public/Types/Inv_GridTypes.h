#pragma once

#include "Inv_GridTypes.generated.h"

class UInv_InventoryItem;

UENUM(BlueprintType)
enum class EInv_ItemCategory : uint8
{
	Equippable,
	Consumable,
	Craftable,
	None
};

USTRUCT()
struct FInv_SlotAvailability
{
	GENERATED_BODY()

	FInv_SlotAvailability(){}
	FInv_SlotAvailability(const int32 ItemIndex, const int32 Room, const bool bHasItem) : Index(ItemIndex), AmountToFill(Room), bItemAtIndex(bHasItem) {}

	int32 Index{INDEX_NONE}; //what index are we putting an item in
	int32 AmountToFill{0}; //how much of that item are we filling in
	bool bItemAtIndex{false}; //is there already an item there
};

USTRUCT()
struct FInv_SlotAvailabilityResult
{
	GENERATED_BODY()
	FInv_SlotAvailabilityResult(){}

	TWeakObjectPtr<UInv_InventoryItem> Item; //is there an item of this type already in the inventory
	int32 TotalRoomToFill{0}; //how much of this item we can fit
	int32 Remainder{0}; //how much we can't fit
	bool bStackable{false}; //is the item stackable
	
	TArray<FInv_SlotAvailability> SlotAvailabilities;
};
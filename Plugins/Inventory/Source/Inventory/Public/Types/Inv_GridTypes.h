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

/*
 * This enum lets us categorize the quadrant of the grid slot,
 * we use this information later to determine things like what squares should we highlight
 * when dragging an item over to a different position.
 */
UENUM(BlueprintType)
enum class EInv_TileQuadrant : uint8
{
	TopLeft,
	TopRight,
	BottomLeft,
	BottomRight,
	None
};

/*
 * Allows us to store parameters for any given frame
 */
USTRUCT(BlueprintType)
struct FInv_TileParameters
{
	GENERATED_BODY()

	//where on the grid are we from a coords perspective
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FIntPoint TileCoordinates;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 TileIndex = INDEX_NONE;
	
	//where we are within the particular grid slot
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	EInv_TileQuadrant TileQuadrant = EInv_TileQuadrant::None;

};


inline bool operator==(const FInv_TileParameters& A, const FInv_TileParameters& B)
{
	return A.TileCoordinates == B.TileCoordinates && A.TileIndex == B.TileIndex && A.TileQuadrant == B.TileQuadrant;
}

USTRUCT()
struct FInv_SpaceQueryResult
{
	GENERATED_BODY()

	// True if space queried has no items in it
	bool bHasSpace{false};

	// Valid if there is a single item we can swap with
	TWeakObjectPtr<UInv_InventoryItem> ValidItem = nullptr;
	
	// Upper left index of the single valid item, if there is one
	int32 UpperLeftIndex{INDEX_NONE};
};

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Inv_FragmentTags.h"
#include "Inv_ItemFragment.generated.h"

class UInv_CompositeBase;
class APlayerController;

/*
* Base Item Fragment (scroll down to see children)
*/
USTRUCT(BlueprintType)
struct FInv_ItemFragment
{
	GENERATED_BODY()

	FInv_ItemFragment() {}

	/*
	 * The only reason why there is a destructor, is because we need to be able to derive children from this struct,
	 * and since we're adding a destructor, we need to add all 5 special member functions, including destructor and all the listed below,
	 * to be precise about the implementation (but we're also defaulting 4 of them to the default behaviour).
	 */

	virtual ~FInv_ItemFragment() {}

	//copy-constructor
	FInv_ItemFragment(const FInv_ItemFragment&) = default;

	//copy assignment operator
	FInv_ItemFragment& operator=(const FInv_ItemFragment&) = default;

	//move constructor
	FInv_ItemFragment(FInv_ItemFragment&&) = default;

	//move assignment operator
	FInv_ItemFragment& operator=(FInv_ItemFragment&&) = default;

	
	FGameplayTag GetFragmentTag() const { return FragmentTag; }
	
protected:
	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (Categories = "FragmentTags")) //Categories specify the "FragmentTags" tag
	FGameplayTag FragmentTag;
	
};

/*
* Inventory Item Fragment (Responsible for the description widget showing the info of the item - so specifically for assimilation into a widget.)
*/
USTRUCT(BlueprintType)
struct FInv_InventoryItemFragment : public FInv_ItemFragment
{
	GENERATED_BODY()
public:
	virtual void Assimilate(UInv_CompositeBase* Composite) const;

protected:
	bool MatchesWidgetTag(const UInv_CompositeBase* Composite) const;
};


/*
* Grid Item Fragment (mainly responsible for the size being taken by the item in the inventory)
*/
USTRUCT(BlueprintType)
struct FInv_GridFragment :public FInv_ItemFragment
{
	GENERATED_BODY()
	
public:
	//default constructor for this fragment (setting up tag, but can be done in bp as well)
	FInv_GridFragment() { FragmentTag = FragmentTags::GridFragment; }
	
	FIntPoint GetGridSize() const { return GridSize; }
	void SetGridSize(const FIntPoint& NewGridSize) { GridSize = NewGridSize; }
	float GetGridPadding() const { return GridPadding; }
	void SetGridPadding(const float NewGridPadding) { GridPadding = NewGridPadding; }

private:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	FIntPoint GridSize{1,1};

private:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	float GridPadding{0.f};
};

/*
* Image Item Fragment (for any image icon we need)
*/
USTRUCT(BlueprintType)
struct FInv_ImageFragment : public FInv_ItemFragment
{
	GENERATED_BODY()
public:
	//default constructor for this fragment (setting up tag, but can be done in bp as well)
	FInv_ImageFragment() { FragmentTag = FragmentTags::IconFragment; }
	
	UTexture2D* GetIcon() const { return Icon; }
	
private:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TObjectPtr<UTexture2D> Icon{nullptr};
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	FVector2D IconSize{44.f,44.f};
	
};

/*
* Stackable Item Fragment
*/
USTRUCT(BlueprintType)
struct FInv_StackableFragment : public FInv_ItemFragment
{
	GENERATED_BODY()
public:
	//default constructor for this fragment (setting up tag, but can be done in bp as well)
	FInv_StackableFragment() { FragmentTag = FragmentTags::StackableFragment; }
	
	int32 GetMaxStackSize() const { return MaxStackSize; }
	int32 GetStackCount() const { return StackCount; }

	void SetStackCount(const int32 NewStackCount) { StackCount = NewStackCount; }
	
private:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 MaxStackSize{1};

	//currently more like item count?
	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 StackCount{1};
	
};

/*
* Base Consumable Item Fragment
*/
USTRUCT(BlueprintType)
struct FInv_ConsumableFragment : public FInv_ItemFragment
{
	GENERATED_BODY()
public:
	FInv_ConsumableFragment() { FragmentTag = FragmentTags::ConsumableFragment; };

	virtual void OnConsume(APlayerController* PC) {};
};

USTRUCT(BlueprintType)
struct FInv_HealthPotion : public FInv_ConsumableFragment
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	float HealAmount = 20.f;
	
	virtual void OnConsume(APlayerController* PC) override;
};

USTRUCT(BlueprintType)
struct FInv_ManaPotion : public FInv_ConsumableFragment
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	float ManaAmount = 20.f;
	
	virtual void OnConsume(APlayerController* PC) override;
};
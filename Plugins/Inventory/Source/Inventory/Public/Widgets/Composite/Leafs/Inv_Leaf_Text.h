// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Composite/Inv_Leaf.h"
#include "Inv_Leaf_Text.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class INVENTORY_API UInv_Leaf_Text : public UInv_Leaf
{
	GENERATED_BODY()
public:

	//~Begin UUserWidget Interface
	virtual void NativePreConstruct() override;
	//~End UUserWidget Interface
	
	void SetText(const FText& NewText);
	
private:
	//******* Bound Widgets *******//
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_LeafText;
	//******* Bound Widgets *******//

	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 FontSize = 12;
};

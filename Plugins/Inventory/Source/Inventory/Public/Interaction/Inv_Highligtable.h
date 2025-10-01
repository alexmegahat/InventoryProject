// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Inv_Highligtable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UInv_Highligtable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INVENTORY_API IInv_Highligtable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
	void Highlight();
	
	UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
	void UnHighlight();
};

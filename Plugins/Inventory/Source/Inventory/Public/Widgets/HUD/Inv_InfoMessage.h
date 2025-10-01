// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inv_InfoMessage.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class INVENTORY_API UInv_InfoMessage : public UUserWidget
{
	GENERATED_BODY()
public:
	//~Begin UUserWidget Interface
	virtual void NativeOnInitialized() override;
	//~End UUserWidget Interface
	
	void ShowMessage(const FText& MessageToShow);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Inventory")
	void ShowTextBlock();

	UFUNCTION(BlueprintImplementableEvent, Category = "Inventory")
	void HideTextBlock();
private:
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_Message;

	UPROPERTY(EditAnywhere)
	float MessageLifetime = 3.f;

	FTimerHandle MessageTimer;
	bool bIsMessageActive = false;
};

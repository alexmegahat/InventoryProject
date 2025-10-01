// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/HUD/Inv_InfoMessage.h"
#include "Components/TextBlock.h"

void UInv_InfoMessage::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Text_Message->SetText(FText::GetEmpty());
	HideTextBlock();
}

void UInv_InfoMessage::ShowMessage(const FText& MessageToShow)
{
	Text_Message->SetText(MessageToShow);
	
	if (!bIsMessageActive)
	{
		ShowTextBlock();
	}
	bIsMessageActive = true;

	GetWorld()->GetTimerManager().SetTimer(MessageTimer,
	[this]()
	{
		HideTextBlock();
		bIsMessageActive = false;
	},
	MessageLifetime,
	false
	);
		
}


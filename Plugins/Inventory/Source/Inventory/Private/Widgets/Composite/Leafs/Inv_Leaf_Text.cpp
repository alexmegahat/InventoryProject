// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Composite/Leafs/Inv_Leaf_Text.h"
#include "Components/TextBlock.h"

void UInv_Leaf_Text::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	FSlateFontInfo FontInfo = TextBlock_LeafText->GetFont();
	FontInfo.Size = FontSize;
	TextBlock_LeafText->SetFont(FontInfo);
}

void UInv_Leaf_Text::SetText(const FText& NewText)
{
	TextBlock_LeafText->SetText(NewText);
}

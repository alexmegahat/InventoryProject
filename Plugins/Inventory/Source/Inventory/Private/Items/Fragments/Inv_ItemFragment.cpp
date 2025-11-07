
#include "Items/Fragments/Inv_ItemFragment.h"

void FInv_HealthPotion::OnConsume(APlayerController* PC)
{
	//Get stats comp from the PC or the PC->GetPawn()
	//or get Ability System Component and apply a Gameplay Effect
	//or call an interface func for healing

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Health potion consumed! Healing %f Player HP."), HealAmount));
}

void FInv_ManaPotion::OnConsume(APlayerController* PC)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Mana potion consumed! Mana replenished by %f."), ManaAmount));
}

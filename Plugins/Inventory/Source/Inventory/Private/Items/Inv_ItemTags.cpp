
#include "Items/Inv_ItemTags.h"

//GameItems::Equipment::Weapons::Axe - access tag

namespace GameItems
{
	namespace Equipment
	{
		namespace Weapons
		{
			UE_DEFINE_GAMEPLAY_TAG(Axe, "GameItems.Equipment.Weapons.Axe")
			UE_DEFINE_GAMEPLAY_TAG(Sword, "GameItems.Equipment.Weapons.Sword")
		}
		namespace Head
		{
			
		}
		namespace Face
		{
			UE_DEFINE_GAMEPLAY_TAG(SteelMask, "GameItems.Equipment.Head.SteelMask")
		}
		namespace Chest
		{
			
		}
		namespace Legs
		{
			
		}
		namespace Foot
		{
			
		}
		namespace Cloaks
		{
			UE_DEFINE_GAMEPLAY_TAG(RedCloak, "GameItems.Equipment.Cloaks.RedCloak")
		}
		namespace Special
		{
			
		}
	}

	namespace Consumables
	{
		namespace Potions
		{
			namespace Health
			{
				UE_DEFINE_GAMEPLAY_TAG(Small, "GameItems.Consumables.Potions.Health.Small")
				UE_DEFINE_GAMEPLAY_TAG(Medium, "GameItems.Consumables.Potions.Health.Medium")
			}
			namespace Stamina
			{
				UE_DEFINE_GAMEPLAY_TAG(Small, "GameItems.Consumables.Potions.Stamina.Small")
				UE_DEFINE_GAMEPLAY_TAG(Medium, "GameItems.Consumables.Potions.Stamina.Medium")
			}
		}
	}
	
	namespace Craftables
	{
		UE_DEFINE_GAMEPLAY_TAG(FireFernFruit, "GameItems.Craftables.FireFernFruit")
		UE_DEFINE_GAMEPLAY_TAG(LuminDaisy, "GameItems.Craftables.LuminDaisy")
		UE_DEFINE_GAMEPLAY_TAG(ScorchPetalBlossom, "GameItems.Craftables.ScorchPetalBlossom")
	}
}


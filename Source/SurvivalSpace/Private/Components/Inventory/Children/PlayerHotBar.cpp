// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.


#include "Components/Inventory/Children/PlayerHotBar.h"

#include "Character/ASurvivalCharacter.h"
#include "DataAssets/PrimaryAssets/ItemInfo.h"

void UPlayerHotBar::CheckHotBar(int32 Index, bool& HasItemInSlot, EItemType& ItemType)
{
	if (Items[Index].ItemID == 0)
	{
		HasItemInSlot = false;
	}
	else
	{
		HasItemInSlot = true;

		// Check if the soft object path is valid
		if (Items[Index].ItemAsset.ToSoftObjectPath().IsValid())
		{
			// Load the item asset if the path is valid
			UItemInfo* LoadedAsset = Items[Index].ItemAsset.LoadSynchronous();
			if (LoadedAsset)
			{
				ItemType = LoadedAsset->ItemType;
			}
			else
			{
				// Handle the case where the asset failed to load
			}
		}
		else
		{
			// Handle the case where the path is invalid
		}
	}
}

void UPlayerHotBar::HandleSlotDrop(UItemsContainerMaster* FromContainer, int32 FromIndex, int32 DropIndex)
{
    UItemsContainerMaster* LocalFromContainer = FromContainer;
    int32 LocalFromIndex = FromIndex;
    int32 LocalDropIndex = DropIndex;

	
    if (LocalFromContainer == this && LocalFromIndex == LocalDropIndex)
    {
        // DO NOTHING
    }
    else
    {
        switch (LocalFromContainer->ContainerType) {
        case EContainerType::Inventory:
            LocalFromContainer->TransferItem(this, LocalDropIndex, LocalFromIndex);
            break;
        case EContainerType::HotBar:
            LocalFromContainer->TransferItem(this, LocalDropIndex, LocalFromIndex);
            break;
        case EContainerType::Storage:
            break;
        case EContainerType::Armor:
            break;
case EContainerType::Crafting:
	break;
        }
    }
}



void UPlayerHotBar::AddItemToIndex(FItemStructure ItemInfo, int32 LocalSpecificIndex, int32 LocalItemIndex, bool& Success)
{
	Super::AddItemToIndex(ItemInfo, LocalSpecificIndex, LocalItemIndex, Success);
	
	// GetOwner returns a pointer to the owning character
	if (AASurvivalCharacter* SurvivalCharacter = Cast<AASurvivalCharacter>(GetOwner()))
	{
		// Check if the character implements the ISurvivalCharacterInterface
		ISurvivalCharacterInterface* CharacterInterface = Cast<ISurvivalCharacterInterface>(SurvivalCharacter);
		if (CharacterInterface)
		{
			FItemStructure SpecificItemInfo;
			GetItemAtIndex(LocalSpecificIndex, SpecificItemInfo);
			CharacterInterface->UpdateItem(ContainerType, LocalSpecificIndex, SpecificItemInfo);
			CharacterInterface->UpdateCraftItem(ContainerType, LocalSpecificIndex, SpecificItemInfo);
		}
	}
}



void UPlayerHotBar::RemoveItemAtIndex(int32 Index, bool& Success)
{
	Super::RemoveItemAtIndex(Index, Success);

	// GetOwner returns a pointer to the owning character
	if (AASurvivalCharacter* SurvivalCharacter = Cast<AASurvivalCharacter>(GetOwner()))
	{
		// Check if the character implements the ISurvivalCharacterInterface
		ISurvivalCharacterInterface* CharacterInterface = Cast<ISurvivalCharacterInterface>(SurvivalCharacter);
		if (CharacterInterface)
		{
			CharacterInterface->ResetItem(ContainerType, Index);
		}
	}
}



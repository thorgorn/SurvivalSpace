// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.


#include "Components/Inventory/Children/PlayerHotBar.h"

#include "Character/ASurvivalCharacter.h"
#include "DataAssets/PrimaryAssets/ItemInfo.h"

void UPlayerHotBar::CheckHotBar(int32 Index, bool& HasItemInSlot, EItemType& ItemType)
{
	if (GetItems()[Index].ItemID == 0)
	{
		HasItemInSlot = false;
	}
	else
	{
		HasItemInSlot = true;
		
		if (GetItems()[Index].ItemAsset.ToSoftObjectPath().IsValid())
		{
			UItemInfo* LoadedAsset = GetItems()[Index].ItemAsset.LoadSynchronous();
			if (LoadedAsset)
			{
				ItemType = LoadedAsset->ItemType;
			}
		}
	}
}

void UPlayerHotBar::HandleSlotDrop(UItemsContainerMaster* FromContainer, int32 FromIndex, int32 DropIndex)
{
    //TObjectPtr<UItemsContainerMaster> LocalFromContainer = FromContainer;
    //int32 LocalFromIndex = FromIndex;
    //int32 LocalDropIndex = DropIndex;
	
    if (FromContainer == this && FromIndex == DropIndex)
    {
        // DO NOTHING
    }
    else
    {
        switch (FromContainer->GetContainerType()) {
        case EContainerType::Inventory:
            FromContainer->TransferItem(this, DropIndex, FromIndex);
            break;
        case EContainerType::HotBar:
            FromContainer->TransferItem(this, DropIndex, FromIndex);
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
	
	if (AASurvivalCharacter* SurvivalCharacter = Cast<AASurvivalCharacter>(GetOwner()))
	{
		ISurvivalCharacterInterface* CharacterInterface = Cast<ISurvivalCharacterInterface>(SurvivalCharacter);
		if (CharacterInterface)
		{
			FItemStructure SpecificItemInfo;
			
			GetItemAtIndex(LocalSpecificIndex, SpecificItemInfo);
			
			CharacterInterface->UpdateItem(GetContainerType(), LocalSpecificIndex, SpecificItemInfo);
			
			CharacterInterface->UpdateCraftItem(GetContainerType(), LocalSpecificIndex, SpecificItemInfo);
		}
	}
}



void UPlayerHotBar::RemoveItemAtIndex(int32 Index, bool& Success)
{
	Super::RemoveItemAtIndex(Index, Success);
	
	if (AASurvivalCharacter* SurvivalCharacter = Cast<AASurvivalCharacter>(GetOwner()))
	{
		ISurvivalCharacterInterface* CharacterInterface = Cast<ISurvivalCharacterInterface>(SurvivalCharacter);
		if (CharacterInterface)
		{
			CharacterInterface->ResetItem(GetContainerType(), Index);
		}
	}
}



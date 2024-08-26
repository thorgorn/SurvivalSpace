// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Inventory/Children/PlayerInventory.h"

#include "Character/ASurvivalCharacter.h"

void UPlayerInventory::HandleSlotDrop(UItemsContainerMaster* FromContainer, int32 FromIndex, int32 DropIndex)
{
	
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

void UPlayerInventory::AddItemToIndex(FItemStructure ItemInfo, int32 LocalSpecificIndex, int32 LocalItemIndex,
	bool& Success)
{
	Super::AddItemToIndex(ItemInfo, LocalSpecificIndex, LocalItemIndex, Success);
	
	if (ISurvivalCharacterInterface* CharacterInterface = Cast<ISurvivalCharacterInterface>(GetOwner()))
	{
		TObjectPtr<AASurvivalCharacter> SurvivalCharacter = nullptr;
		
		CharacterInterface->GetCharRef(SurvivalCharacter);

		if (SurvivalCharacter)
		{
			FItemStructure SpecificItemInfo;
			
			GetItemAtIndex(LocalSpecificIndex, SpecificItemInfo);
			
			CharacterInterface->UpdateItem(GetContainerType(), LocalSpecificIndex, SpecificItemInfo);
		}
	}
}

void UPlayerInventory::RemoveItemAtIndex(int32 Index, bool& Success)
{
	Super::RemoveItemAtIndex(Index, Success);
	
	if (ISurvivalCharacterInterface* CharacterInterface = Cast<ISurvivalCharacterInterface>(GetOwner()))
	{
		TObjectPtr<AASurvivalCharacter> SurvivalCharacter = nullptr;
		
		CharacterInterface->GetCharRef(SurvivalCharacter);

		if (SurvivalCharacter)
		{
			CharacterInterface->ResetItem(GetContainerType(), Index);
		}
	}
}

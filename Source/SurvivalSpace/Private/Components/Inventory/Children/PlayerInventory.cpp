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

bool UPlayerInventory::AddItemToIndex(const FItemStructure& ItemInfo, int32 TargetIndex,
	int32 FromIndex)
{
	const bool& bIsSuccessful = Super::AddItemToIndex(ItemInfo, TargetIndex, FromIndex);
	
	if (ISurvivalCharacterInterface* CharacterInterface = Cast<ISurvivalCharacterInterface>(GetOwner()))
	{
		TObjectPtr<AASurvivalCharacter> SurvivalCharacter = nullptr;
		
		CharacterInterface->GetCharRef(SurvivalCharacter);

		if (SurvivalCharacter)
		{
			FItemStructure SpecificItemInfo = GetItemAtIndex(TargetIndex);
			
			CharacterInterface->UpdateItem(GetContainerType(), TargetIndex, SpecificItemInfo);
			return bIsSuccessful;
		}
	}
	return false;
}

bool UPlayerInventory::RemoveItemAtIndex(const int32 Index)
{
	const bool& bIsSuccessful = Super::RemoveItemAtIndex(Index);
	
	if (ISurvivalCharacterInterface* CharacterInterface = Cast<ISurvivalCharacterInterface>(GetOwner()))
	{
		TObjectPtr<AASurvivalCharacter> SurvivalCharacter = nullptr;
		
		CharacterInterface->GetCharRef(SurvivalCharacter);

		if (SurvivalCharacter)
		{
			CharacterInterface->ResetItem(GetContainerType(), Index);
			return bIsSuccessful;
		}
	}
	return false;
}

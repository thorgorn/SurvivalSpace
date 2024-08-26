// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Inventory/Children/PlayerInventory.h"

#include "Character/ASurvivalCharacter.h"

void UPlayerInventory::HandleSlotDrop(UItemsContainerMaster* FromContainer, int32 FromIndex, int32 DropIndex)
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

void UPlayerInventory::AddItemToIndex(FItemStructure ItemInfo, int32 LocalSpecificIndex, int32 LocalItemIndex,
	bool& Success)
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
		}
	}
}

void UPlayerInventory::RemoveItemAtIndex(int32 Index, bool& Success)
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

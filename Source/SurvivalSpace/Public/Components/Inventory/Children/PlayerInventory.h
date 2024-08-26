// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Inventory/ItemsContainerMaster.h"
#include "PlayerInventory.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALSPACE_API UPlayerInventory : public UItemsContainerMaster
{
	GENERATED_BODY()

protected:

	//--------------------------------------------------------------------------------------------
	// PLAYER INVENTORY FUNCTIONS
	//--------------------------------------------------------------------------------------------

	virtual void HandleSlotDrop(UItemsContainerMaster* FromContainer, int32 FromIndex, int32 DropIndex) override;

	virtual void AddItemToIndex(FItemStructure ItemInfo, int32 LocalSpecificIndex, int32 LocalItemIndex, bool& Success) override;

	virtual void RemoveItemAtIndex(int32 Index, bool& Success) override;
};
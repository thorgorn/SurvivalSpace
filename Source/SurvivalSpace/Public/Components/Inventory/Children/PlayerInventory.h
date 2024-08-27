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

	virtual bool AddItemToIndex(const FItemStructure& ItemInfo, int32 TargetIndex,
	int32 FromIndex) override;

	virtual bool RemoveItemAtIndex(const int32 Index) override;
};
// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.

#pragma once

#include "CoreMinimal.h"
#include "Components/Inventory/ItemsContainerMaster.h"
#include "PlayerHotBar.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALSPACE_API UPlayerHotBar : public UItemsContainerMaster
{
	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------------------------
	// PLAYER HOTBAR FUNCTIONS
	//--------------------------------------------------------------------------------------------

	UFUNCTION(BlueprintCallable, Category = "HotBar Functions")
	void CheckHotBar(int32 Index, bool& HasItemInSlot, EItemType& ItemType);

	virtual void HandleSlotDrop(UItemsContainerMaster* FromContainer, int32 FromIndex, int32 DropIndex) override;

	virtual void AddItemToIndex(FItemStructure ItemInfo, int32 LocalSpecificIndex, int32 LocalItemIndex, bool& Success) override;

	virtual void RemoveItemAtIndex(int32 Index, bool& Success) override;
};
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

	virtual bool AddItemToIndex(const FItemStructure& ItemInfo, int32 TargetIndex,
	int32 FromIndex) override;

	virtual bool RemoveItemAtIndex(const int32 Index) override;
};
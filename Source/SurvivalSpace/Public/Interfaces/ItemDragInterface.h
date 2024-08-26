// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.

#pragma once

#include "CoreMinimal.h"
#include "Enums/Enums.h"
#include "UObject/Interface.h"
#include "ItemDragInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable)
class UItemDragInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SURVIVALSPACE_API IItemDragInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable)
	virtual void GetItemDragInfo(int32 &OutSlotIndex, EContainerType &OutFromContainer, EArmorType &OutArmorType, EItemType &OutItemType);
};

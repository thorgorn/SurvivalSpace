// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "Enums/Enums.h"
#include "Interfaces/ItemDragInterface.h"
#include "ItemDrag.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALSPACE_API UItemDrag : public UDragDropOperation, public IItemDragInterface
{
	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------------------------
	// INTERFACE FUNCTIONS
	//--------------------------------------------------------------------------------------------
	virtual void GetItemDragInfo(int32 &OutSlotIndex, EContainerType &OutFromContainer, EArmorType &OutArmorType, EItemType &OutItemType) override;
	//--------------------------------------------------------------------------------------------
	// DRAGGED OPERATION PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(EditAnywhere ,BlueprintReadWrite, Category = "Widget Data", meta=(ExposeOnSpawn))
	int32 SlotIndex;

	UPROPERTY(EditAnywhere ,BlueprintReadWrite, Category = "Widget Data", meta=(ExposeOnSpawn))
	EContainerType FromContainer;

	UPROPERTY(EditAnywhere ,BlueprintReadWrite, Category = "Widget Data", meta=(ExposeOnSpawn))
	EItemType ItemType;

	UPROPERTY(EditAnywhere ,BlueprintReadWrite, Category = "Widget Data", meta=(ExposeOnSpawn))
	EArmorType ArmorType;
};

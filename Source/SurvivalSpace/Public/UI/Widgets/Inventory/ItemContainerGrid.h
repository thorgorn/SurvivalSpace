// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Enums/Enums.h"
#include "ItemContainerGrid.generated.h"

class UScrollBox;
class UInventorySlot;
class UUniformGridPanel;
/**
 * 
 */
UCLASS()
class SURVIVALSPACE_API UItemContainerGrid : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------------------------
	// ITEM CONTAINER GRID FUNCTIONS
	//--------------------------------------------------------------------------------------------

	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void AddSlots(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void AddSlotToGrid(int32 Index, UInventorySlot* ItemSlot);

	//--------------------------------------------------------------------------------------------
	// ITEM CONTAINER GRID GETTERS
	//--------------------------------------------------------------------------------------------
	UFUNCTION(BlueprintPure, Category = "Data")
	TArray<UInventorySlot*> GetSlots() const;
	//--------------------------------------------------------------------------------------------
	// ITEM CONTAINER GRID PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UUniformGridPanel> Grid;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UScrollBox> ScrollBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ContainerData", meta=(ExposeOnSpawn))
	int32 SlotsPerRow;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ContainerData", meta=(ExposeOnSpawn))
	int32 TotalSlots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ContainerData", meta=(ExposeOnSpawn))
	EContainerType ContainerType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ContainerData")
	TSubclassOf<UInventorySlot> InventorySlotClass;

	UPROPERTY(BlueprintReadWrite, Category = "ContainerData")
	TObjectPtr<UInventorySlot> InventorySlot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ContainerData")
	int32 ItemIndex;

	UPROPERTY(BlueprintReadWrite, Category = "ContainerData")
	int32 DesiredSlotToFocus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ContainerData")
	bool bShowScrollBar = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ContainerData")
	bool bIsCraftingSlot = false;

private:

	//--------------------------------------------------------------------------------------------
	// ITEM CONTAINER GRID PRIVATE VARIABLES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(BlueprintReadWrite, Category = "ContainerData", meta=(AllowPrivateAccess))
	TArray<TObjectPtr<UInventorySlot>> Slots;
	
};

// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Enums/Enums.h"
#include "Structs/Structs.h"
#include "CraftingContainer.generated.h"


class UCraftingRecipeSlot;
class UUniformGridPanel;
class UScrollBox;
/**
 * 
 */
UCLASS()
class SURVIVALSPACE_API UCraftingContainer : public UUserWidget
{
	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------------------------
	// CRAFTING CONTAINER GRID FUNCTIONS
	//--------------------------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable)
	void InitializeSlots();

	UFUNCTION(BlueprintCallable)
	void UpdateSlots(ECraftingType ItemCraftingType, TArray<FItem> ItemArray);

	UFUNCTION(BlueprintCallable)
	void AddSlots(ECraftingType InCraftingType, TArray<FItem> ItemArray, bool bAdminMode);
	
	UFUNCTION(BlueprintCallable)
	void AddSlotsToGrid(int32 Index, UCraftingRecipeSlot* InSlot);

	UFUNCTION(BlueprintCallable, Category = "CraftingContainerFunctions")
	void CheckCraftableItem(TArray<FItemRecipes> RequiredItems, TArray<FItem> ItemsArray, bool& bCanCraft, TArray<FItemRecipeInfo>& LocalItems);
	//--------------------------------------------------------------------------------------------
	// CRAFTING CONTAINER GRID PROPERTIES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UScrollBox> ScrollBox;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UUniformGridPanel> Grid;

	//--------------------------------------------------------------------------------------------
	// CRAFTING CONTAINER GRID VARIABLES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(EditAnywhere ,BlueprintReadWrite, Category = "Data")
	EContainerType ContainerType;

	UPROPERTY(EditAnywhere ,BlueprintReadWrite, Category = "Data")
	ECraftingType CraftingType;

	UPROPERTY(EditAnywhere ,BlueprintReadWrite, Category = "Data")
	TArray<UCraftingRecipeSlot*> Slots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TSubclassOf<UCraftingRecipeSlot> CraftingSlotClass;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	TObjectPtr<UCraftingRecipeSlot> CraftingSlot;

	UPROPERTY(EditAnywhere ,BlueprintReadWrite, Category = "Data")
	int32 SlotsPerRow = 6;
};

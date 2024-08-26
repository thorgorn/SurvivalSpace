// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Crafting.generated.h"

class UCraftingContainer;
class UCraftingItemContainerGrid;

/**
 * 
 */
UCLASS()
class SURVIVALSPACE_API UCrafting : public UUserWidget
{
	GENERATED_BODY()

	//--------------------------------------------------------------------------------------------
	// CRAFTING WIDGET PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------

public:
	
	UPROPERTY(BlueprintReadWrite, Category = "Widgets", meta=(BindWidget))
	TObjectPtr<UCraftingItemContainerGrid> CraftingItemContainerGrid;

	UPROPERTY(BlueprintReadWrite, Category = "Widgets", meta=(BindWidget))
	TObjectPtr<UCraftingContainer> CraftingContainerGrid;
	
};

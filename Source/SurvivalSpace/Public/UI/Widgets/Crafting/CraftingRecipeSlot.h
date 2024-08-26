// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "Enums/Enums.h"
#include "Structs/Structs.h"
#include "CraftingRecipeSlot.generated.h"

class UCraftingInfo;
class UItemRecipe;
class UImage;
class UBorder;
class USizeBox;
/**
 * 
 */
UCLASS()
class SURVIVALSPACE_API UCraftingRecipeSlot : public UCommonButtonBase
{
	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------------------------
	// CRAFTING SLOT FUNCTIONS
	//--------------------------------------------------------------------------------------------
		virtual void NativeOnHovered() override;

		virtual void NativeOnUnhovered() override;
	//--------------------------------------------------------------------------------------------
	// CRAFTING SLOT VARIABLES
	//--------------------------------------------------------------------------------------------
	UPROPERTY(EditAnywhere ,BlueprintReadWrite, Category = "Data")
	bool bCanCraftItem;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	TObjectPtr<UTexture2D> ItemIconTexture;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	int32 ItemID;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	int32 ItemIndex;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	EContainerType ContainerType;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	TArray<FItemRecipeInfo> RequiredItems;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	FText ItemName;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	ECraftingType CraftingType;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	TSoftObjectPtr<UItemRecipe> RecipeAsset;

	UPROPERTY(BlueprintReadWrite, Category = "Widgets")
	TObjectPtr<UCraftingInfo> CraftingInfoWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UCraftingInfo> CraftingInfoWidgetClass;
	
	
	//--------------------------------------------------------------------------------------------
	// CRAFTING SLOT PROPERTIES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<USizeBox> SizeBox;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UBorder> CraftingItemBackground;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UImage> CraftingItemIcon;
};

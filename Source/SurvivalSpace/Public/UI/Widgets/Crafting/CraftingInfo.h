// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/Structs.h"
#include "CraftingInfo.generated.h"

class UProgressBar;
class UVerticalBox;
class UCraftItemResource;
class UItemInfo;
class UCommonButtonBase;
class UTextBlock;
class UHorizontalBox;
class UBorder;
class UImage;
/**
 * 
 */
UCLASS()
class SURVIVALSPACE_API UCraftingInfo : public UUserWidget
{
	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------------------------
	// CRAFTING ITEM INFO PROPERTIES
	//--------------------------------------------------------------------------------------------

	UFUNCTION(BlueprintCallable)
	void SetupWidgetData();

	UFUNCTION(BlueprintImplementableEvent)
	void CraftItem();

	//--------------------------------------------------------------------------------------------
	// CRAFTING ITEM INFO PROPERTIES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UImage> BGAlpha;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UBorder> BorderColor;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UVerticalBox> ResourceBox;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UHorizontalBox> CraftingProgressBox;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UProgressBar> CraftingProgressBar;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UTextBlock> ItemDescription;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UImage> ItemIcon;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UTextBlock> ItemName;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UTextBlock> ItemTypeText;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UCommonButtonBase> CraftButton;

	//--------------------------------------------------------------------------------------------
	// CRAFTING ITEM INFO VARIABLES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(BlueprintReadWrite, Category = "Data", meta=(ExposeOnSpawn))
	TSoftObjectPtr<UItemInfo> ItemAsset;

	UPROPERTY(BlueprintReadWrite, Category = "Data", meta=(ExposeOnSpawn))
	TObjectPtr<UTexture2D> ItemIconTexture;

	UPROPERTY(BlueprintReadWrite, Category = "Data", meta=(ExposeOnSpawn))
	TArray<FItemRecipeInfo> RequiredItems;

	UPROPERTY(BlueprintReadWrite, Category = "Data", meta=(ExposeOnSpawn))
	FText ItemNameText;

	UPROPERTY(BlueprintReadWrite, Category = "Widgets")
	TObjectPtr<UCraftItemResource> CraftItemResourceWidget;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UCraftItemResource> CraftItemResourceWidgetClass;
};

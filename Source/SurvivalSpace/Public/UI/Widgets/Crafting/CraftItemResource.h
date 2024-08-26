// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CraftItemResource.generated.h"

class UProgressBar;
class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class SURVIVALSPACE_API UCraftItemResource : public UUserWidget
{
	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------------------------
	// CRAFTING ITEM RESOURCE INFO FUNCTIONS
	//--------------------------------------------------------------------------------------------
	virtual void NativeConstruct() override;
	//--------------------------------------------------------------------------------------------
	// CRAFTING ITEM RESOURCE INFO PROPERTIES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UImage> ItemResourceIcon;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UTextBlock> ResourceQuantity;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UTextBlock> ItemName;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UProgressBar> ResourceProgressBar;

	//--------------------------------------------------------------------------------------------
	// CRAFTING ITEM RESOURCE INFO VARIABLES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	TObjectPtr<UTexture2D> ResourceIconTexture;
	
	UPROPERTY(BlueprintReadWrite, Category = "Data")
	FText ItemNameText;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	int32 ResourceCurrentAmount;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	int32 ResourceNeededAmount;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	float ResourceAmount;
	
};

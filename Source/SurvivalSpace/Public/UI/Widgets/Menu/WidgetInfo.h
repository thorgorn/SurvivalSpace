// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetInfo.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class SURVIVALSPACE_API UWidgetInfo : public UUserWidget
{
	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------------------------
	// INFO WIDGET FUNCTIONS
	//--------------------------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable)
	void UpdateText(FText WidgetName, FText WidgetDescription);
	//--------------------------------------------------------------------------------------------
	// INFO WIDGET PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UTextBlock> WidgetInfoText;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UTextBlock> WidgetInfoDescription;
	
};

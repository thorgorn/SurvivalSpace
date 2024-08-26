// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "ItemToolTip.generated.h"

class UItemInfoWidget;
class UCommonActivatableWidgetStack;
/**
 * 
 */
UCLASS()
class SURVIVALSPACE_API UItemToolTip : public UCommonUserWidget
{
	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------------------------
	// WIDGET FUNCTIONS
	//--------------------------------------------------------------------------------------------
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "UI")
	void PushItemInfoWidget();
	
	//--------------------------------------------------------------------------------------------
	// WIDGET PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget), Category = "Stacks")
	TObjectPtr<UCommonActivatableWidgetStack> ItemInfoStack;
	
	UPROPERTY(BlueprintReadWrite, Category = "PushWidgets")
	TObjectPtr<UItemInfoWidget> ItemInfoWidget;
	
};

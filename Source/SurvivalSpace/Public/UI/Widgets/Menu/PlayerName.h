// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerName.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class SURVIVALSPACE_API UPlayerName : public UUserWidget
{
	GENERATED_BODY()

protected:
	//--------------------------------------------------------------------------------------------
	// PLAYER NAME WIDGET FUNCTIONS
	//--------------------------------------------------------------------------------------------
	virtual void NativeConstruct() override;
	//--------------------------------------------------------------------------------------------
	// PLAYER NAME WIDGET PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UTextBlock> PlayerNameText;
	
};

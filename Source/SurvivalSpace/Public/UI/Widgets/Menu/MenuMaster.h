// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "MenuMaster.generated.h"

class UCommonButton;
/**
 * 
 */
UCLASS()
class SURVIVALSPACE_API UMenuMaster : public UCommonUserWidget
{
	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------------------------
	// MENU MASTER WIDGET PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UCommonButton> InventoryButton;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UCommonButton> EquipmentButton;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UCommonButton> CraftingButton;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UCommonButton> SkillsButton;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UCommonButton> MapButton;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UCommonButton> SettingsButton;
	
};

// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HotBarWidget.generated.h"

class UUniformGridPanel;
class UInputActionWidget;
class UItemContainerGrid;
/**
 * 
 */
UCLASS()
class SURVIVALSPACE_API UHotBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------------------------
	// HOTBAR PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UItemContainerGrid> ItemContainerGrid;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UUniformGridPanel> UniformGridPanelActions;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UUniformGridPanel> UniformGridPanelController;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UInputActionWidget> InputAction1;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UInputActionWidget> InputAction2;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UInputActionWidget> InputAction3;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UInputActionWidget> InputAction4;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UInputActionWidget> InputAction5;
	
	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UInputActionWidget> InputAction6;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UInputActionWidget> InputAction7;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UInputActionWidget> InputAction8;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UInputActionWidget> InputActionController;
};

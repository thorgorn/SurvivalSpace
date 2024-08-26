// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Enums/Enums.h"
#include "Structs/Structs.h"
#include "GameInventoryLayout.generated.h"

class UPlayerName;
class UWidgetInfo;
class UMenuMaster;
class UWidgetSwitcher;
class UCrafting;
class UInventory;
class UCommonButton;
class UHotBarWidget;
/**
 * 
 */
UCLASS()
class SURVIVALSPACE_API UGameInventoryLayout : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------------------------
	// STANDARD FUNCTIONS
	//--------------------------------------------------------------------------------------------

	virtual void NativeConstruct() override;

	virtual void NativeOnDeactivated() override;
	
	//--------------------------------------------------------------------------------------------
	// BUTTON FUNCTIONS
	//--------------------------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable, Category = "ButtonFunctions")
	void InventoryButtonClicked();

	UFUNCTION(BlueprintCallable, Category = "ButtonFunctions")
	void UpdateCraftWidget(ECraftingType CraftingType, TArray<FItem> ItemArray);
	
	//--------------------------------------------------------------------------------------------
	// BUTTON PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(ExposeOnSpawn))
	TObjectPtr<UHotBarWidget> HotBarWidget;
	
	UPROPERTY(BlueprintReadWrite, Category = "Widgets", meta=(BindWidget))
	TObjectPtr<UCommonButton> CloseInventoryButton;

	UPROPERTY(BlueprintReadWrite, Category = "Widgets", meta=(BindWidget))
	TObjectPtr<UInventory> InventoryWidget;

	UPROPERTY(BlueprintReadWrite, Category = "Widgets", meta=(BindWidget))
	TObjectPtr<UCrafting> CraftingWidget;

	UPROPERTY(BlueprintReadWrite, Category = "Widgets", meta=(BindWidget))
	TObjectPtr<UMenuMaster> MenuMasterWidget;

	UPROPERTY(BlueprintReadWrite, Category = "Widgets", meta=(BindWidget))
	TObjectPtr<UWidgetInfo> WidgetInfoWidget;

	UPROPERTY(BlueprintReadWrite, Category = "Widgets", meta=(BindWidget))
	TObjectPtr<UPlayerName> PlayerNameWidget;

	UPROPERTY(BlueprintReadWrite, Category = "Widgets", meta=(BindWidget))
	TObjectPtr<UWidgetSwitcher> WidgetSwitcher;


	
};

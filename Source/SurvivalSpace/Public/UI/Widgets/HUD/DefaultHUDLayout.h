// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "DefaultHUDLayout.generated.h"

class UItemCollected;
class UVerticalBox;
class UHotBarWidget;
/**
 * 
 */
UCLASS()
class SURVIVALSPACE_API UDefaultHUDLayout : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------------------------
	// DEFAULT HUD LAYOUT FUNCTIONS
	//--------------------------------------------------------------------------------------------

	UFUNCTION(BlueprintCallable)
	void AddResource(UTexture2D* Icon, int32 Quantity, FText ItemName);
	
	UFUNCTION(BlueprintCallable)
	void RemoveResource(UTexture2D* Icon, int32 Quantity, FText ItemName);
	//--------------------------------------------------------------------------------------------
	// DEFAULT HUD LAYOUT PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(ExposeOnSpawn))
	TObjectPtr<UHotBarWidget> HotBarWidget;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UVerticalBox> ResourcesCollected;

	UPROPERTY(EditAnywhere ,BlueprintReadWrite, Category = "Widget Data")
	TSubclassOf<UItemCollected> ItemCollectedWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "Widget Data")
	TObjectPtr<UItemCollected> ItemCollectedWidget;

	UPROPERTY(EditAnywhere ,BlueprintReadWrite, Category = "Widget Data")
	TSubclassOf<UItemCollected> ItemDestroyedWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "Widget Data")
	TObjectPtr<UItemCollected> ItemDestroyedWidget;
	
};


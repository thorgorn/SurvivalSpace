// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "MainUILayout.generated.h"

class UItemInfoWidget;
class UGameInventoryLayout;
class UActivatableWidgetStackCustom;
class UDefaultHUDLayout;
class UCommonActivatableWidgetStack;
/**
 * 
 */
UCLASS()
class SURVIVALSPACE_API UMainUILayout : public UCommonUserWidget
{
	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------------------------
	// WIDGET FUNCTIONS
	//--------------------------------------------------------------------------------------------
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void PushDefaultHUDLayout();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "UI")
	void PushGameInventoryLayout();
	
	//--------------------------------------------------------------------------------------------
	// WIDGET PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget), Category = "Stacks")
	TObjectPtr<UCommonActivatableWidgetStack> GameHUDStack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget), Category = "Stacks")
	TObjectPtr<UCommonActivatableWidgetStack> GameInventoryStack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget), Category = "Stacks")
	TObjectPtr<UCommonActivatableWidgetStack> GameMenuStack;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PushWidgets")
	TSubclassOf<UDefaultHUDLayout> DefaultHUDLayoutClass;

	UPROPERTY(BlueprintReadWrite, Category = "PushWidgets")
	TObjectPtr<UDefaultHUDLayout> DefaultHUDLayout;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PushWidgets")
	TSubclassOf<UGameInventoryLayout> GameInventoryLayoutClass;

	UPROPERTY(BlueprintReadWrite, Category = "PushWidgets")
	TObjectPtr<UGameInventoryLayout> GameInventoryLayout;
	
};

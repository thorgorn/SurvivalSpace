// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory.generated.h"

class UItemContainerGrid;
/**
 * 
 */
UCLASS()
class SURVIVALSPACE_API UInventory : public UUserWidget
{
	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------------------------
	// INVENTORY WIDGET PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(BlueprintReadWrite, Category = "Widgets", meta=(BindWidget))
	TObjectPtr<UItemContainerGrid> ItemContainerGrid;
	
};

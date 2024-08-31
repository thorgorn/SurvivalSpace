// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/Enums.h"
#include "Structs/Structs.h"
#include "UObject/Interface.h"
#include "ControllerInterface.generated.h"

class UItemRecipe;
// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable)
class UControllerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SURVIVALSPACE_API IControllerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(Blueprintable)
	virtual void CloseInventory();

	UFUNCTION(Blueprintable)
	virtual void UpdateItemSlot(EContainerType Container, int32 Index, FItemStructure ItemInfo);

	UFUNCTION(Blueprintable)
	virtual void ResetItemSlot(EContainerType Container, int32 Index);

	UFUNCTION(Blueprintable)
	virtual void ShowItemCollected(UTexture2D* ResourceImage, int32 ResourceQuantity, FText ResourceName);

	UFUNCTION(BlueprintCallable)
	virtual void ShowItemDestroyed(UTexture2D* ResourceImage, int32 ResourceQuantity, FText ResourceName);

	UFUNCTION(BlueprintCallable)
	virtual void DestroyItem(int32 Index);

	UFUNCTION(BlueprintCallable)
	virtual void SetFocusInventory();

	UFUNCTION(BlueprintCallable)
	virtual void SetSelectedItem(EContainerType ContainerType, int32 SelectedIndex, bool ItemInFirstSlot, EArmorType ArmorType);

	UFUNCTION(Blueprintable)
	virtual void UpdateCraftItemSlot(EContainerType Container, int32 Index, FItemStructure ItemInfo);

	UFUNCTION(Blueprintable)
	virtual void ResetCraftItemSlot(EContainerType Container, int32 Index);

	UFUNCTION(Blueprintable)
	virtual void UpdateCraftResourceUI();

	UFUNCTION(Blueprintable)
	virtual void SetupCraftableItems(ECraftingType CraftingType, TArray<FSimpleItemStructure> ItemArray);

	UFUNCTION(Blueprintable)
	virtual void DisplayCraftProgress();
	
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/ControllerInterface.h"
#include "SurvivalController.generated.h"

class UCraftingSlot;
class UCraftingItemContainerGrid;
class UItemContainerGrid;
class UItemToolTip;
class UInventorySlot;
class UInputAction;
class UCommonActivatableWidget;
class UMainUILayout;
class UInputMappingContext;
class UTexture2D;
/**
 * 
 */
UCLASS()
class SURVIVALSPACE_API ASurvivalController : public APlayerController, public IControllerInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	bool bInventoryShown = false;

	UPROPERTY(BlueprintReadWrite, Category = "Crafting")
	bool CraftingShown = false;


protected:

	//--------------------------------------------------------------------------------------------
	// CONTROLLER FUNCTIONS
	//--------------------------------------------------------------------------------------------

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
	//--------------------------------------------------------------------------------------------
	// INTERFACE FUNCTIONS
	//--------------------------------------------------------------------------------------------
	
	virtual void CloseInventory() override;

	virtual void DestroyItem(int32 Index) override;

	virtual void ResetItemSlot(EContainerType Container, int32 Index) override;

	virtual void ResetCraftItemSlot(EContainerType Container, int32 Index) override;

	virtual void UpdateItemSlot(EContainerType Container, int32 Index, FItemStructure ItemInfo) override;

	virtual void UpdateCraftItemSlot(EContainerType Container, int32 Index, FItemStructure ItemInfo) override;

	virtual void UpdateCraftResourceUI() override;

	virtual void ShowItemCollected(UTexture2D* ResourceImage, int32 ResourceQuantity, FText ResourceName) override;

	virtual void ShowItemDestroyed(UTexture2D* ResourceImage, int32 ResourceQuantity, FText ResourceName) override;
	
	virtual void SetSelectedItem(EContainerType ContainerType, int32 SelectedIndex, bool ItemInFirstSlot, EArmorType ArmorType) override;

	virtual void SetupCraftableItems(ECraftingType CraftingType, TArray<FItem> ItemArray) override;
	

	//--------------------------------------------------------------------------------------------
	// INPUT MAPPING
	//--------------------------------------------------------------------------------------------
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> InventoryAction;
	
	//--------------------------------------------------------------------------------------------
	// CONTROLLER PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------
	UPROPERTY(BlueprintReadWrite, Category="Widgets")
	TObjectPtr<UMainUILayout> RootLayout;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Widgets")
	TSubclassOf<UMainUILayout> RootLayoutClass;
	
	UPROPERTY(BlueprintReadWrite)
	bool bItemSelected;

	UPROPERTY()
	int32 SelectedItemIndex;

	UPROPERTY()
	EContainerType SelectedContainer;
	
	// Timer handle for the delay on Inventory
	FTimerHandle InventoryTimerHandle;

	//Timer handle for the delay to reset ItemSelectedBool
	FTimerHandle SelectedItemTimerHandle;


	
	//--------------------------------------------------------------------------------------------
	// CONTROLLER INPUT FUNCTIONS
	//--------------------------------------------------------------------------------------------
	UFUNCTION(Blueprintable, Client, Unreliable, Category = "Input Functions")
	void InventoryOnClient();

	UFUNCTION(Blueprintable, Category = "Input Functions")
	void DelayOpenInventory();

	UFUNCTION(Blueprintable, Category = "Input Functions")
	void OpenInventory();
	
	//--------------------------------------------------------------------------------------------
	// CONTROLLER WIDGET FUNCTIONS
	//--------------------------------------------------------------------------------------------

	UFUNCTION(BlueprintCallable, Category = "ControllerFunctions")
	void SetupMainUIWidget();

	UFUNCTION(BlueprintCallable,Server, Unreliable, Category = "ControllerFunctions")
	void DestroyItemWidget(int32 ItemIndex);

	UFUNCTION(BlueprintCallable, Category = "ControllerFunctions")
	void InitialiseInventoryWidget();

	UFUNCTION(BlueprintCallable, Client, Unreliable, Category = "Controller Functions")
	void ShowItemOnClient(UTexture2D* InIcon, int32 InQuantity, const FText& InName);

	UFUNCTION(BlueprintCallable, Client, Unreliable, Category = "Controller Functions")
	void ShowItemDestroyOnClient(UTexture2D* InIcon, int32 InQuantity, const FText& InName);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void ResetSelectedItemStatus();

	UFUNCTION(BlueprintCallable,Server, Unreliable, Category = "ControllerFunctions")
	void UpdateHotBarUI();

	UFUNCTION(BlueprintCallable, Server, Unreliable,Category = "ControllerFunctions")
	void UpdateCraftingUI();

	UFUNCTION(BlueprintCallable, Client, Unreliable, Category = "ControllerFunctions")
	void CraftWidgetOnClient(ECraftingType CraftingType, const TArray<FItem>& ItemsArray) const;

	
	
	//--------------------------------------------------------------------------------------------
	// CONTROLLER INVENTORY FUNCTIONS
	//--------------------------------------------------------------------------------------------

	UFUNCTION(BlueprintCallable, Client, Reliable, Category = "Controller Functions")
	void UpdateSlotOnClient(EContainerType Container, int32 Index, FItemStructure ItemInfo);
	
	void GetInventoryWidget(EContainerType Container, int32 SlotIndex, TObjectPtr<UInventorySlot>& Widget);
	
	void GetCraftingItemWidget(int32 SlotIndex, TObjectPtr<UCraftingSlot>& Widget);

	UFUNCTION(BlueprintCallable, Client, Reliable, Category = "Controller Functions")
	void UpdateCraftingSlotOnClient(int32 Index, FItemStructure ItemInfo);

	UFUNCTION(BlueprintCallable, Client, Unreliable, Category = "ControllerFunctions")
	void ResetOnClient(EContainerType Container, int32 Index);

	UFUNCTION(BlueprintCallable, Client, Unreliable, Category = "ControllerFunctions")
	void ResetCraftSlotOnClient(EContainerType Container, int32 Index);
};

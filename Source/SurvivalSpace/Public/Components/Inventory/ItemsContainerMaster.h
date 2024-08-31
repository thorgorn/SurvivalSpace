// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enums/Enums.h"
#include "Structs/Structs.h"
#include "ItemsContainerMaster.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class SURVIVALSPACE_API UItemsContainerMaster : public UActorComponent
{
	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------------------------
	// ITEMS CONTAINER MASTER CONSTRUCTOR
	//--------------------------------------------------------------------------------------------
	
	UItemsContainerMaster();

	UFUNCTION(BlueprintCallable, Server, Unreliable, Category = "Items Container Master")
	void AddItemOnServer(const FItemStructure Item);
	//--------------------------------------------------------------------------------------------
	// ITEMS CONTAINER MASTER GETTER FUNCTIONS
	//--------------------------------------------------------------------------------------------
	UFUNCTION(BlueprintPure, Category = "Items Container Master")
	TArray<FItemStructure> GetItems() const;

	UFUNCTION(BlueprintPure, Category = "Items Container Master")
	EContainerType GetContainerType() const;

	UFUNCTION(BlueprintPure, Category = "Items Container Master")
	FItemStructure GetItemAtIndex(int32 Index);

	UFUNCTION(BlueprintPure, Category = "Items Container Master")
	bool GetIsSlotEmpty(const int32 SlotIndex);

	UFUNCTION(BlueprintPure, Category = "Items Container Master")
	TArray<FSimpleItemStructure> GetItemQuantities();

	//--------------------------------------------------------------------------------------------
	// ITEMS CONTAINER MASTER SETTER FUNCTIONS
	//--------------------------------------------------------------------------------------------
	UFUNCTION(BlueprintPure, Category = "Items Container Master")
	virtual bool RemoveItemAtIndex(const int32 Index);
	//--------------------------------------------------------------------------------------------
	// ITEMS CONTAINER MASTER PUBLIC FUNCTIONS
	//--------------------------------------------------------------------------------------------
	
	UFUNCTION(BlueprintCallable, Category = "Items Container Master")
	void TransferItem(UItemsContainerMaster* ToComponent , int32 ToSpecificIndex, int32 ItemIndexToTransfer);

	UFUNCTION(BlueprintCallable, Category = "Items Container Master")
	void TransferItemHotKey(UItemsContainerMaster* FromContainer, int32 FromIndex);

	UFUNCTION(BlueprintCallable, Server, Unreliable, Category = "Items Container Master")
	void OnSlotDrop(UItemsContainerMaster* FromContainer, int32 FromIndex, int32 DropIndex);

	UFUNCTION(BlueprintCallable, Category = "Items Container Master")
	bool CheckIfCraftable(TArray<FItemRecipes> RequiredItems);

	UFUNCTION(BlueprintCallable, Category = "Items Container Master")
	void CraftItem(TArray<FItemRecipes> RequiredItems);

protected:
	
	//--------------------------------------------------------------------------------------------
	// ITEMS CONTAINER MASTER PROTECTED FUNCTIONS
	//--------------------------------------------------------------------------------------------
	
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, Category = "Items Container Master")
	void AddItem(const FItemStructure& Item, bool AddSplitItem);
	


	UFUNCTION(BlueprintPure, Category = "Items Container Master")
	virtual bool AddItemToIndex(const FItemStructure& ItemInfo, int32 TargetIndex,
	int32 FromIndex);
	
	UFUNCTION(BlueprintCallable, Category = "Items Container Master")
	virtual void HandleSlotDrop(UItemsContainerMaster* FromContainer, int32 FromIndex, int32 DropIndex);

private:
	
	//--------------------------------------------------------------------------------------------
	// ITEMS CONTAINER MASTER PRIVATE HELPER FUNCTIONS
	//--------------------------------------------------------------------------------------------
	
	void HandleStackableItem(FItemStructure& LocalItemInfo, bool bAddSplitItem);

	void AddSplitItemToInventory(FItemStructure& LocalItemInfo);

	void StackOrAddNewItems(FItemStructure& LocalItemInfo);

	void StackExistingItems(FItemStructure& LocalItemInfo);

	void AddRemainingItemsToNewSlots(FItemStructure& LocalItemInfo);

	void AddItemToEmptySlot(FItemStructure& LocalItemInfo);

	UFUNCTION(BlueprintPure, Category = "Items Container Master")
	bool HasItemsToStack(const FItemStructure& ItemInfo);
	
	UFUNCTION(BlueprintPure, Category = "Items Container Master")
	bool FindEmptySlot(int32& OutEmptySlotIndex);

	//--------------------------------------------------------------------------------------------
	// ITEMS CONTAINER MASTER PRIVATE FUNCTIONS
	//--------------------------------------------------------------------------------------------

	UFUNCTION(BlueprintCallable, Category = "Items Container Master")
	void UpdateUI(int32 Index, FItemStructure ItemInfo);
	
	//--------------------------------------------------------------------------------------------
	// ITEMS CONTAINER MASTER PRIVATE VARIABLES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	EContainerType ContainerType;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TArray<FItemStructure> Items;

};
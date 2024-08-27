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
	bool IsSlotEmpty(const int32 SlotIndex);

	//--------------------------------------------------------------------------------------------
	// ITEMS CONTAINER MASTER PUBLIC FUNCTIONS
	//--------------------------------------------------------------------------------------------
	
	UFUNCTION(BlueprintCallable, Category = "Items Container Master")
	void TransferItem(UItemsContainerMaster* ToComponent , int32 ToSpecificIndex, int32 ItemIndexToTransfer);
	
	UFUNCTION(BlueprintCallable, Server, Unreliable, Category = "Items Container Master")
	void OnSlotDrop(UItemsContainerMaster* FromContainer, int32 FromIndex, int32 DropIndex);
	
	UFUNCTION(BlueprintPure, Category = "Items Container Master")
	virtual bool RemoveItemAtIndex(const int32 Index);
	
	UFUNCTION(BlueprintCallable, Category = "Items Container Master")
	void TransferItemHotKey(UItemsContainerMaster* FromContainer, int32 FromIndex);

	UFUNCTION(BlueprintCallable, Category = "Items Container Master")
	void GetItemQuantities(TArray<FItem>& ItemArray);

protected:
	
	//--------------------------------------------------------------------------------------------
	// ITEMS CONTAINER MASTER PROTECTED FUNCTIONS
	//--------------------------------------------------------------------------------------------
	
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, Category = "Items Container Master")
	void AddItem(const FItemStructure& Item, bool AddSplitItem);
	
	UFUNCTION(BlueprintCallable, Server, Unreliable, Category = "Items Container Master")
	void AddItemOnServer(const FItemStructure Item);

	UFUNCTION(BlueprintCallable, Category = "Items Container Master")
	void UpdateUI(int32 Index, FItemStructure ItemInfo);
	
	UFUNCTION(BlueprintCallable, Category = "Items Container Master")
	virtual void HandleSlotDrop(UItemsContainerMaster* FromContainer, int32 FromIndex, int32 DropIndex);
	
	UFUNCTION(BlueprintPure, Category = "Items Container Master")
	virtual bool AddItemToIndex(const FItemStructure& ItemInfo, int32 TargetIndex,
	int32 FromIndex);


private:
	
	//--------------------------------------------------------------------------------------------
	// ITEMS CONTAINER MASTER PRIVATE HELPER FUNCTIONS
	//--------------------------------------------------------------------------------------------

	UFUNCTION(BlueprintPure, Category = "Items Container Master")
	bool HasItemsToStack(const FItemStructure& ItemInfo);

	void HandleStackableItem(FItemStructure& LocalItemInfo, bool bAddSplitItem);

	void AddSplitItemToInventory(FItemStructure& LocalItemInfo);

	void StackOrAddNewItems(FItemStructure& LocalItemInfo);

	void StackExistingItems(FItemStructure& LocalItemInfo);

	void AddRemainingItemsToNewSlots(FItemStructure& LocalItemInfo);

	void AddItemToEmptySlot(FItemStructure& LocalItemInfo);
	
	UFUNCTION(BlueprintPure, Category = "Items Container Master")
	bool FindEmptySlot(int32& OutEmptySlotIndex);
	
	//--------------------------------------------------------------------------------------------
	// ITEMS CONTAINER MASTER PRIVATE VARIABLES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	EContainerType ContainerType;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TArray<FItemStructure> Items;

};
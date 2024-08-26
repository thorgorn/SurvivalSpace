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
	// ITEMS CONTAINER MASTER PUBLIC FUNCTIONS
	//--------------------------------------------------------------------------------------------


	void TransferItem(UItemsContainerMaster* ToComponent , int32 ToSpecificIndex, int32 ItemIndexToTransfer);
	
	UFUNCTION(BlueprintCallable, Server, Unreliable, Category = "Items Container Master")
	void OnSlotDrop(UItemsContainerMaster* FromContainer, int32 FromIndex, int32 DropIndex);
	
	UFUNCTION(BlueprintPure, Category = "Items Container Master")
	void GetItemAtIndex(int32 Index, FItemStructure &ItemInfo);

	UFUNCTION(BlueprintCallable, Category = "Items Container Master")
	virtual void RemoveItemAtIndex(int32 Index, bool &Success);

	UFUNCTION(BlueprintPure, Category = "Items Container Master")
	bool IsSlotEmpty(int32 SlotIndex);

	UFUNCTION(BlueprintCallable, Category = "Items Container Master")
	void TransferItemHotKey(UItemsContainerMaster* FromContainer, int32 FromIndex);

	UFUNCTION(BlueprintCallable, Category = "Items Container Master")
	void GetItemQuantities(TArray<FItem>& ItemArray);
	
	//--------------------------------------------------------------------------------------------
	// ITEMS CONTAINER MASTER PUBLIC PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
	EContainerType ContainerType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FItemStructure> Items;
	
protected:
	
	//--------------------------------------------------------------------------------------------
	// ITEMS CONTAINER MASTER PROTECTED FUNCTIONS
	//--------------------------------------------------------------------------------------------
	
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, Category = "Items Container Master")
	void FindEmptySlot(bool& Success, int32& EmptySlotIndex);

	UFUNCTION(BlueprintCallable, Category = "Items Container Master")
	void AddItem(const FItemStructure& Item, bool AddSplitItem);
	
	UFUNCTION(BlueprintCallable, Server, Unreliable, Category = "Items Container Master")
	void AddItemOnServer(const FItemStructure Item);

	UFUNCTION(BlueprintCallable, Category = "Items Container Master")
	void UpdateUI(int32 Index, FItemStructure ItemInfo);
	
	UFUNCTION(BlueprintCallable, Category = "Items Container Master")
	virtual void HandleSlotDrop(UItemsContainerMaster* FromContainer, int32 FromIndex, int32 DropIndex);
	
	UFUNCTION(BlueprintCallable, Category = "Items Container Master")
	virtual void AddItemToIndex(FItemStructure ItemInfo, int32 LocalSpecificIndex, int32 LocalItemIndex, bool &Success);
	
	UFUNCTION(BlueprintCallable, Category = "Items Container Master")
	void HasItemsToStack(FItemStructure ItemInfo, bool& ItemExistsInInv);

	UFUNCTION(BlueprintCallable, Category = "Items Container Master")
	virtual void SwapItemIndexes(int32 TargetIndex, int32 FromIndex);
	
	//--------------------------------------------------------------------------------------------
	// ITEMS CONTAINER MASTER PROTECTED PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------


};

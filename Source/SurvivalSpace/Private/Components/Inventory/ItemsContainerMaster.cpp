// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Inventory/ItemsContainerMaster.h"
#include "Character/ASurvivalCharacter.h"
#include "DataAssets/PrimaryAssets/ItemInfo.h"


UItemsContainerMaster::UItemsContainerMaster()
{
	ContainerType = GetContainerType();

	PrimaryComponentTick.bCanEverTick = false;
}

TArray<FItemStructure> UItemsContainerMaster::GetItems() const
{
	return Items;
}

EContainerType UItemsContainerMaster::GetContainerType() const
{
	return ContainerType;
}


void UItemsContainerMaster::BeginPlay()
{
	Super::BeginPlay();
	
}

void UItemsContainerMaster::TransferItem(UItemsContainerMaster* ToComponent, int32 ToIndex, int32 IndexToTransfer)
{
	if (!ToComponent || IsSlotEmpty(IndexToTransfer) || 
		(ToIndex == IndexToTransfer && ToComponent == this))
	{
		return;
	}

	const FItemStructure& LocalItemToTransfer = GetItemAtIndex(IndexToTransfer);

	if (ToComponent->AddItemToIndex(LocalItemToTransfer, ToIndex, IndexToTransfer))
	{
		RemoveItemAtIndex(IndexToTransfer);
	}
}


void UItemsContainerMaster::OnSlotDrop_Implementation(UItemsContainerMaster* FromContainer, int32 FromIndex,
													  int32 DropIndex)
{
	HandleSlotDrop(FromContainer, FromIndex, DropIndex);
}

FItemStructure UItemsContainerMaster::GetItemAtIndex(int32 Index)
{
	if (Items.IsValidIndex(Index))
		return Items[Index];

	return FItemStructure();
}

void UItemsContainerMaster::AddItem(const FItemStructure& Item, bool AddSplitItem)
{
	FItemStructure LocalItemInfo = Item;
	
	if (!LocalItemInfo.ItemAsset.ToSoftObjectPath().IsValid()) return; 
	
	TSoftObjectPtr<UItemInfo> LoadedAsset = LocalItemInfo.ItemAsset.LoadSynchronous();
	if (!LoadedAsset)return; 
	
	if (LoadedAsset->bIsStackable)
	{
		HandleStackableItem(LocalItemInfo, AddSplitItem);
	}
	else
	{
		AddItemToEmptySlot(LocalItemInfo);
	}
}

void UItemsContainerMaster::AddItemOnServer_Implementation(const FItemStructure Item)
{
	AddItem(Item, false);
}

void UItemsContainerMaster::UpdateUI(int32 Index, FItemStructure ItemInfo)
{
	if (AASurvivalCharacter* SurvivalCharacter = Cast<AASurvivalCharacter>(GetOwner()))
	{
		ISurvivalCharacterInterface* CharacterInterface = Cast<ISurvivalCharacterInterface>(SurvivalCharacter);
		if (CharacterInterface)
		{
			switch (ContainerType)
			{
			case EContainerType::Inventory:
					CharacterInterface->UpdateItem(ContainerType, Index, ItemInfo);
					CharacterInterface->UpdateCraftResourcesUI();
				break;
			case EContainerType::HotBar:
				CharacterInterface->UpdateItem(ContainerType, Index, ItemInfo);
				break;
			case EContainerType::Storage:
				// Update storage item
				break;
			case EContainerType::Armor:
				// Update armor item
				break;
			case EContainerType::Crafting:

				break;
			default:
				break;
			}
		}
	}
}

void UItemsContainerMaster::HandleSlotDrop(UItemsContainerMaster* FromContainer, int32 FromIndex, int32 DropIndex)
{
	// OVERRIDDEN IN CHILD CLASSES
}

bool UItemsContainerMaster::AddItemToIndex(const FItemStructure& ItemInfo, int32 ToItemIndex, int32 FromItemIndex)
{
	if (IsSlotEmpty(ToItemIndex))
	{
		if (Items.IsValidIndex(ToItemIndex))
		{
			Items[ToItemIndex] = ItemInfo;

			return true;
		}
	}
	else
	{
		
	}
	return false;
}


bool UItemsContainerMaster::IsSlotEmpty(const int32 SlotIndex)
{
	if (Items[SlotIndex].ItemID == 0) return true;
		
	
	return false;
}

bool UItemsContainerMaster::RemoveItemAtIndex(const int32 Index)
{
	Items[Index] = FItemStructure();
	
	return true;
}

void UItemsContainerMaster::TransferItemHotKey(UItemsContainerMaster* FromContainer, int32 FromIndex)
{
	FItemStructure ItemInfo = FromContainer->GetItemAtIndex(FromIndex);
	
	AddItem(ItemInfo, false);
	
	FromContainer->RemoveItemAtIndex(FromIndex);
}

void UItemsContainerMaster::GetItemQuantities(TArray<FItem>& ItemsArray)
{
	TArray<FItem> LocalItemArray;
	
	bool LocalFoundItem;
	
	int32 LocalNewQuantity; 
	
	for (int32 Index = 0; Index < Items.Num(); ++Index)
	{
		LocalFoundItem = false; 
		
		if (Items[Index].ItemID != 0)
		{
			for (int32 LocalIndex = 0; LocalIndex < LocalItemArray.Num(); ++LocalIndex)
			{
				if (Items[Index].ItemID == LocalItemArray[LocalIndex].ItemID)
				{
					LocalFoundItem = true;
					LocalNewQuantity = LocalItemArray[LocalIndex].ItemQuantity + Items[Index].ItemQuantity;
					
					LocalItemArray[LocalIndex].ItemQuantity = LocalNewQuantity;
					break;
				}
			}
			
			if (!LocalFoundItem)
			{
				FItem NewItem;
				
				NewItem.ItemID = Items[Index].ItemID;
				
				NewItem.ItemQuantity = Items[Index].ItemQuantity;
				
				LocalItemArray.Add(NewItem);
			}
		}
	}
	
	ItemsArray = LocalItemArray;
}


bool UItemsContainerMaster::HasItemsToStack(const FItemStructure& ItemInfo)
{
	for (const auto& Item : Items)
	{
		if (Item.ItemID == ItemInfo.ItemID && Item.ItemQuantity < Item.StackSize)
			return true;
	}
	
	return false;
}

void UItemsContainerMaster::HandleStackableItem(FItemStructure& LocalItemInfo, bool bAddSplitItem)
{
	if (bAddSplitItem)
	{
		AddSplitItemToInventory(LocalItemInfo);
	}
	else
	{
		StackOrAddNewItems(LocalItemInfo);
	}
}

void UItemsContainerMaster::AddSplitItemToInventory(FItemStructure& LocalItemInfo)
{
	int32 EmptySlotIndex;
	bool bSlotFound = FindEmptySlot(EmptySlotIndex);

	if (bSlotFound && Items.IsValidIndex(EmptySlotIndex))
	{
		Items[EmptySlotIndex] = LocalItemInfo;
	}
	else
	{
		Items.Insert(LocalItemInfo, EmptySlotIndex);
	}

	UpdateUI(EmptySlotIndex, LocalItemInfo);
}

void UItemsContainerMaster::StackOrAddNewItems(FItemStructure& LocalItemInfo)
{
	if (HasItemsToStack(LocalItemInfo))
	{
		StackExistingItems(LocalItemInfo);
	}

	AddRemainingItemsToNewSlots(LocalItemInfo);
}

void UItemsContainerMaster::StackExistingItems(FItemStructure& LocalItemInfo)
{
	int32 TotalItemQuantity = LocalItemInfo.ItemQuantity;

	for (int32 Index = 0; Index < Items.Num(); ++Index)
	{
		if (Items[Index].ItemID == LocalItemInfo.ItemID && Items[Index].ItemQuantity < Items[Index].StackSize)
		{
			int32 MaxStackSize = Items[Index].StackSize;
			int32 CurrentSlotQuantity = Items[Index].ItemQuantity;

			int32 NewSlotQuantity = FMath::Min(MaxStackSize, CurrentSlotQuantity + TotalItemQuantity);
			Items[Index].ItemQuantity = NewSlotQuantity;

			UpdateUI(Index, Items[Index]);

			TotalItemQuantity -= (MaxStackSize - CurrentSlotQuantity);

			if (TotalItemQuantity <= 0)
			{
				break;
			}
		}
	}

	LocalItemInfo.ItemQuantity = TotalItemQuantity;
}

void UItemsContainerMaster::AddRemainingItemsToNewSlots(FItemStructure& LocalItemInfo)
{
	int32 TotalItemQuantity = LocalItemInfo.ItemQuantity;

	while (TotalItemQuantity > 0)
	{
		int32 EmptySlotIndex;
		bool bSlotFound = FindEmptySlot(EmptySlotIndex);

		if (!bSlotFound)
		{
			break; 
		}

		int32 MaxStackSize = LocalItemInfo.StackSize;
		int32 AddableQuantity = FMath::Min(TotalItemQuantity, MaxStackSize);

		LocalItemInfo.ItemQuantity = AddableQuantity;
		Items[EmptySlotIndex] = LocalItemInfo;

		UpdateUI(EmptySlotIndex, LocalItemInfo);

		TotalItemQuantity -= AddableQuantity;
	}
}

void UItemsContainerMaster::AddItemToEmptySlot(FItemStructure& LocalItemInfo)
{
	int32 EmptySlotIndex;
	bool bSlotFound = FindEmptySlot(EmptySlotIndex);

	if (bSlotFound)
	{
		if (Items.IsValidIndex(EmptySlotIndex))
		{
			Items[EmptySlotIndex] = LocalItemInfo;
		}
		else
		{
			Items.Insert(LocalItemInfo, EmptySlotIndex);
		}
		UpdateUI(EmptySlotIndex, LocalItemInfo);
	}
}

bool UItemsContainerMaster::FindEmptySlot(int32& OutEmptySlotIndex)
{
	for (int32 Index = 0; Index < Items.Num(); ++Index)
	{
		if (Items[Index].ItemID == 0)
		{
			OutEmptySlotIndex = Index;
			return true;
		}
	}

	return false;
}


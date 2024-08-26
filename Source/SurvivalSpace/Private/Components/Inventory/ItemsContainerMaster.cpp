// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Inventory/ItemsContainerMaster.h"
#include "Character/ASurvivalCharacter.h"
#include "DataAssets/PrimaryAssets/ItemInfo.h"
#include "Kismet/KismetMathLibrary.h"


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

void UItemsContainerMaster::TransferItem(UItemsContainerMaster* ToComponent, int32 ToSpecificIndex, int32 ItemIndexToTransfer)
{
	
	bool SlotEmpty = IsSlotEmpty(ItemIndexToTransfer);
	
	bool CombinedBool = SlotEmpty || (ToSpecificIndex == ItemIndexToTransfer && ToComponent == this);

	if (CombinedBool)
	{
		
	}
	else
	{
		TObjectPtr<UItemsContainerMaster> LocalReceiverComponent = ToComponent;
		
		int32 LocalSpecificIndex = ToSpecificIndex;
		
		int32 LocalItemIndex = ItemIndexToTransfer;
		
		if (IsValid(LocalReceiverComponent))
		{
			FItemStructure LocalItemToTransfer;
			
			GetItemAtIndex(LocalItemIndex, LocalItemToTransfer);
			
			bool Success;
			
			LocalReceiverComponent->AddItemToIndex(LocalItemToTransfer, LocalSpecificIndex, LocalItemIndex, Success);
			
			if (Success)
			{
				bool RemoveSuccess;
				RemoveItemAtIndex(LocalItemIndex, RemoveSuccess);
			}
		}
	}
}

void UItemsContainerMaster::OnSlotDrop_Implementation(UItemsContainerMaster* FromContainer, int32 FromIndex,
													  int32 DropIndex)
{
	HandleSlotDrop(FromContainer, FromIndex, DropIndex);
}

void UItemsContainerMaster::GetItemAtIndex(int32 Index, FItemStructure& ItemInfo)
{
	if (Items.IsValidIndex(Index))
	{
		ItemInfo = Items[Index];
	}
}

void UItemsContainerMaster::FindEmptySlot(bool& Success, int32& EmptySlotIndex)
{
	bool FoundEmptySlot = false;
	int32 LocalEmptySlotIndex = -1;
	
	for (int32 Index = 0; Index < Items.Num(); ++Index)
	{
		FItemStructure Item = Items[Index];
		
		int32 ItemID = Item.ItemID;
		
		if (ItemID == 0)
		{
			LocalEmptySlotIndex = Index;
			FoundEmptySlot = true;
			break; 
		}
	}
	
	Success = FoundEmptySlot;
	EmptySlotIndex = LocalEmptySlotIndex;
}

void UItemsContainerMaster::AddItem(const FItemStructure& Item, bool AddSplitItem)
{
    FItemStructure LocalItemInfo = Item;
	
    int32 LocalEmptyIndex;
	
    int32 TotalItemQuantity = LocalItemInfo.ItemQuantity;
	
    int32 MaxStackSize;
	
    int32 CurrentSlotQuantity;
	
    int32 TempSlotQuantity;

    if (LocalItemInfo.ItemAsset.ToSoftObjectPath().IsValid())
    {
        UItemInfo* LoadedAsset = LocalItemInfo.ItemAsset.LoadSynchronous();

        if (LoadedAsset->bIsStackable)
        {
            if (AddSplitItem)
            {
                bool Success = false;
                int32 EmptySlotIndex = -1;
                FindEmptySlot(Success, EmptySlotIndex);

                if (Success)
                {
                    LocalEmptyIndex = EmptySlotIndex;
                    
                    if (Items.IsValidIndex(LocalEmptyIndex))
                    {
                        Items[LocalEmptyIndex] = LocalItemInfo;
                    }
                    else
                    {
                        Items.Insert(LocalItemInfo, LocalEmptyIndex);
                    }

                    UpdateUI(LocalEmptyIndex, LocalItemInfo);
                }
            }
            else
            {
                bool bItemExistsInInv;
                HasItemsToStack(LocalItemInfo, bItemExistsInInv);

                if (bItemExistsInInv)
                {
                    // Add Item if same item, and has room to stack
                    for (int32 Index = 0; Index < Items.Num(); ++Index)
                    {
                        if (Items[Index].ItemID == LocalItemInfo.ItemID && Items[Index].ItemQuantity < Items[Index].StackSize)
                        {
                            MaxStackSize = Items[Index].StackSize;
                        	
                            LocalEmptyIndex = Index;
                        	
                            CurrentSlotQuantity = Items[Index].ItemQuantity;
                        	
                            TempSlotQuantity = CurrentSlotQuantity;
                        	
                            int32 SelectIntB = CurrentSlotQuantity + TotalItemQuantity;
                        	
                            bool PickA = SelectIntB >= MaxStackSize;
                        	
                            CurrentSlotQuantity = UKismetMathLibrary::SelectInt(MaxStackSize, SelectIntB, PickA);
                        	
                            Items[LocalEmptyIndex] = LocalItemInfo;
                        	
                            Items[LocalEmptyIndex].ItemQuantity = CurrentSlotQuantity;
                        	
                            UpdateUI(LocalEmptyIndex, Items[LocalEmptyIndex]);

                            int32 RemainingItems = TotalItemQuantity - (MaxStackSize - TempSlotQuantity);
                        	
                            TotalItemQuantity = (PickA && RemainingItems > 0) ? RemainingItems : 0;
                        	
                            LocalItemInfo.ItemQuantity = TotalItemQuantity;

                            if (TotalItemQuantity <= 0)
                            {
                                break;
                            }
                        }
                    }
                }

                // Handle any remaining items that couldn't be stacked
                while (TotalItemQuantity > 0)
                {
                    bool Success = false;
                    int32 EmptySlotIndex = -1;
                    FindEmptySlot(Success, EmptySlotIndex);

                    if (Success)
                    {
                        LocalEmptyIndex = EmptySlotIndex;
                    	
                        MaxStackSize = LocalItemInfo.StackSize;

                        int32 AddableQuantity = FMath::Min(TotalItemQuantity, MaxStackSize);
                    	
                        LocalItemInfo.ItemQuantity = AddableQuantity;
                    	
                        Items[LocalEmptyIndex] = LocalItemInfo;
                    	
                        UpdateUI(LocalEmptyIndex, Items[LocalEmptyIndex]);

                        TotalItemQuantity -= AddableQuantity;
                    }
                    else
                    {
                        // Handle case where no empty slots are available
                        break;
                    }
                }
            }
        }
        else
        {
            bool Success = false;
        	
            int32 EmptySlotIndex = -1;
        	
            FindEmptySlot(Success, EmptySlotIndex);

            if (Success)
            {
                LocalEmptyIndex = EmptySlotIndex;

                if (Items.IsValidIndex(LocalEmptyIndex))
                {
                    Items[LocalEmptyIndex] = LocalItemInfo;
                }
                else
                {
                    Items.Insert(LocalItemInfo, LocalEmptyIndex);
                }
                UpdateUI(LocalEmptyIndex, LocalItemInfo);
            }
        }
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

bool UItemsContainerMaster::IsSlotEmpty(int32 SlotIndex)
{
	if (Items[SlotIndex].ItemID == 0)
		return true;
	
	return false;
}

void UItemsContainerMaster::TransferItemHotKey(UItemsContainerMaster* FromContainer, int32 FromIndex)
{
	FItemStructure ItemInfo;
	
	FromContainer->GetItemAtIndex(FromIndex, ItemInfo);
	
	AddItem(ItemInfo, false);
	
	bool Success;
	
	FromContainer->RemoveItemAtIndex(FromIndex, Success);
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


void UItemsContainerMaster::AddItemToIndex(FItemStructure ItemInfo, int32 LocalSpecificIndex, int32 LocalItemIndex, bool& Success)
{
	FItemStructure LocalItem = ItemInfo;
	
	//int32 LocalTargetIndex = LocalSpecificIndex;
	//int32 LocalFromIndex = LocalItemIndex;

	bool SlotEmpty = IsSlotEmpty(LocalSpecificIndex);

	if (SlotEmpty)
	{
		// If the target slot is empty, place the item directly
		if (Items.IsValidIndex(LocalSpecificIndex))
		{
			Items[LocalSpecificIndex] = LocalItem;
			Success = true;
		}
	}
	else
	{
		switch (ContainerType)
		{
		case EContainerType::Inventory:
			SwapItemIndexes(LocalSpecificIndex, LocalItemIndex);
			break;
		case EContainerType::HotBar:
			break;
		case EContainerType::Storage:
			break;
		case EContainerType::Armor:
			break;
		case EContainerType::Crafting:
			break;
		}
		Success = false;
	}
}

void UItemsContainerMaster::HasItemsToStack(FItemStructure ItemInfo, bool& ItemExistsInInv)
{
	//FItemStructure LocalItemInfo = ItemInfo;
	
	bool LocalItemExistsInInv = false;

	for (int32 Index = 0; Index < Items.Num(); ++Index)
	{
		if (Items[Index].ItemID == ItemInfo.ItemID && Items[Index].ItemQuantity < Items[Index].StackSize)
		{
			LocalItemExistsInInv = true;
			break;
		}
	}
	ItemExistsInInv = LocalItemExistsInInv;
}

void UItemsContainerMaster::RemoveItemAtIndex(int32 Index, bool& Success)
{
	if (Items.IsValidIndex(Index))
	{
		UItemInfo* LoadedItem = Items[Index].ItemAsset.LoadSynchronous();
		if (LoadedItem)
		{
			//UE_LOG(LogTemp, Warning, TEXT("%s Removed"),*LoadedItem->ItemName.ToString());
		}
		Items[Index] = FItemStructure();
		Success = true;
		UpdateUI(Index, Items[Index]);
	}
	else
	{
		Success = false;
	}
}

void UItemsContainerMaster::SwapItemIndexes(int32 TargetIndex, int32 FromIndex)
{
	//int32 LocalTargetIndex = TargetIndex;
	//int32 LocalFromIndex = FromIndex;

	FItemStructure LocalTargetItem = Items[TargetIndex];
	FItemStructure LocalFromItem = Items[FromIndex];

	Items[TargetIndex] = LocalFromItem;
	Items[FromIndex] = LocalTargetItem;
	UpdateUI(TargetIndex, LocalFromItem);
	UpdateUI(FromIndex, LocalTargetItem);
}
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

void UItemsContainerMaster::FindEmptySlot(bool& Success, int32& EmptySlotIndex)
{
	for (int32 i = 0; i < Items.Num(); ++i)
	{
		if (Items[i].ItemID == 0)
		{
			EmptySlotIndex = i; 

			Success = true;

			break;
		}
	}
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
               bool bItemExistsInInv = HasItemsToStack(LocalItemInfo);

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


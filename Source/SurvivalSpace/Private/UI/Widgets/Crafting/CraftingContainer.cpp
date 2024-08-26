// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.


#include "UI/Widgets/Crafting/CraftingContainer.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "DataAssets/PrimaryAssets/ItemRecipe.h"
#include "Interfaces/SurvivalCharacterInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/Widgets/Crafting/CraftingRecipeSlot.h"
#include "UI/Widgets/Crafting/CraftingSlot.h"

void UCraftingContainer::InitializeSlots()
{
	ISurvivalCharacterInterface* CharacterInterface = Cast<ISurvivalCharacterInterface>(GetOwningPlayerPawn());
	if (CharacterInterface)
	{
		CharacterInterface->GetCraftingRecipesAndItems(CraftingType);
	}
}

void UCraftingContainer::UpdateSlots(ECraftingType ItemCraftingType, TArray<FItem> ItemArray)
{
	UE_LOG(LogTemp, Warning, TEXT("Updates Crafting Slots called"));

	CraftingType = ItemCraftingType;

	Grid->ClearChildren();

	Slots.Empty();

	AddSlots(ItemCraftingType, ItemArray, false);
	
}


void UCraftingContainer::AddSlots(ECraftingType InCraftingType, TArray<FItem> ItemArray, bool bAdminMode)
{
    TArray<FItem> LocalItemArray = ItemArray;
    FName PathName; // Declare the variable once

    // Determine the path based on the crafting type
    switch (InCraftingType)
    {
    case ECraftingType::PlayerInventory:
        PathName = "/Game/_Main/DataAssets/ItemRecipes/PlayerInventory"; // Change to the desired asset path for PlayerInventory
        break;
    case ECraftingType::CookingPot:
        PathName = "/Game/CookingPotPath"; // Change to the desired asset path for CookingPot
        break;
    case ECraftingType::CraftingBench:
        PathName = "/Game/CraftingBenchPath"; // Change to the desired asset path for CraftingBench
        break;
    case ECraftingType::SmeltingForge:
        PathName = "/Game/SmeltingForgePath"; // Change to the desired asset path for SmeltingForge
        break;
    case ECraftingType::AdvancedWorkBench:
        PathName = "/Game/AdvancedWorkBenchPath"; // Change to the desired asset path for AdvancedWorkBench
        break;
    case ECraftingType::StorageBox:
        PathName = "/Game/StorageBoxPath"; // Change to the desired asset path for StorageBox
        break;
    case ECraftingType::CropPlot:
        PathName = "/Game/CropPlotPath"; // Change to the desired asset path for CropPlot
        break;
    default:
        PathName = "/Game/DefaultPath"; // Optional: Default path if none of the cases match
        break;
    }

    switch (InCraftingType)
    {
    case ECraftingType::PlayerInventory:
        if (bAdminMode)
        {
            // Logic for admin mode
        }
        else
        {
            // Get the Asset Registry module
            IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();

            // Prepare an array to store the asset data
            TArray<FAssetData> LocalDataAssets;

            // Use GetAssetsByPath to fill the array with assets found at the specified path
            bool bRecursive = true;  // Set to true if you want to include subdirectories
            AssetRegistry.GetAssetsByPath(PathName, LocalDataAssets, bRecursive);

            // Process the assets found and add to LocalItemArray or handle them appropriately
            for (const FAssetData& AssetData : LocalDataAssets)
            {
                UItemRecipe* ItemRecipe = Cast<UItemRecipe>(AssetData.GetAsset());
                if (ItemRecipe)
                {
                    bool CanCraft;
                    TArray<FItemRecipeInfo> LocalItems;
                    CheckCraftableItem(ItemRecipe->RequiredItems, ItemArray, CanCraft, LocalItems);


                    if (CraftingSlotClass)
                    {
                        CraftingSlot = CreateWidget<UCraftingRecipeSlot>(GetWorld(), CraftingSlotClass);
                        if (CraftingSlot)
                        {
                            CraftingSlot->bCanCraftItem = CanCraft;
                            CraftingSlot->ItemIconTexture = ItemRecipe->ItemIcon;
                            CraftingSlot->ItemID = ItemRecipe->ItemID;
                            CraftingSlot->ItemName = ItemRecipe->ItemName;
                            CraftingSlot->ContainerType = ContainerType;
                            CraftingSlot->RequiredItems = LocalItems;
                            CraftingSlot->CraftingType = CraftingType;
                            CraftingSlot->RecipeAsset = ItemRecipe;
                            Slots.Add(CraftingSlot);
                            CraftingSlot->ItemIndex = Slots.Num() -1 ;
                            AddSlotsToGrid(CraftingSlot->ItemIndex, CraftingSlot);
                        }
                    }
                }
            }

            // Example: Print a log to confirm the assets have been added
            //UE_LOG(LogTemp, Log, TEXT("Added %d assets from path: %s"), LocalItemArray.Num(), *PathName.ToString());
        }
        break;
    case ECraftingType::CookingPot:
        // Add your logic for CookingPot
        break;
    case ECraftingType::CraftingBench:
        // Add your logic for CraftingBench
        break;
    case ECraftingType::SmeltingForge:
        // Add your logic for SmeltingForge
        break;
    case ECraftingType::AdvancedWorkBench:
        // Add your logic for AdvancedWorkBench
        break;
    case ECraftingType::StorageBox:
        // Add your logic for StorageBox
        break;
    case ECraftingType::CropPlot:
        // Add your logic for CropPlot
        break;
    }
}

void UCraftingContainer::AddSlotsToGrid(int32 Index, UCraftingRecipeSlot* InSlot)
{
    int32 LocalSlotIndex = Index;
    UCraftingRecipeSlot* LocalCraftingSlot = InSlot;

    UUniformGridSlot* GridSlot = Grid->AddChildToUniformGrid(LocalCraftingSlot);
    if (!GridSlot)
    {
        return;
    }

    // Calculate row and column separately
    int32 SlotsPerRowValue = SlotsPerRow;

    // Calculate Row and Column
    double LocalSlotIndexAsDouble = UKismetMathLibrary::Conv_IntToDouble(LocalSlotIndex);
    double SlotsPerRowAsDouble = UKismetMathLibrary::Conv_IntToDouble(SlotsPerRowValue);

    double Remainder;
    int32 ReturnValue = UKismetMathLibrary::FMod(LocalSlotIndexAsDouble, SlotsPerRowAsDouble, Remainder);
    int32 Column = UKismetMathLibrary::FTrunc(Remainder);
    int32 Row = UKismetMathLibrary::FTrunc(ReturnValue);

    // Set row and column for the slot
    GridSlot->SetRow(Row);
    GridSlot->SetColumn(Column);
}

void UCraftingContainer::CheckCraftableItem(TArray<FItemRecipes> RequiredItems, TArray<FItem> ItemsArray,
    bool& bCanCraft, TArray<FItemRecipeInfo>& LocalItems)
{
    TArray<FItemRecipes> LocalRequiredItems = RequiredItems;
    TArray<FItem> LocalItemsArray = ItemsArray;
    TArray<FItemRecipeInfo> LocalItemsInInventory;

    bool bDoesNotContainItems = false; // Start assuming all items can be crafted.

    for (int32 Index = 0; Index < LocalRequiredItems.Num(); ++Index)
    {
        bool bLocalFound = false; // Reset for each required item.

        if (LocalItemsArray.Num() == 0)
        {
            // No items in inventory; cannot craft any
            FItemRecipeInfo NewItem;
            NewItem.ItemID = LocalRequiredItems[Index].ItemID;
            NewItem.ItemIcon = LocalRequiredItems[Index].ItemIcon;
            NewItem.ItemName = LocalRequiredItems[Index].ItemName;
            NewItem.CurrentQuantity = 0;
            NewItem.NeededQuantity = LocalRequiredItems[Index].ItemQuantity;
            bDoesNotContainItems = true; // Missing all items
            LocalItemsInInventory.Add(NewItem);
            continue; // Move to the next required item
        }

        for (int32 LocalItemIndex = 0; LocalItemIndex < LocalItemsArray.Num(); ++LocalItemIndex)
        {
            if (LocalItemsArray[LocalItemIndex].ItemID == LocalRequiredItems[Index].ItemID)
            {
                bLocalFound = true;

                FItemRecipeInfo NewItem;
                NewItem.ItemID = LocalRequiredItems[Index].ItemID;
                NewItem.ItemIcon = LocalRequiredItems[Index].ItemIcon;
                NewItem.ItemName = LocalRequiredItems[Index].ItemName;
                NewItem.CurrentQuantity = LocalItemsArray[LocalItemIndex].ItemQuantity;
                NewItem.NeededQuantity = LocalRequiredItems[Index].ItemQuantity;

                if (LocalItemsArray[LocalItemIndex].ItemQuantity < LocalRequiredItems[Index].ItemQuantity)
                {
                    bDoesNotContainItems = true; // Not enough items to craft
                }

                LocalItemsInInventory.Add(NewItem);
                break; // Exit loop once item is found and processed
            }
        }

        if (!bLocalFound)
        {
            // Item is not in the inventory
            FItemRecipeInfo NewItem;
            NewItem.ItemID = LocalRequiredItems[Index].ItemID;
            NewItem.ItemIcon = LocalRequiredItems[Index].ItemIcon;
            NewItem.ItemName = LocalRequiredItems[Index].ItemName;
            NewItem.CurrentQuantity = 0;
            NewItem.NeededQuantity = LocalRequiredItems[Index].ItemQuantity;
            bDoesNotContainItems = true; // Missing required item
            LocalItemsInInventory.Add(NewItem);
        }
    }

    LocalItems = LocalItemsInInventory;
    bCanCraft = !bDoesNotContainItems; // Can craft if no missing or insufficient items
}







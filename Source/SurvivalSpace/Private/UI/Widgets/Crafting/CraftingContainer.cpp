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
	CraftingType = ItemCraftingType;

	Grid->ClearChildren();

	Slots.Empty();

	AddSlots(ItemCraftingType, ItemArray, false);
	
}


void UCraftingContainer::AddSlots(ECraftingType InCraftingType, TArray<FItem> ItemArray, bool bAdminMode)
{
    TArray<FItem> LocalItemArray = ItemArray;
    FName PathName;
    
    switch (InCraftingType)
    {
    case ECraftingType::PlayerInventory:
        PathName = "/Game/_Main/DataAssets/ItemRecipes/PlayerInventory";
        break;
    case ECraftingType::CookingPot:
        PathName = "/Game/CookingPotPath";
        break;
    case ECraftingType::CraftingBench:
        PathName = "/Game/CraftingBenchPath"; 
        break;
    case ECraftingType::SmeltingForge:
        PathName = "/Game/SmeltingForgePath";
        break;
    case ECraftingType::AdvancedWorkBench:
        PathName = "/Game/AdvancedWorkBenchPath";
        break;
    case ECraftingType::StorageBox:
        PathName = "/Game/StorageBoxPath";
        break;
    case ECraftingType::CropPlot:
        PathName = "/Game/CropPlotPath";
        break;
    default:
        PathName = "/Game/DefaultPath";
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
            IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();
            
            TArray<FAssetData> LocalDataAssets;
            
            bool bRecursive = true;
            
            AssetRegistry.GetAssetsByPath(PathName, LocalDataAssets, bRecursive);
            
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
        }
        break;
    case ECraftingType::CookingPot:
        break;
    case ECraftingType::CraftingBench:
        break;
    case ECraftingType::SmeltingForge:
        break;
    case ECraftingType::AdvancedWorkBench:
        break;
    case ECraftingType::StorageBox:
        break;
    case ECraftingType::CropPlot:
        break;
    }
}

void UCraftingContainer::AddSlotsToGrid(int32 Index, UCraftingRecipeSlot* InSlot)
{
    //int32 LocalSlotIndex = Index;
    //UCraftingRecipeSlot* LocalCraftingSlot = InSlot;

    UUniformGridSlot* GridSlot = Grid->AddChildToUniformGrid(InSlot);
    if (!GridSlot)
    {
        return;
    }
    
    int32 SlotsPerRowValue = SlotsPerRow;
    
    double LocalSlotIndexAsDouble = UKismetMathLibrary::Conv_IntToDouble(Index);
    double SlotsPerRowAsDouble = UKismetMathLibrary::Conv_IntToDouble(SlotsPerRowValue);

    double Remainder;
    int32 ReturnValue = UKismetMathLibrary::FMod(LocalSlotIndexAsDouble, SlotsPerRowAsDouble, Remainder);
    int32 Column = UKismetMathLibrary::FTrunc(Remainder);
    int32 Row = UKismetMathLibrary::FTrunc(ReturnValue);
    
    GridSlot->SetRow(Row);
    GridSlot->SetColumn(Column);
}

void UCraftingContainer::CheckCraftableItem(TArray<FItemRecipes> RequiredItems, TArray<FItem> ItemsArray,
    bool& bCanCraft, TArray<FItemRecipeInfo>& LocalItems)
{
    TArray<FItemRecipes> LocalRequiredItems = RequiredItems;
    TArray<FItem> LocalItemsArray = ItemsArray;
    TArray<FItemRecipeInfo> LocalItemsInInventory;

    bool bDoesNotContainItems = false;

    for (int32 Index = 0; Index < LocalRequiredItems.Num(); ++Index)
    {
        bool bLocalFound = false; 

        if (LocalItemsArray.Num() == 0)
        {
            FItemRecipeInfo NewItem;
            NewItem.ItemID = LocalRequiredItems[Index].ItemID;
            NewItem.ItemIcon = LocalRequiredItems[Index].ItemIcon;
            NewItem.ItemName = LocalRequiredItems[Index].ItemName;
            NewItem.CurrentQuantity = 0;
            NewItem.NeededQuantity = LocalRequiredItems[Index].ItemQuantity;
            bDoesNotContainItems = true;
            LocalItemsInInventory.Add(NewItem);
            continue;
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
                    bDoesNotContainItems = true;
                }

                LocalItemsInInventory.Add(NewItem);
                break;
            }
        }

        if (!bLocalFound)
        {
            FItemRecipeInfo NewItem;
            NewItem.ItemID = LocalRequiredItems[Index].ItemID;
            NewItem.ItemIcon = LocalRequiredItems[Index].ItemIcon;
            NewItem.ItemName = LocalRequiredItems[Index].ItemName;
            NewItem.CurrentQuantity = 0;
            NewItem.NeededQuantity = LocalRequiredItems[Index].ItemQuantity;
            bDoesNotContainItems = true;
            LocalItemsInInventory.Add(NewItem);
        }
    }

    LocalItems = LocalItemsInInventory;
    bCanCraft = !bDoesNotContainItems;
}







// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.


#include "UI/Widgets/Crafting/CraftingSlot.h"

#include "Components/Border.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "DataAssets/PrimaryAssets/ItemInfo.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "UI/Widgets/Crafting/CraftingItemContainerGrid.h"

void UCraftingSlot::NativeOnHovered()
{
    Super::NativeOnHovered();

    ItemHoverBorder->SetVisibility(ESlateVisibility::Visible);
    
}

void UCraftingSlot::NativeOnUnhovered()
{
    Super::NativeOnUnhovered();

    ItemHoverBorder->SetVisibility(ESlateVisibility::Hidden);
    
}

FReply UCraftingSlot::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
    if (IsValid(Parent))
    {
        Parent->DesiredSlotToFocus = ItemIndex;
        return FReply::Handled();
    }

    return Super::NativeOnFocusReceived(InGeometry, InFocusEvent);
}

void UCraftingSlot::UpdateSlot(FItemStructure ItemInfo)
{
	// Update ItemInfoData
	ItemInfoData = ItemInfo;

	// Update bHasItemInSlot based on whether ItemInfo is valid (assuming it is valid if ItemID is not zero)
	bHasItemInSlot = ItemInfo.ItemID != 0;

	// Load ItemAsset asynchronously
	if (ItemInfo.ItemAsset.ToSoftObjectPath().IsValid())
	{
		FStreamableManager& AssetLoader = UAssetManager::GetStreamableManager();
		AssetLoader.RequestAsyncLoad(ItemInfo.ItemAsset.ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this, &UCraftingSlot::OnItemAssetLoaded, ItemInfo.ItemAsset.ToSoftObjectPath(), ItemInfo));
	}
	else
	{
		ItemAssetInfo = nullptr;
	}
}

void UCraftingSlot::OnItemAssetLoaded(FSoftObjectPath AssetPath, FItemStructure ItemInfo)
{
	UObject* LoadedAsset = AssetPath.ResolveObject();

    if (LoadedAsset)
    {
        ItemAssetInfo = Cast<UItemInfo>(LoadedAsset);
        if (ItemAssetInfo)
        {
            // Successfully loaded item asset
            if (ItemIcon && ItemNameText && ItemAssetInfo->ItemIcon)
            {
                ItemIcon->SetBrushFromTexture(ItemAssetInfo->ItemIcon);
                ItemNameText->SetText(ItemAssetInfo->ItemName);
                ItemIcon->SetVisibility(ESlateVisibility::Visible);
                ItemNameText->SetVisibility(ESlateVisibility::Visible);
            }

            switch (ItemAssetInfo->ItemType) 
            {
            case EItemType::Resource:
                {
                    // Formated Text for Quantity
                    FFormatNamedArguments Args;
                    Args.Add(TEXT("Quantity"), FText::AsNumber(ItemInfo.ItemQuantity));
                    FText FormattedTextQuantity = FText::Format(NSLOCTEXT("InventorySlot", "QuantityFormat", "x{Quantity}"), Args);
                    if (QuantityText)
                    {
                        QuantityText->SetText(FormattedTextQuantity);
                        QuantityText->SetVisibility(ESlateVisibility::Visible);
                    }
                    break;
                }
            case EItemType::Equippable:
                {
                    break;
                }
            case EItemType::Armor:
                {

                    break;
                }
            case EItemType::Consumable:
                {
                    break;
                }
            case EItemType::Buildable:
                {
                    break;
                }
            default:
                break;
            }
        }
    }
}

void UCraftingSlot::ResetSlot()
{
    ItemIcon->SetVisibility(ESlateVisibility::Hidden);
    ItemNameText->SetVisibility(ESlateVisibility::Hidden);
    QuantityText->SetVisibility(ESlateVisibility::Hidden);
    bHasItemInSlot = false;
    ItemInfoData = FItemStructure();
}

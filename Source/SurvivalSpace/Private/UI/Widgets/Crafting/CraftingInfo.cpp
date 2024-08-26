// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.


#include "UI/Widgets/Crafting/CraftingInfo.h"


#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "DataAssets/PrimaryAssets/ItemInfo.h"
#include "UI/Widgets/Crafting/CraftItemResource.h"

void UCraftingInfo::SetupWidgetData()
{
	ItemName->SetText(ItemNameText);
	ItemIcon->SetBrushFromTexture(ItemIconTexture);
	
	if (ItemAsset.ToSoftObjectPath().IsValid())
	{
		UItemInfo* LoadedAsset = ItemAsset.LoadSynchronous();

		if (LoadedAsset)
		{
			FText ItemType = StaticEnum<EItemType>()->GetDisplayValueAsText(LoadedAsset->ItemType);
			ItemTypeText->SetText(ItemType);
			ItemDescription->SetText(LoadedAsset->ItemDescription);
		}
	}

	for (int32 Index = 0; Index < RequiredItems.Num(); ++Index)
	{
		if (RequiredItems[Index].ItemIcon.ToSoftObjectPath().IsValid())
		{
			UTexture2D* LoadedIcon = RequiredItems[Index].ItemIcon.LoadSynchronous();

			if (LoadedIcon)
			{
				if (CraftItemResourceWidgetClass)
				{
					CraftItemResourceWidget = CreateWidget<UCraftItemResource>(GetWorld(), CraftItemResourceWidgetClass);

					if (CraftItemResourceWidget)
					{
						CraftItemResourceWidget->ResourceIconTexture = LoadedIcon;
						CraftItemResourceWidget->ItemNameText = RequiredItems[Index].ItemName;
						CraftItemResourceWidget->ResourceCurrentAmount = RequiredItems[Index].CurrentQuantity;
						CraftItemResourceWidget->ResourceNeededAmount = RequiredItems[Index].NeededQuantity;
						CraftItemResourceWidget->ResourceAmount = FMath::Clamp(static_cast<float>(RequiredItems[Index].CurrentQuantity) / static_cast<float>(RequiredItems[Index].NeededQuantity), 0.0f, 1.0f);
						ResourceBox->AddChild(CraftItemResourceWidget);
					}
				}
			}
		}
	}
}

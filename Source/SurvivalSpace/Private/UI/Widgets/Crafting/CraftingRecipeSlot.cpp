// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.


#include "UI/Widgets/Crafting/CraftingRecipeSlot.h"

#include "Components/SizeBox.h"
#include "DataAssets/PrimaryAssets/ItemRecipe.h"
#include "UI/Widgets/Crafting/CraftingInfo.h"


void UCraftingRecipeSlot::NativeOnHovered()
{
	Super::NativeOnHovered();

	if (CraftingInfoWidgetClass)
	{
		CraftingInfoWidget = CreateWidget<UCraftingInfo>(GetWorld(), CraftingInfoWidgetClass);

		if (CraftingInfoWidget)
		{
			if (RecipeAsset.ToSoftObjectPath().IsValid())
			{
				UItemRecipe* LoadedAsset = RecipeAsset.LoadSynchronous();

				if (LoadedAsset)
				{
					CraftingInfoWidget->ItemAsset = LoadedAsset->ItemAsset;
					CraftingInfoWidget->ItemIconTexture = ItemIconTexture;
					CraftingInfoWidget->ItemNameText = ItemName;
					CraftingInfoWidget->RequiredItems = RequiredItems;
					CraftingInfoWidget->SetupWidgetData();
					SizeBox->SetToolTip(CraftingInfoWidget);
				}
			}
		}
	}


}

void UCraftingRecipeSlot::NativeOnUnhovered()
{
	Super::NativeOnUnhovered();

	SizeBox->SetToolTip(nullptr);

}

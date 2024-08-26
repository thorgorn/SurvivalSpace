// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.


#include "UI/Widgets/Crafting/CraftItemResource.h"

#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UCraftItemResource::NativeConstruct()
{
	Super::NativeConstruct();

	ItemResourceIcon->SetBrushFromTexture(ResourceIconTexture);
	ItemName->SetText(ItemNameText);

	FFormatNamedArguments ArgsItemQuantity;
	ArgsItemQuantity.Add(TEXT("Quantity"), FText::AsNumber(ResourceCurrentAmount));
	ArgsItemQuantity.Add(TEXT("Needed"), FText::AsNumber(ResourceNeededAmount));
	FText FormattedTextQuantity = FText::Format(NSLOCTEXT("ItemInfoWidget", "ItemQuantityFormat", "Quantity:{Quantity} of {Needed}"), ArgsItemQuantity);
	ResourceQuantity->SetText(FormattedTextQuantity);
	ResourceProgressBar->SetPercent(ResourceAmount);
}

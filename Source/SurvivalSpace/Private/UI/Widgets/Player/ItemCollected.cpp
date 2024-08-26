// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.


#include "UI/Widgets/Player/ItemCollected.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UItemCollected::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateUI();
	
}

void UItemCollected::UpdateUI()
{
	if (ResourceIcon && ResourceImage)
	{
		ResourceIcon->SetBrushFromTexture(ResourceImage);
	}
	
	if (ItemText)
	{
		FFormatNamedArguments ArgsReturnText;
		ArgsReturnText.Add(TEXT("quantity"), FText::AsNumber(ResourceQuantity));
		ArgsReturnText.Add(TEXT("name"), ResourceName);
		FText FormattedTextName = FText::Format(NSLOCTEXT("InventorySlot", "ReturnFormat", "x{quantity} {name}"), ArgsReturnText);

		ItemText->SetText(FormattedTextName);
	}
}
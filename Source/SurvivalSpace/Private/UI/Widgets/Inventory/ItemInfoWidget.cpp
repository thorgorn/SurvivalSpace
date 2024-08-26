// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.


#include "UI/Widgets/Inventory/ItemInfoWidget.h"

#include "CommonButtonBase.h"
#include "Components/Border.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Interfaces/ControllerInterface.h"
#include "Interfaces/SurvivalCharacterInterface.h"

void UItemInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeItemInfo();

	if (W_ItemDestroyButton)
	{
		W_ItemDestroyButton->OnClicked().AddUObject(this, &UItemInfoWidget::DestroyButtonClicked);
	}
	if (W_ItemTransferButton)
	{
		W_ItemTransferButton->OnClicked().AddUObject(this, &UItemInfoWidget::TransferButtonClicked);
	}
}

void UItemInfoWidget::DestroyButtonClicked()
{
	IControllerInterface* ControllerInterface = Cast<IControllerInterface>(GetOwningPlayer());
	
	if (ControllerInterface)
	{
		ControllerInterface->DestroyItem(ItemIndex);
		ControllerInterface->ShowItemDestroyed(ItemImage, ItemQuantityAmount, ItemNameText);
	}
	DeactivateWidget();
	RemoveFromParent();
	RequestRefreshFocus();
}

void UItemInfoWidget::TransferButtonClicked()
{
	ISurvivalCharacterInterface* CharacterInterface = Cast<ISurvivalCharacterInterface>(GetOwningPlayerPawn());

	if(CharacterInterface)
	{
		CharacterInterface->DoublePressSlot(ItemContainerType, ItemIndex);
		DeactivateWidget();
		this->SetVisibility(ESlateVisibility::Hidden);
		RequestRefreshFocus();
	}
}

void UItemInfoWidget::InitializeItemInfo()
{
	ItemIcon->SetBrushFromTexture(ItemImage);
	ItemName->SetText(ItemNameText);
	FFormatNamedArguments ArgsItemType;
	ArgsItemType.Add(TEXT("type"), ItemTypeText);
	FText FormattedTextItemType = FText::Format(NSLOCTEXT("ItemInfoWidget", "ItemTypeFormat", "{type}"), ArgsItemType);
	ItemType->SetText(FormattedTextItemType);
	ItemRarity->SetText(ItemRarityText);

	switch (ItemRarityType) {
	case EItemRarity::Common:
		ItemRarity->SetColorAndOpacity(Common);
		break;
	case EItemRarity::Uncommon:
		ItemRarity->SetColorAndOpacity(Uncommon);
		break;
	case EItemRarity::Rare:
		ItemRarity->SetColorAndOpacity(Rare);
		break;
	case EItemRarity::Epic:
		ItemRarity->SetColorAndOpacity(Epic);
		break;
	case EItemRarity::Legendary:
		ItemRarity->SetColorAndOpacity(Legendary);
		break;
	}

	ItemDescription->SetText(ItemDescriptionText);

	if (bIsStackable)
	{
		ItemStatsBox->SetVisibility(ESlateVisibility::Collapsed);
		DurabilityBox->SetVisibility(ESlateVisibility::Collapsed);
		FFormatNamedArguments ArgsItemQuantity;
		ArgsItemQuantity.Add(TEXT("Quantity"), FText::AsNumber(ItemQuantityAmount));
		ArgsItemQuantity.Add(TEXT("Stacksize"), FText::AsNumber(ItemStackSize));
		FText FormattedTextQuantity = FText::Format(NSLOCTEXT("ItemInfoWidget", "ItemQuantityFormat", "Quantity:{Quantity} of {Stacksize}"), ArgsItemQuantity);
		ItemQuantity->SetText(FormattedTextQuantity);
		GatherProgress->SetPercent(GatherPercent);
		ItemGatherIcon->SetBrushFromTexture(ItemImage);
		ItemLocation->SetText(ItemLocationText);
		BorderColor->SetBrushFromTexture(BorderTexture);
	}
	else
	{
		GatherBox->SetVisibility(ESlateVisibility::Collapsed);
		ItemLocationBox->SetVisibility(ESlateVisibility::Collapsed);
		FFormatNamedArguments ArgsItemDamage;
		ArgsItemDamage.Add(TEXT("damage"),FText::AsNumber(ItemDamageAmount));
		FText FormattedTextItemDamage = FText::Format(NSLOCTEXT("ItemInfoWidget", "ItemDamageFormat", "Damage: {damage}"), ArgsItemDamage);
		ItemDamage->SetText(FormattedTextItemDamage);
		WeaponImage->SetBrushFromTexture(ItemImage);
		FFormatNamedArguments ArgsItemDurability;
		ArgsItemDurability.Add(TEXT("Current"), FText::AsNumber(ItemCurrentHP));
		ArgsItemDurability.Add(TEXT("Max"), FText::AsNumber(ItemMaxHP));
		FText FormattedTextItemDurability = FText::Format(NSLOCTEXT("ItemInfoWidget", "ItemDurabilityFormat", "Durability:{Current} of {Max}"), ArgsItemDurability);
		ItemDurability->SetText(FormattedTextItemDurability);
		float ItemDurabilityProgressAmount = ItemCurrentHP / ItemMaxHP;
		ItemDurabilityProgress->SetPercent(ItemDurabilityProgressAmount);
		BorderColor->SetBrushFromTexture(BorderTexture);
	}
}

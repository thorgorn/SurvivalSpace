// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.


#include "UI/Widgets/Inventory/DraggedItem.h"

#include "Components/Border.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UDraggedItem::NativeConstruct()
{
	Super::NativeConstruct();

	if (WeightText)
	{
		WeightText->SetText(Weight);
		WeightText->SetVisibility(ESlateVisibility::Visible);
	}

	if (ItemIcon)
	{
		ItemIcon->SetBrushFromTexture(ImageIcon);
		ItemIcon->SetVisibility(ESlateVisibility::Visible);
	}

	switch (ItemType) {
	case EItemType::Resource:
		{
			FFormatNamedArguments Args;
			Args.Add(TEXT("Quantity"), Quantity);
			FText FormattedQuantity = FText::Format(NSLOCTEXT("DraggedItem", "QuantityFormat", "x{Quantity}"), Args);
			if (QuantityText)
			{
				QuantityText->SetText(FormattedQuantity);
				QuantityText->SetVisibility(ESlateVisibility::Visible);
			}
			if (TopText) TopText->SetVisibility(ESlateVisibility::Hidden);
			if (BottomText) BottomText->SetVisibility(ESlateVisibility::Hidden);
			if (ItemHP) ItemHP->SetVisibility(ESlateVisibility::Hidden);
			
			break;
		}
	case EItemType::Equippable:
		{
			// Formated Text for DMG
			FFormatNamedArguments ArgsDMG;
			ArgsDMG.Add(TEXT("ItemDamage"), TextTop);
			FText FormattedTextDamage = FText::Format(NSLOCTEXT("InventorySlot", "DamageFormat", "DMG {ItemDamage}%"), ArgsDMG);

			// Formated Text for Ammo
			FFormatNamedArguments ArgsAmmo;
			ArgsAmmo.Add(TEXT("Current"), CurrentAmmo);
			ArgsAmmo.Add(TEXT("Max"), MaxAmmo);
			FText FormattedTextAmmo = FText::Format(NSLOCTEXT("InventorySlot", "AmmoFormat", "{Current}/{Max}"), ArgsAmmo);
			if (TopText)
			{
				TopText->SetText(FormattedTextDamage);
				TopText->SetVisibility(ESlateVisibility::Visible);
				ItemHP->SetVisibility(ESlateVisibility::Visible);
				float DamagePercent = CurrentHP / MaxHP;
				ItemHP->SetPercent(DamagePercent);
				QuantityText->SetVisibility(ESlateVisibility::Hidden);
                        
				if (bUseAmmo)
				{
					BottomText->SetVisibility(ESlateVisibility::Visible);
					BottomText->SetText(FormattedTextAmmo);
				}
				else
				{
					BottomText->SetVisibility(ESlateVisibility::Hidden);
				}
			}
			break;
		}
	case EItemType::Armor:
		{
			// Formated Text for Armor
			FFormatNamedArguments ArgsArmor;
			ArgsArmor.Add(TEXT("ArmorAmount"), TextTop);
			FText FormattedTextArmor = FText::Format(NSLOCTEXT("InventorySlot", "ArmorFormat", "{ArmorAmount}Armor"), ArgsArmor);
			if (TopText)
			{
				TopText->SetText(FormattedTextArmor);
				TopText->SetVisibility(ESlateVisibility::Visible);
				ItemHP->SetVisibility(ESlateVisibility::Visible);
				float ArmorPercent = CurrentHP / MaxHP;
				ItemHP->SetPercent(ArmorPercent);
				QuantityText->SetVisibility(ESlateVisibility::Hidden);
				BottomText->SetVisibility(ESlateVisibility::Hidden);
			}
			break;
		}
	case EItemType::Consumable:
		{
			// Formated Text for Quantity
			FFormatNamedArguments Args;
			Args.Add(TEXT("Quantity"), Quantity);
			FText FormattedTextQuantity = FText::Format(NSLOCTEXT("InventorySlot", "QuantityFormat", "x{Quantity}"), Args);
			if (QuantityText)
			{
				QuantityText->SetText(FormattedTextQuantity);
				QuantityText->SetVisibility(ESlateVisibility::Visible);
				ItemHP->SetVisibility(ESlateVisibility::Visible);
				float ConsumableAmount = CurrentHP / MaxHP;
				ItemHP->SetPercent(ConsumableAmount);
			}

			if (TopText) TopText->SetVisibility(ESlateVisibility::Hidden);
			if (BottomText) BottomText->SetVisibility(ESlateVisibility::Hidden);
			break;
		}
	case EItemType::Buildable:
		{
			// Formated Text for Quantity
			FFormatNamedArguments Args;
			Args.Add(TEXT("Quantity"), Quantity);
			FText FormattedTextQuantity = FText::Format(NSLOCTEXT("InventorySlot", "QuantityFormat", "x{Quantity}"), Args);
			if (QuantityText)
			{
				QuantityText->SetText(FormattedTextQuantity);
				QuantityText->SetVisibility(ESlateVisibility::Visible);
			}

			if (TopText) TopText->SetVisibility(ESlateVisibility::Hidden);
			if (BottomText) BottomText->SetVisibility(ESlateVisibility::Hidden);
			if (ItemHP) ItemHP->SetVisibility(ESlateVisibility::Hidden);
			break;
		}
	}
}

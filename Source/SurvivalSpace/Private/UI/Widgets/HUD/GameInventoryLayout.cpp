// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/HUD/GameInventoryLayout.h"

#include "Components/Border.h"
#include "Components/WidgetSwitcher.h"
#include "Interfaces/ControllerInterface.h"
#include "UI/Common/Buttons/CommonButton.h"
#include "UI/Widgets/Crafting/Crafting.h"
#include "UI/Widgets/Crafting/CraftingContainer.h"
#include "UI/Widgets/Crafting/CraftingItemContainerGrid.h"
#include "UI/Widgets/Crafting/CraftingProgress.h"
#include "UI/Widgets/Crafting/CraftingRecipeSlot.h"
#include "UI/Widgets/Menu/MenuMaster.h"
#include "UI/Widgets/Menu/WidgetInfo.h"

void UGameInventoryLayout::NativePreConstruct()
{
	Super::NativePreConstruct();

	SwitchWidget(WidgetSwitcher->GetActiveWidgetIndex());
}

void UGameInventoryLayout::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (CloseInventoryButton)
	{
		CloseInventoryButton->OnClicked().AddUObject(this, &UGameInventoryLayout::InventoryButtonClicked);
	}
}

void UGameInventoryLayout::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();

	if (APlayerController* PlayerController = GetOwningPlayer())
	{
		IControllerInterface* ControllerInterface = Cast<IControllerInterface>(PlayerController);
		if (ControllerInterface)
		{
			ControllerInterface->CloseInventory();
		}
	}
}

void UGameInventoryLayout::InventoryButtonClicked()
{
	DeactivateWidget();
	WidgetSwitcher->SetActiveWidgetIndex(0);
}

void UGameInventoryLayout::UpdateCraftWidget(ECraftingType CraftingType, TArray<FSimpleItemStructure> ItemArray)
{
	switch (CraftingType) {
	case ECraftingType::PlayerInventory:
		CraftingWidget->CraftingContainerGrid->UpdateSlots(CraftingType, ItemArray);
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

void UGameInventoryLayout::ShowCraftingProgress(FText ItemName)
{
	if (CraftingProgressWidget)
	{
		CraftingProgressWidget->SetVisibility(ESlateVisibility::Visible);
		CraftingProgressWidget->CraftItem(ItemName);
		GetWorld()->GetTimerManager().SetTimer(DelayHideCraftProgress, this, &UGameInventoryLayout::HideCraftProgressWidget, 3.0f, false);
	}
}

void UGameInventoryLayout::HideCraftProgressWidget()
{
	CraftingProgressWidget->SetVisibility(ESlateVisibility::Hidden);
}

void UGameInventoryLayout::SwitchWidget(const int32 WidgetIndex)
{
	if (!WidgetSwitcher || !MenuMasterWidget || !WidgetInfoWidget)
	{
		return;
	}

	switch (WidgetIndex)
	{
	case 0:
		ActivateWidget(0, "Inventory", "Manage your items and containers here");
		SetButtonVisibility(MenuMasterWidget->InventoryButton);
		break;
	case 1:
		ActivateWidget(1, "EQUIPMENT", "Equip Items and manage your character");
		SetButtonVisibility(MenuMasterWidget->EquipmentButton);
		break;
	case 2:
		WidgetSwitcher->SetActiveWidgetIndex(2);
		CraftingWidget->CraftingContainerGrid->InitializeSlots();
		SetButtonVisibility(MenuMasterWidget->CraftingButton);
		UpdateWidgetText("CRAFTING", "Craft your items and manage resources");
		GetDesiredFocusTarget()->SetFocus();
		break;
	case 3:
	case 4:
	case 5:
		WidgetSwitcher->SetActiveWidgetIndex(WidgetIndex);
		break;
	default:
		break;
	}
}

void UGameInventoryLayout::ActivateWidget(int32 Index, const FString& Name, const FString& Description)
{
	WidgetSwitcher->SetActiveWidgetIndex(Index);
	UpdateWidgetText(Name, Description);
	GetDesiredFocusTarget()->SetFocus();
}

void UGameInventoryLayout::UpdateWidgetText(const FString& Name, const FString& Description)
{
	FText WidgetName = FText::FromString(Name);
	FText WidgetDescription = FText::FromString(Description);
	WidgetInfoWidget->UpdateText(WidgetName, WidgetDescription);
}

void UGameInventoryLayout::SetButtonVisibility(UCommonButton* ActiveButton)
{
	if (!MenuMasterWidget) return;

	MenuMasterWidget->InventoryButton->SelectedImage->SetVisibility(ESlateVisibility::Hidden);
	MenuMasterWidget->EquipmentButton->SelectedImage->SetVisibility(ESlateVisibility::Hidden);
	MenuMasterWidget->CraftingButton->SelectedImage->SetVisibility(ESlateVisibility::Hidden);

	if (ActiveButton && ActiveButton->SelectedImage)
	{
		ActiveButton->SelectedImage->SetVisibility(ESlateVisibility::Visible);
	}
}


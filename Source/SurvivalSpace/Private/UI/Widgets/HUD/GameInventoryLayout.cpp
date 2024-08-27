// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/HUD/GameInventoryLayout.h"

#include "Components/WidgetSwitcher.h"
#include "Interfaces/ControllerInterface.h"
#include "UI/Common/Buttons/CommonButton.h"
#include "UI/Widgets/Crafting/Crafting.h"
#include "UI/Widgets/Crafting/CraftingContainer.h"
#include "UI/Widgets/Crafting/CraftingItemContainerGrid.h"
#include "UI/Widgets/Crafting/CraftingRecipeSlot.h"

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


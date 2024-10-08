// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/HUD/DefaultHUDLayout.h"

#include "Components/VerticalBox.h"
#include "UI/Widgets/Player/ItemCollected.h"

void UDefaultHUDLayout::AddResource(UTexture2D* Icon, int32 Quantity, FText ItemName)
{
	if (ItemCollectedWidgetClass)
	{
		ItemCollectedWidget = CreateWidget<UItemCollected>(GetWorld(), ItemCollectedWidgetClass);
		
		if (ItemCollectedWidget)
		{
			ItemCollectedWidget->ResourceImage = Icon;
			ItemCollectedWidget->ResourceQuantity = Quantity;
			ItemCollectedWidget->ResourceName = ItemName;

			ItemCollectedWidget->UpdateUI();

			ResourcesCollected->AddChild(ItemCollectedWidget);
		}
	}
}

void UDefaultHUDLayout::RemoveResource(UTexture2D* Icon, int32 Quantity, FText ItemName)
{
	if (ItemDestroyedWidgetClass)
	{
		ItemDestroyedWidget = CreateWidget<UItemCollected>(GetWorld(), ItemDestroyedWidgetClass);
		
		if (ItemDestroyedWidget)
		{
			ItemDestroyedWidget->ResourceImage = Icon;
			ItemDestroyedWidget->ResourceQuantity = Quantity;
			ItemDestroyedWidget->ResourceName = ItemName;

			ItemDestroyedWidget->UpdateUI();

			ResourcesCollected->AddChild(ItemDestroyedWidget);
		}
	}
}


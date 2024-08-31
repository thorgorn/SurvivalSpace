// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/ControllerInterface.h"

// Add default functionality here for any IControllerInterface functions that are not pure virtual.
void IControllerInterface::CloseInventory()
{
}

void IControllerInterface::UpdateItemSlot(EContainerType Container, int32 Index, FItemStructure ItemInfo)
{
}

void IControllerInterface::ResetItemSlot(EContainerType Container, int32 Index)
{
}

void IControllerInterface::ShowItemCollected(UTexture2D* ResourceImage, int32 ResourceQuantity, FText ResourceName)
{
}

void IControllerInterface::ShowItemDestroyed(UTexture2D* ResourceImage, int32 ResourceQuantity, FText ResourceName)
{
}

void IControllerInterface::DestroyItem(int32 Index)
{
}

void IControllerInterface::SetFocusInventory()
{
}

void IControllerInterface::SetSelectedItem(EContainerType ContainerType, int32 SelectedIndex, bool ItemInFirstSlot,
	EArmorType ArmorType)
{
}

void IControllerInterface::UpdateCraftItemSlot(EContainerType Container, int32 Index, FItemStructure ItemInfo)
{
}

void IControllerInterface::ResetCraftItemSlot(EContainerType Container, int32 Index)
{
}

void IControllerInterface::UpdateCraftResourceUI()
{
}

void IControllerInterface::SetupCraftableItems(ECraftingType CraftingType, TArray<FSimpleItemStructure> ItemArray)
{
}

void IControllerInterface::DisplayCraftProgress(FText ItemName)
{
}




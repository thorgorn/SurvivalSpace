// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/SurvivalCharacterInterface.h"


void ISurvivalCharacterInterface::GetAnimationStates(ECharacterStates& OutCurrentState, EEquippableState& OutEquippableState)
{
}

void ISurvivalCharacterInterface::UpdateItem(EContainerType Container, int32 Index, FItemStructure ItemInfo)
{
}

void ISurvivalCharacterInterface::OnSlotDrop(EContainerType TargetContainer, EContainerType FromContainer,
	int32 FromIndex, int32 DroppedIndex, EArmorType ArmorType)
{
}

void ISurvivalCharacterInterface::ResetItem(EContainerType Container, int32 Index)
{
	
}

void ISurvivalCharacterInterface::ThirdPersonMontage(UAnimMontage* Montage)
{
}

void ISurvivalCharacterInterface::HarvestItem(FItemStructure Resource)
{
}

void ISurvivalCharacterInterface::DestroyItem(int32 Index)
{
}

void ISurvivalCharacterInterface::GetHitFXInfo(FVector HitLocation, EResourceType ResourceType)
{
}

void ISurvivalCharacterInterface::DoublePressSlot(EContainerType ContainerType, int32 Index)
{
}

void ISurvivalCharacterInterface::GetCharRef(TObjectPtr<AASurvivalCharacter> &CharRef)
{
}

void ISurvivalCharacterInterface::UpdateCraftItem(EContainerType Container, int32 Index, FItemStructure ItemInfo)
{
}

void ISurvivalCharacterInterface::ResetCraftItem(EContainerType Container, int32 Index)
{
}

void ISurvivalCharacterInterface::UpdateCraftResourcesUI()
{
}

void ISurvivalCharacterInterface::GetCraftingRecipesAndItems(ECraftingType CraftingType)
{
}

void ISurvivalCharacterInterface::CraftItem(TSoftObjectPtr<UItemRecipe> RecipeAsset, EContainerType ContainerType,
	ECraftingType CraftingType)
{
}

void ISurvivalCharacterInterface::ShowCraftProgress()
{
}




// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.


#include "Interfaces/LargeItemInterface.h"

// Add default functionality here for any ILargeItemInterface functions that are not pure virtual.
void ILargeItemInterface::GetLargeItemHealth(float& OutHealth)
{
}

void ILargeItemInterface::UpdateLargeItemHealth(float InHealth)
{
}

void ILargeItemInterface::GetLargeResources(TSoftObjectPtr<UHarvestingResource> &OutResources)
{
}

void ILargeItemInterface::GetResourceType(EResourceType& OutResourceType)
{
}

void ILargeItemInterface::HarvestFoliage(float Damage, EHarvestingToolType ToolType, EToolTier ToolTier, AActor* CharacterRef)
{
}

void ILargeItemInterface::CalculateResources(TArray<FResourceStructure> InGivenResources, float LocalDamage, EHarvestingToolType ToolType, EToolTier ToolTier, AActor* CharacterRef)
{
}

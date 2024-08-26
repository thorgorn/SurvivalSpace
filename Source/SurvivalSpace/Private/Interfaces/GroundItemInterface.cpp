// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.


#include "Interfaces/GroundItemInterface.h"

// Add default functionality here for any IGroundItemInterface functions that are not pure virtual.
void IGroundItemInterface::GetResourceHealth(float& OutHealth)
{
}

void IGroundItemInterface::UpdateHealth(const float NewHealth)
{
}

void IGroundItemInterface::GetGivenResources(TSoftObjectPtr<UHarvestingResource>& OutResources)
{
}

void IGroundItemInterface::GetResourceType(EResourceType &OutResourceType)
{
}

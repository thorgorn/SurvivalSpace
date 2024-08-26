// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.


#include "HarvestingSystem/GroundItemMaster.h"

void AGroundItemMaster::GetGivenResources(TSoftObjectPtr<UHarvestingResource>& OutResources)
{
	OutResources = Resources;
}

void AGroundItemMaster::UpdateHealth(const float NewHealth)
{
	Health = NewHealth;
}

void AGroundItemMaster::GetResourceHealth(float& OutHealth)
{
	OutHealth = Health;
}

void AGroundItemMaster::GetResourceType(EResourceType &OutResourceType)
{
	OutResourceType = ResourceType;
}

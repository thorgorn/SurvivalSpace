// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.


#include "HarvestingSystem/HarvestingMaster.h"


AHarvestingMaster::AHarvestingMaster()
{
	bReplicates = true;

	// Disable ticking by default
	PrimaryActorTick.bCanEverTick = true; // Ensures the actor can tick if needed
	PrimaryActorTick.bStartWithTickEnabled = false; // Disable tick at the start
}

void AHarvestingMaster::BeginPlay()
{
	Super::BeginPlay();
}
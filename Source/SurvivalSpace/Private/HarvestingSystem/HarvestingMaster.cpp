// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.


#include "HarvestingSystem/HarvestingMaster.h"


AHarvestingMaster::AHarvestingMaster()
{
	bReplicates = true;
	
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void AHarvestingMaster::BeginPlay()
{
	Super::BeginPlay();
}
// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.


#include "HarvestingSystem/DestructableHarvestableMaster.h"

#include "Net/UnrealNetwork.h"

ADestructableHarvestableMaster::ADestructableHarvestableMaster()
{
	bReplicates = true;

	// Disable ticking by default
	PrimaryActorTick.bCanEverTick = true; 
	PrimaryActorTick.bStartWithTickEnabled = false;

}

void ADestructableHarvestableMaster::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADestructableHarvestableMaster, Direction);
}

void ADestructableHarvestableMaster::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADestructableHarvestableMaster::UpdateDirection(const FVector& NewDirection)
{
	Direction = NewDirection;
}


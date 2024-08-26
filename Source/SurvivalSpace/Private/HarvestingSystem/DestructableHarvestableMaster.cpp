// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.


#include "HarvestingSystem/DestructableHarvestableMaster.h"

#include "Net/UnrealNetwork.h"

ADestructableHarvestableMaster::ADestructableHarvestableMaster()
{
	bReplicates = true;

	// Disable ticking by default
	PrimaryActorTick.bCanEverTick = true; // Ensures the actor can tick if needed
	PrimaryActorTick.bStartWithTickEnabled = true; // Disable tick at the start

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


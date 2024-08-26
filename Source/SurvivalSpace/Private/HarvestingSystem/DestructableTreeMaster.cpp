// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.


#include "HarvestingSystem/DestructableTreeMaster.h"

#include "Components/CapsuleComponent.h"


ADestructableTreeMaster::ADestructableTreeMaster()
{
}

void ADestructableTreeMaster::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		if (FallForceCapsule)
		{
			AddFallForce(FallForceCapsule);
			GetWorld()->GetTimerManager().SetTimer(DelayFallenDestroyActor, this, &ADestructableTreeMaster::DelayDestroyActor, 15.0f, false);
		}
	}
	else
	{
		if (FallForceCapsule)
		{
			AddFallForce(FallForceCapsule);
		}
	}
}

void ADestructableTreeMaster::AddFallForce(UCapsuleComponent* Capsule)
{
	FVector ForceAmount = Direction * Force;
	
	FName BoneName = NAME_None;
	
	Capsule->AddForce(ForceAmount, BoneName, true);
}

void ADestructableTreeMaster::DelayDestroyActor()
{
	Destroy();
}

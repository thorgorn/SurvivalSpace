// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.

#pragma once

#include "CoreMinimal.h"
#include "HarvestingSystem/DestructableHarvestableMaster.h"
#include "DestructableTreeMaster.generated.h"

class UCapsuleComponent;
/**
 * 
 */
UCLASS()
class SURVIVALSPACE_API ADestructableTreeMaster : public ADestructableHarvestableMaster
{
	GENERATED_BODY()

public:
	//--------------------------------------------------------------------------------------------
	// DESTRUCTABLE TREE MASTER CONSTRUCTOR
	//--------------------------------------------------------------------------------------------

	ADestructableTreeMaster();

protected:

	//--------------------------------------------------------------------------------------------
	// DESTRUCTABLE TREE MASTER FUNCTIONS
	//--------------------------------------------------------------------------------------------

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, Category = "Destructable TreeMaster Functions")
	void AddFallForce(UCapsuleComponent* Capsule);

	UFUNCTION()
	void DelayDestroyActor();

	//--------------------------------------------------------------------------------------------
	// DESTRUCTABLE TREE MASTER PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(EditAnywhere ,BlueprintReadWrite, Category = "Destructable TreeMaster Data")
	TObjectPtr<UCapsuleComponent> FallForceCapsule;
	
	UPROPERTY()
	float Force = 1500.0f;

	UPROPERTY()
	FTimerHandle DelayFallenDestroyActor;
};

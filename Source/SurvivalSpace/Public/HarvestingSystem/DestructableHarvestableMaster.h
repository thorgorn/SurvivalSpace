// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/DestructableHarvestableInterface.h"
#include "DestructableHarvestableMaster.generated.h"

UCLASS()
class SURVIVALSPACE_API ADestructableHarvestableMaster : public AActor, public IDestructableHarvestableInterface
{
	GENERATED_BODY()
	
public:	

	//--------------------------------------------------------------------------------------------
	// DESTRUCTABLEHARVESTABLEMASTER CONSTRUCTOR
	//--------------------------------------------------------------------------------------------
	ADestructableHarvestableMaster();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//--------------------------------------------------------------------------------------------
	// DESTRUCTABLEHARVESTABLEMASTER PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Destructable Data", meta = (ExposeOnSpawn))
	FVector Direction;

protected:

	//--------------------------------------------------------------------------------------------
	// DESTRUCTABLEHARVESTABLEMASTER FUNCTIONS
	//--------------------------------------------------------------------------------------------
	virtual void BeginPlay() override;

	//--------------------------------------------------------------------------------------------
	// DESTRUCTABLEHARVESTABLEMASTER INTERFACE FUNCTIONS
	//--------------------------------------------------------------------------------------------

	virtual void UpdateDirection(const FVector& NewDirection) override;
};
	

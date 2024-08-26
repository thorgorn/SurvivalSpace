// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HarvestingMaster.generated.h"

class UHarvestingResource;

UCLASS()
class SURVIVALSPACE_API AHarvestingMaster : public AActor
{
	GENERATED_BODY()
	
public:	
	//--------------------------------------------------------------------------------------------
	// HARVESTING MASTER CONSTRUCTOR
	//--------------------------------------------------------------------------------------------
	
	AHarvestingMaster();

protected:
	//--------------------------------------------------------------------------------------------
	// HARVESTING MASTER PROTECTED FUNCTIONS
	//--------------------------------------------------------------------------------------------
	
	virtual void BeginPlay() override;
	
	//--------------------------------------------------------------------------------------------
	// HARVESTING MASTER PROTECTED PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvestable Data")
	TSoftObjectPtr<UHarvestingResource> Resources;

};

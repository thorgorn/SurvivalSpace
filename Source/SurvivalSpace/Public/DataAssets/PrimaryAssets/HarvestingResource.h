// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Structs/Structs.h"
#include "HarvestingResource.generated.h"

class ADestructableHarvestableMaster;
/**
 * 
 */
UCLASS()
class SURVIVALSPACE_API UHarvestingResource : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------------------------
	// DATA ASSET HARVESTING RESOURCE PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "ResourceInfo")
	TArray<FResourceStructure> GivenItems;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "ResourceInfo")
	TSoftClassPtr<ADestructableHarvestableMaster> DestructableClass;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "ResourceInfo|VFX&SFX")
	TArray<FResourceEffects> ResourceEffectsArray;
};

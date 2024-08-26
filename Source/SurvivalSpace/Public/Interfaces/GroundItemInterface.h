// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enums/Enums.h"
#include "GroundItemInterface.generated.h"

class UHarvestingResource;
// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable)
class UGroundItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SURVIVALSPACE_API IGroundItemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable)
	virtual void GetResourceHealth(float& OutHealth);

	UFUNCTION(BlueprintCallable)
	virtual void UpdateHealth(const float NewHealth);

	UFUNCTION(BlueprintCallable)
	virtual void GetGivenResources(TSoftObjectPtr<UHarvestingResource>& OutResources);

	UFUNCTION(BlueprintCallable)
	virtual void GetResourceType(EResourceType &OutResourceType);
};

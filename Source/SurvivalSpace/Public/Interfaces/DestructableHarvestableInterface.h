// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DestructableHarvestableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable)
class UDestructableHarvestableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SURVIVALSPACE_API IDestructableHarvestableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable)
	virtual void UpdateDirection(const FVector& NewDirection);
};

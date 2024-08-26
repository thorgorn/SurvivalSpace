// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.

#pragma once

#include "CoreMinimal.h"
#include "Enums/Enums.h"
#include "Structs/Structs.h"
#include "UObject/Interface.h"
#include "LargeItemInterface.generated.h"

class UHarvestingResource;
// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable)
class ULargeItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SURVIVALSPACE_API ILargeItemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable)
	virtual void GetLargeItemHealth(float& OutHealth);

	UFUNCTION(BlueprintCallable)
	virtual void UpdateLargeItemHealth(float InHealth);

	UFUNCTION(BlueprintCallable)
	virtual void GetLargeResources(TSoftObjectPtr<UHarvestingResource> &OutResources);

	UFUNCTION(BlueprintCallable)
	virtual void GetResourceType(EResourceType &OutResourceType);

	UFUNCTION(BlueprintCallable)
	virtual void HarvestFoliage(float Damage, EHarvestingToolType ToolType, EToolTier ToolTier, AActor* CharacterRef);

	UFUNCTION(BlueprintCallable)
	virtual void CalculateResources(TArray<FResourceStructure> InGivenResources, float LocalDamage, EHarvestingToolType ToolType, EToolTier ToolTier, AActor* CharacterRef);
};

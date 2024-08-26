// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.

#pragma once

#include "CoreMinimal.h"
#include "HarvestingSystem/HarvestingMaster.h"
#include "Interfaces/GroundItemInterface.h"
#include "Interfaces/InteractableInterface.h"
#include "GroundItemMaster.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALSPACE_API AGroundItemMaster : public AHarvestingMaster, public IGroundItemInterface, public IInteractableInterface
{
	GENERATED_BODY()

protected:

	//--------------------------------------------------------------------------------------------
	// GROUND ITEM MASTER INTERFACE FUNCTIONS
	//--------------------------------------------------------------------------------------------

	virtual void GetGivenResources(TSoftObjectPtr<UHarvestingResource>& OutResources) override;
	virtual void UpdateHealth(const float NewHealth) override;
	virtual void GetResourceHealth(float& OutHealth) override;
	virtual void GetResourceType(EResourceType &OutResourceType) override;
	
	//--------------------------------------------------------------------------------------------
	// GROUND ITEM MASTER PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties")
	float Health = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties")
	EResourceType ResourceType;
};

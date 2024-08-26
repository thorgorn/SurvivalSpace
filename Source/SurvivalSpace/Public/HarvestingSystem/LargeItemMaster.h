// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.

#pragma once

#include "CoreMinimal.h"
#include "Enums/Enums.h"
#include "HarvestingSystem/HarvestingMaster.h"
#include "Interfaces/LargeItemInterface.h"
#include "LargeItemMaster.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALSPACE_API ALargeItemMaster : public AHarvestingMaster, public ILargeItemInterface
{
	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------------------------
	// LARGE ITEM MASTER CONSTRUCTOR
	//--------------------------------------------------------------------------------------------

	ALargeItemMaster();
	
protected:

	//--------------------------------------------------------------------------------------------
	// LARGE ITEM MASTER FUNCTIONS
	//--------------------------------------------------------------------------------------------
	UFUNCTION(BlueprintImplementableEvent, Category = "Large ItemMaster Functions")
	void FoliageDestroyed(float Damage, EHarvestingToolType ToolType, EToolTier ToolTier, AActor* CharacterRef);
	//--------------------------------------------------------------------------------------------
	// LARGE ITEM MASTER INTERFACE FUNCTIONS
	//--------------------------------------------------------------------------------------------
	
	virtual void GetLargeItemHealth(float& OutHealth) override;
	virtual void UpdateLargeItemHealth(float InHealth) override;
	virtual void GetLargeResources(TSoftObjectPtr<UHarvestingResource> &OutResources) override;
	virtual void GetResourceType(EResourceType& OutResourceType) override;
	virtual void HarvestFoliage(float Damage, EHarvestingToolType ToolType, EToolTier ToolTier, AActor* CharacterRef) override;
	virtual void CalculateResources(TArray<FResourceStructure> InGivenResources, float LocalDamage, EHarvestingToolType ToolType, EToolTier ToolTier, AActor* CharacterRef) override;
	
	//--------------------------------------------------------------------------------------------
	// LARGE ITEM MASTER PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USceneComponent> DefaultSceneRoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvestable Data")
	float Health = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvestable Data")
	EResourceType ResourceType;
};

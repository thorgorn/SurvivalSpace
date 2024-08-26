// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.

#pragma once

#include "CoreMinimal.h"
#include "Items/EquippableMaster.h"
#include "Structs/Structs.h"
#include "EquippableToolMaster.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALSPACE_API AEquippableToolMaster : public AEquippableMaster
{
	GENERATED_BODY()
	
public:

	//--------------------------------------------------------------------------------------------
	// EQUIPPABLE TOOL MASTER CONSTRUCTOR
	//--------------------------------------------------------------------------------------------
	
	AEquippableToolMaster();

protected:
	
	//--------------------------------------------------------------------------------------------
	// EQUIPPABLE TOOL INTERFACE FUNCTIONS
	//--------------------------------------------------------------------------------------------
	
	virtual void UseItem(AActor* CharacterRef, UAnimMontage* MontageToPlay) override;

	virtual void EndAnimation() override;

	virtual void NotifyInterface() override;
	
	//--------------------------------------------------------------------------------------------
	// EQUIPPABLE TOOL FUNCTIONS
	//--------------------------------------------------------------------------------------------

	UFUNCTION(BlueprintCallable, Client, Unreliable, Category = "Hatchet Functions")
	void GetRotationClient();
	
	UFUNCTION(BlueprintCallable, Server, Unreliable, Category = "Hatchet Functions")
	void OverLapOnServer(FRotator InRotator);

	UFUNCTION(BlueprintCallable, Category = "Hatchet Functions")
	void OverLap(FRotator Rotation);
	
	//--------------------------------------------------------------------------------------------
	// EQUIPPABLE TOOL MASTER PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USceneComponent> DefaultSceneRoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(BlueprintReadWrite, Category = "HatchetData")
	bool bUsingItem;

	UPROPERTY(BlueprintReadWrite, Category = "HatchetData")
	TObjectPtr<AActor> CharRef;
	
	UPROPERTY(EditAnywhere ,BlueprintReadWrite, Category = "HatchetData")
	float ItemDamage = 12.0f;

	UPROPERTY(EditAnywhere ,BlueprintReadWrite, Category = "HatchetData")
	EHarvestingToolType ToolType;

	UPROPERTY(EditAnywhere ,BlueprintReadWrite, Category = "HatchetData")
	EToolTier ToolTier;
};

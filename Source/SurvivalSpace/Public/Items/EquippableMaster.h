// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.

#pragma once

#include "CoreMinimal.h"
#include "Enums/Enums.h"
#include "Interfaces/EquippableItemInterface.h"
#include "Items/ItemMaster.h"
#include "EquippableMaster.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALSPACE_API AEquippableMaster : public AItemMaster, public IEquippableItemInterface
{
	GENERATED_BODY()

protected:

	//--------------------------------------------------------------------------------------------
	// EQUIPPABLE INTERFACE FUNCTIONS
	//--------------------------------------------------------------------------------------------
	
	virtual void GetEquippableInfo(FName& OutSocketName, EEquippableState& OutAnimationState) override;

	virtual void GetInitialSocketInfo(FName& InitialSocket) override;
	
	//--------------------------------------------------------------------------------------------
	// EQUIPPABLE PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equippable Setup")
	FName SocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equippable Setup")
	FName InitialSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equippable Setup")
	EEquippableState AnimationState;
	
};

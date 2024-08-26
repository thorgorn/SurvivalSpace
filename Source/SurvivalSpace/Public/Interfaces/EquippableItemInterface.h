// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.

#pragma once

#include "CoreMinimal.h"
#include "Enums/Enums.h"
#include "UObject/Interface.h"
#include "EquippableItemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable)
class UEquippableItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SURVIVALSPACE_API IEquippableItemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable)
	virtual void GetEquippableInfo(FName &OutSocketName, EEquippableState &OutAnimationState);

	UFUNCTION(BlueprintCallable)
	virtual void GetInitialSocketInfo(FName& InitialSocket);
	
	UFUNCTION(BlueprintCallable)
	virtual void UseItem(AActor* CharacterRef, UAnimMontage* MontageToPlay);

	UFUNCTION(BlueprintCallable)
	virtual void EndAnimation();

	UFUNCTION(BlueprintCallable)
	virtual void NotifyInterface();

	UFUNCTION(BlueprintCallable)
	virtual void GetAttackMontage(UAnimMontage* &AttackMontage);
	
};

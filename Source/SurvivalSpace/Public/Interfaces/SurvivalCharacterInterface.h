// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/Enums.h"
#include "Structs/Structs.h"
#include "UObject/Interface.h"
#include "SurvivalCharacterInterface.generated.h"

class AASurvivalCharacter;
// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable)
class USurvivalCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SURVIVALSPACE_API ISurvivalCharacterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable)
	virtual void GetAnimationStates(ECharacterStates& OutCurrentState, EEquippableState& OutEquippableState);

	UFUNCTION(BlueprintCallable)
	virtual void UpdateItem(EContainerType Container, int32 Index, FItemStructure ItemInfo);

	UFUNCTION(BlueprintCallable)
	virtual void OnSlotDrop(EContainerType TargetContainer, EContainerType FromContainer, int32 FromIndex, int32 DroppedIndex, EArmorType ArmorType);

	UFUNCTION(BlueprintCallable)
	virtual void ResetItem(EContainerType Container, int32 Index);

	UFUNCTION(BlueprintCallable)
	virtual void ThirdPersonMontage(UAnimMontage* Montage);

	UFUNCTION(BlueprintCallable)
	virtual void GetCameraRotation(FRotator& Rotation) const = 0;

	UFUNCTION(BlueprintCallable)
	virtual void GetCameraLocation(FVector& Location) const = 0;

	UFUNCTION(BlueprintCallable)
	virtual void HarvestItem(FItemStructure Resource);

	UFUNCTION(BlueprintCallable)
	virtual void DestroyItem(int32 Index);

	UFUNCTION(BlueprintCallable)
	virtual void GetHitFXInfo(FVector HitLocation, EResourceType ResourceType);

	UFUNCTION(BlueprintCallable)
	virtual void DoublePressSlot(EContainerType ContainerType, int32 Index);
	
	virtual void GetCharRef(TObjectPtr<AASurvivalCharacter> &CharRef);

	UFUNCTION(BlueprintCallable)
	virtual void UpdateCraftItem(EContainerType Container, int32 Index, FItemStructure ItemInfo);

	UFUNCTION(BlueprintCallable)
	virtual void ResetCraftItem(EContainerType Container, int32 Index);

	UFUNCTION(BlueprintCallable)
	virtual void UpdateCraftResourcesUI();

	UFUNCTION(BlueprintCallable)
	virtual void GetCraftingRecipesAndItems(ECraftingType CraftingType);
};

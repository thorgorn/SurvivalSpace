#pragma once

#include "CoreMinimal.h"
#include "Enums/Enums.h"
#include "Structs.generated.h"

class UItemInfo;

USTRUCT(Blueprintable)
struct FItemStructure
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 ItemID;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 ItemQuantity;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSoftObjectPtr<UItemInfo> ItemAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 CurrentHP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MaxHP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 CurrentAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MaxAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 StackSize;
};

USTRUCT(Blueprintable)
struct FResourceStructure
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSoftObjectPtr<UItemInfo> Resource;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Quantity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EHarvestingToolType PreferredTool;
};

USTRUCT(Blueprintable)
struct FResourceEffects
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EResourceType ResourceType; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UParticleSystem> VFX;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USoundBase> SFX;
};

USTRUCT(Blueprintable)
struct FItemRecipes
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 ItemID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 ItemQuantity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> ItemIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText ItemName;
};

USTRUCT(Blueprintable)
struct FItemRecipeInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 ItemID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> ItemIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 CurrentQuantity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 NeededQuantity;

};

USTRUCT(Blueprintable)
struct FEquippableMontages
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UAnimMontage> AttackMontage;
};

USTRUCT(Blueprintable)
struct FItem
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 ItemID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 ItemQuantity;
	
};
#pragma once

#include "CoreMinimal.h"
#include "Enums/Enums.h"
#include "Structs.generated.h"

class UItemInfo;

USTRUCT(Blueprintable)
struct FItemStructure
{
	GENERATED_BODY()

	FItemStructure() = default;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 ItemID = 0;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 ItemQuantity = 0;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 CurrentHP = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MaxHP = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 CurrentAmmo = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MaxAmmo = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 StackSize = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSoftObjectPtr<UItemInfo> ItemAsset;
};

USTRUCT(Blueprintable)
struct FItem
{
	GENERATED_BODY()

	FItem() : ItemID(0), ItemQuantity(0)
	{
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 ItemID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 ItemQuantity;
};

USTRUCT(Blueprintable)
struct FResourceStructure
{
	GENERATED_BODY()

	FResourceStructure() = default;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSoftObjectPtr<UItemInfo> Resource;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Quantity = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EHarvestingToolType PreferredTool = EHarvestingToolType::Hatchet;
};

USTRUCT(Blueprintable)
struct FResourceEffects
{
	GENERATED_BODY()

	FResourceEffects() = default;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EResourceType ResourceType = EResourceType::Wood; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UParticleSystem> VFX;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USoundBase> SFX;
};

USTRUCT(Blueprintable)
struct FItemRecipes
{
	GENERATED_BODY()

	FItemRecipes() = default;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 ItemID = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 ItemQuantity = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> ItemIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText ItemName;
};

USTRUCT(Blueprintable)
struct FItemRecipeInfo
{
	GENERATED_BODY()

	FItemRecipeInfo() = default;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 ItemID = 0;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 CurrentQuantity = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 NeededQuantity = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> ItemIcon;

};

USTRUCT(Blueprintable)
struct FEquippableMontages
{
	GENERATED_BODY()

	FEquippableMontages() = default;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UAnimMontage> AttackMontage;
};
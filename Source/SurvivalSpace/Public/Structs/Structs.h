﻿#pragma once

#include "CoreMinimal.h"
#include "Enums/Enums.h"
#include "Structs.generated.h"

class UItemInfo;

// Main Item struct that ties into UItemInfo
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

// Used for crafting items
USTRUCT(Blueprintable)
struct FSimpleItemStructure
{
	GENERATED_BODY()
	
	FSimpleItemStructure() : ItemID(0), ItemQuantity(0) {}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 ItemID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 ItemQuantity;
};

// Used for resource items
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

// Used to setup resource effects i.e vfx and sfx
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

// Used for crafting items
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

// Used for crafting item slot widget
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

// Used to get montages for equippables
USTRUCT(Blueprintable)
struct FEquippableMontages
{
	GENERATED_BODY()

	FEquippableMontages() = default;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UAnimMontage> AttackMontage;
};

// Used for Crafting Items
USTRUCT(Blueprintable)
struct FCraftingStruct
{
	GENERATED_BODY()

	FCraftingStruct() = default;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Index = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Quantity = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 ItemID = 0;
};
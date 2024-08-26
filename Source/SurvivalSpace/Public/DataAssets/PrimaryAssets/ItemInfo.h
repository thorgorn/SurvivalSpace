// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Enums/Enums.h"
#include "Structs/Structs.h"
#include "ItemInfo.generated.h"

class AItemMaster;
/**
 * 
 */
UCLASS(Blueprintable)
class SURVIVALSPACE_API UItemInfo : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------------------------
	// DATA ASSET ITEM PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Item Info")
	int32 ItemID;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Item Info")
	TObjectPtr<UTexture2D> ItemIcon;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Item Info")
	FText ItemName;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Item Info")
	FText ItemDescription;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Item Info")
	EItemRarity ItemRarity;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Item Info")
	bool bIsStackable;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Item Info")
	int32 StackSize;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Item Info")
	EItemType ItemType;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Item Info")
	TSoftClassPtr<AItemMaster> ItemClassRef;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Item Info")
	int32 ItemCurrentHP;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Item Info")
	int32 ItemMaxHP;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Item Info")
	float ItemWeight;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Item Info|Resource Info")
	EResourceType ResourceType;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Item Info|Resource Info")
	FText ItemLocationText;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Item Info|Equippable Info")
	int32 ItemDamage;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Item Info|Equippable Info")
	int32 CurrentAmmo;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Item Info|Equippable Info")
	int32 MaxAmmo;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Item Info|Equippable Info")
	bool bUseAmmo;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Item Info|Equippable Info|Armor Info")
	EArmorType ArmorType;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Item Info|Equippable Info|Weapon|Montages")
	TSoftObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Item Info|Equippable Info|Weapon|VFX&SFX")
	TArray<FResourceEffects> ResourceEffectsArray;
};

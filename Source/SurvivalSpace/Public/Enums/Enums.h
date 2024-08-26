#pragma once

#include "CoreMinimal.h"
#include "Enums.generated.h"

UENUM(BlueprintType)
enum class ECharacterStates : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Crouching UMETA(DisplayName = "Crouching"),
	Proning UMETA(DisplayName = "Proning")
};

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	Common UMETA(DisplayName = "Common"),
	Uncommon UMETA(DisplayName = "Uncommon"),
	Rare UMETA(DisplayName = "Rare"),
	Epic UMETA(DisplayName = "Epic"),
	Legendary UMETA(DisplayName = "Legendary")
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Resource UMETA(DisplayName = "Resource"),
	Equippable UMETA(DisplayName = "Equippable"),
	Armor UMETA(DisplayName = "Armor"),
	Consumable UMETA(DisplayName = "Consumable"),
	Buildable UMETA(DisplayName = "Buildable")
};

UENUM(BlueprintType)
enum class EResourceType : uint8
{
	Wood UMETA(DisplayName = "Wood"),
	Stone UMETA(DisplayName = "Stone"),
	Vegetation UMETA(DisplayName = "Vegetation"),
	Metal UMETA(DisplayName = "Metal"),
	Leather UMETA(DisplayName = "Leather"),
	Cloth UMETA(DisplayName = "Cloth")
};

UENUM(BlueprintType)
enum class EArmorType : uint8
{
	Helmet UMETA(DisplayName = "Helmet"),
	Chest UMETA(DisplayName = "Chest"),
	Pants UMETA(DisplayName = "Pants"),
	Boots UMETA(DisplayName = "Boots"),
	BackPack UMETA(DisplayName = "BackPack")
};

UENUM(BlueprintType)
enum class EContainerType : uint8
{
	Inventory UMETA(DisplayName = "Inventory"),
	HotBar UMETA(DisplayName = "HotBar"),
	Storage UMETA(DisplayName = "Storage"),
	Armor UMETA(DisplayName = "Armor"),
	Crafting UMETA(DisplayName = "Crafting")
};

UENUM(BlueprintType)
enum class EEquippableState : uint8
{
	Default UMETA(DisplayName = "Default"),
	Hatchet UMETA(DisplayName = "Hatchet"),
	Bow UMETA(DisplayName = "Bow"),
	Rock UMETA(DisplayName = "Rock"),
	Rifle UMETA(DisplayName = "Rifle"),
	RocketLauncher UMETA(DisplayName = "RocketLauncher"),
	Spear UMETA(DisplayName = "Spear"),
	Swimming UMETA(DisplayName = "Swimming")
};

UENUM(BlueprintType)
enum class EHarvestingToolType : uint8
{
	PickAxe UMETA(DisplayName = "PickAxe"),
	Hatchet UMETA(DisplayName = "Hatchet")
};

UENUM(BlueprintType)
enum class EToolTier : uint8
{
	Stone UMETA(DisplayName = "Stone"),
	Iron UMETA(DisplayName = "Iron")
};

UENUM(BlueprintType)
enum class ECraftingType : uint8
{
	PlayerInventory UMETA(DisplayName = "PlayerInventory"),
	CookingPot UMETA(DisplayName = "CookingPot"),
	CraftingBench UMETA(DisplayName = "CraftingBench"),
	SmeltingForge UMETA(DisplayName = "SmeltingForge"),
	AdvancedWorkBench UMETA(DisplayName = "AdvancedWorkBench"),
	StorageBox UMETA(DisplayName = "StorageBox"),
	CropPlot UMETA(DisplayName = "CropPlot")
};
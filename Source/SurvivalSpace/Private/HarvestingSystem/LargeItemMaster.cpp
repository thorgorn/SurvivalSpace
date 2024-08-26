// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.


#include "HarvestingSystem/LargeItemMaster.h"

#include "DataAssets/PrimaryAssets/HarvestingResource.h"
#include "DataAssets/PrimaryAssets/ItemInfo.h"
#include "GameFramework/Character.h"
#include "Interfaces/SurvivalCharacterInterface.h"
#include "Kismet/KismetMathLibrary.h"

ALargeItemMaster::ALargeItemMaster()
{
	// Create the DefaultSceneRoot component and set it as the root
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(DefaultSceneRoot);

	// Create the StaticMesh component and attach it to the DefaultSceneRoot
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(DefaultSceneRoot);
}

void ALargeItemMaster::GetLargeItemHealth(float& OutHealth)
{
	OutHealth = Health;
}

void ALargeItemMaster::UpdateLargeItemHealth(float InHealth)
{
	Health = InHealth;
}

void ALargeItemMaster::GetLargeResources(TSoftObjectPtr<UHarvestingResource> &OutResources)
{
	OutResources = Resources;
}

void ALargeItemMaster::GetResourceType(EResourceType& OutResourceType)
{
	OutResourceType = ResourceType;
}

void ALargeItemMaster::HarvestFoliage(float Damage, EHarvestingToolType ToolType, EToolTier ToolTier, AActor* CharacterRef)
{
	float LocalDamage = Damage;
	
	float LocalHealth = Health - LocalDamage;

	if (LocalHealth <= 0.0f)
	{
		//Overriden In Blueprints
		FoliageDestroyed(LocalDamage, ToolType, ToolTier, CharacterRef);
	}
	else
	{
		Health = LocalHealth;

		if (Resources.ToSoftObjectPath().IsValid())
		{
			// Load the item asset if the path is valid
			UHarvestingResource* LoadedAsset = Resources.LoadSynchronous();
			if (LoadedAsset)
			{
				CalculateResources(LoadedAsset->GivenItems, LocalDamage, ToolType, ToolTier, CharacterRef);
			}
		}	
	}
}

void ALargeItemMaster::CalculateResources(TArray<FResourceStructure> InGivenResources, float LocalDamage, EHarvestingToolType ToolType, EToolTier ToolTier, AActor* CharacterRef)
{
	TArray<FResourceStructure> LocalGivenResources = InGivenResources;
	float NewLocalDamage = LocalDamage;

	for (const FResourceStructure& ResourceStruct : LocalGivenResources)
	{
		FResourceStructure LocalResourceStruct = ResourceStruct;

		TSoftObjectPtr<UItemInfo> LocalResource = ResourceStruct.Resource;

		float BaseVar = ResourceStruct.Quantity;

		float RateVar = 1.0f;

		// Random Float in Range
		float RandomFloatAToolType = FMath::RandRange(0.8f, 1.1f);
		float RandomFloatBToolType = FMath::RandRange(0.04f, 0.5f);

		// Tool Type Check (Assuming PreferredTool and ToolTypeVar are enums or similar types)
		bool bIsToolTypeEqual = (ResourceStruct.PreferredTool == ToolType);

		float ToolTypeVar = UKismetMathLibrary::SelectFloat(RandomFloatAToolType, RandomFloatBToolType, bIsToolTypeEqual);

		// Random Float in Range for Tool Tier
		float RandomFloatToolTierA = FMath::RandRange(0.8f, 1.2f);
		float RandomFloatToolTierB = FMath::RandRange(1.2f, 1.8f);

		// Select ToolTierVar based on ToolTier enum value
		float ToolTierVar;
		switch (ToolTier)
		{
		case EToolTier::Stone:
			ToolTierVar = RandomFloatToolTierA;
			break;
		case EToolTier::Iron:
			ToolTierVar = RandomFloatToolTierB;
			break;
		default:
			ToolTierVar = 1.0f;
			break;
		}
		
		float Result = (((BaseVar * RateVar) * ToolTypeVar) * ToolTierVar) * NewLocalDamage;

		// Set Local Resource Quantity
		int32 LocalResourceQuantity = Result;
		
		if (LocalResourceQuantity > 0)
		{
			if (LocalResource.ToSoftObjectPath().IsValid())
			{
				// Load the item asset if the path is valid
				UItemInfo* LoadedAsset = LocalResource.LoadSynchronous();
				if (LoadedAsset)
				{
					if (ACharacter* Character = Cast<ACharacter>(CharacterRef))
					{
						ISurvivalCharacterInterface* CharacterInterface = Cast<ISurvivalCharacterInterface>(Character);
						if (CharacterInterface)
						{
							FItemStructure  NewItemToAdd;
							
							NewItemToAdd.ItemID = LoadedAsset->ItemID;
							NewItemToAdd.ItemQuantity = LocalResourceQuantity;
							NewItemToAdd.ItemAsset = LocalResource;
							NewItemToAdd.CurrentHP = LoadedAsset->ItemCurrentHP;
							NewItemToAdd.MaxHP = LoadedAsset->ItemMaxHP;
							NewItemToAdd.StackSize = LoadedAsset->StackSize;
							
							CharacterInterface->HarvestItem(NewItemToAdd);
						}
					}
				}
			}
		}
	}
}

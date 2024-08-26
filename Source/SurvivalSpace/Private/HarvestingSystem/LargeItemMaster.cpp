// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.


#include "HarvestingSystem/LargeItemMaster.h"

#include "DataAssets/PrimaryAssets/HarvestingResource.h"
#include "DataAssets/PrimaryAssets/ItemInfo.h"
#include "GameFramework/Character.h"
#include "Interfaces/SurvivalCharacterInterface.h"
#include "Kismet/KismetMathLibrary.h"

ALargeItemMaster::ALargeItemMaster()
{
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(DefaultSceneRoot);
	
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
	//float LocalDamage = Damage;
	
	float LocalHealth = Health - Damage;

	if (LocalHealth <= 0.0f)
	{
		//Overriden In Blueprints
		FoliageDestroyed(Damage, ToolType, ToolTier, CharacterRef);
	}
	else
	{
		Health = LocalHealth;

		if (Resources.ToSoftObjectPath().IsValid())
		{
			UHarvestingResource* LoadedAsset = Resources.LoadSynchronous();
			if (LoadedAsset)
			{
				CalculateResources(LoadedAsset->GivenItems, Damage, ToolType, ToolTier, CharacterRef);
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
		
		float RandomFloatAToolType = FMath::RandRange(0.8f, 1.1f);
		float RandomFloatBToolType = FMath::RandRange(0.04f, 0.5f);
		
		bool bIsToolTypeEqual = (ResourceStruct.PreferredTool == ToolType);

		float ToolTypeVar = UKismetMathLibrary::SelectFloat(RandomFloatAToolType, RandomFloatBToolType, bIsToolTypeEqual);
		
		float RandomFloatToolTierA = FMath::RandRange(0.8f, 1.2f);
		float RandomFloatToolTierB = FMath::RandRange(1.2f, 1.8f);
		
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
		
		int32 LocalResourceQuantity = Result;
		
		if (LocalResourceQuantity > 0)
		{
			if (LocalResource.ToSoftObjectPath().IsValid())
			{
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

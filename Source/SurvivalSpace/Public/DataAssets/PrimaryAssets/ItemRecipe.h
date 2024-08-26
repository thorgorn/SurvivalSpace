// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Structs/Structs.h"
#include "ItemRecipe.generated.h"

struct FItemRecipe;
/**
 * 
 */
UCLASS()
class SURVIVALSPACE_API UItemRecipe : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------------------------
	// DATA ASSET ITEM RECIPE PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Recipe Info")
	FText ItemName;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Recipe Info")
	int32 ItemID;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Recipe Info")
	FText ItemDescription;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Recipe Info")
	TObjectPtr<UTexture2D> ItemIcon;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Recipe Info")
	TArray<FItemRecipes> RequiredItems;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Recipe Info")
	int32 ItemExperience;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Recipe Info")
	TSoftObjectPtr<UItemInfo> ItemAsset;
	
};

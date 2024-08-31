// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CraftingProgress.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALSPACE_API UCraftingProgress : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent)
	void CraftItem(const FText& ItemName);
	
};

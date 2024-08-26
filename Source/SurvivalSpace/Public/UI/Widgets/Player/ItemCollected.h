// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemCollected.generated.h"

class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class SURVIVALSPACE_API UItemCollected : public UUserWidget
{
	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------------------------
	// DRAGGED ITEM PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------

	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	void UpdateUI();

	//--------------------------------------------------------------------------------------------
	// DRAGGED ITEM PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UImage> ResourceIcon;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UTextBlock> AddedText;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UTextBlock> ItemText;

	UPROPERTY(EditAnywhere ,BlueprintReadWrite, Category = "Data", meta=(ExposeOnSpawn))
	TObjectPtr<UTexture2D> ResourceImage;

	UPROPERTY(EditAnywhere ,BlueprintReadWrite, Category = "Data", meta=(ExposeOnSpawn))
	int32 ResourceQuantity;

	UPROPERTY(EditAnywhere ,BlueprintReadWrite, Category = "Data", meta=(ExposeOnSpawn))
	FText ResourceName;
	
};

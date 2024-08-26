// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "Enums/Enums.h"
#include "DraggedItem.generated.h"

class UProgressBar;
class UTextBlock;
class UBorder;
class UTexture2D;
/**
 * 
 */
UCLASS()
class SURVIVALSPACE_API UDraggedItem : public UCommonButtonBase
{
	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------------------------
	// DRAGGED ITEM FUNCTIONS
	//--------------------------------------------------------------------------------------------
	virtual void NativeConstruct() override;
	
	//--------------------------------------------------------------------------------------------
	// DRAGGED ITEM PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UBorder> ItemBGWhenFilled;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UBorder> ItemIcon;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UTextBlock> TopText;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UTextBlock> BottomText;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UTextBlock> QuantityText;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UTextBlock> WeightText;
	
	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UProgressBar> ItemHP;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Data", meta=(ExposeOnSpawn))
	TObjectPtr<UTexture2D> ImageIcon;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Data", meta=(ExposeOnSpawn))
	FText TextTop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta=(ExposeOnSpawn))
	EItemType ItemType;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Data", meta=(ExposeOnSpawn))
	FText Quantity;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Data", meta=(ExposeOnSpawn))
	bool bUseAmmo;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Data", meta=(ExposeOnSpawn))
	int32 CurrentAmmo;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Data", meta=(ExposeOnSpawn))
	int32 MaxAmmo;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Data", meta=(ExposeOnSpawn))
	int32 CurrentHP;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Data", meta=(ExposeOnSpawn))
	int32 MaxHP;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Data", meta=(ExposeOnSpawn))
	FText Weight;
};

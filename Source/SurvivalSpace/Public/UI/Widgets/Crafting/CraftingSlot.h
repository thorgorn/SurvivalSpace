// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "Structs/Structs.h"
#include "CraftingSlot.generated.h"

class UCraftingItemContainerGrid;
class UItemContainerGrid;
class USizeBox;
class UProgressBar;
class UTextBlock;
class UBorder;
/**
 * 
 */
UCLASS()
class SURVIVALSPACE_API UCraftingSlot : public UCommonButtonBase
{
	GENERATED_BODY()

public:
	
	//--------------------------------------------------------------------------------------------
	// CRAFTING SLOT FUNCTIONS
	//--------------------------------------------------------------------------------------------
	virtual void NativeOnHovered() override;

	virtual void NativeOnUnhovered() override;

	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
	
	UFUNCTION(BlueprintCallable)
	void UpdateSlot(FItemStructure ItemInfo);

	UFUNCTION(BlueprintCallable)
	void OnItemAssetLoaded(FSoftObjectPath AssetPath, FItemStructure ItemInfo);

	UFUNCTION(BlueprintCallable)
	void ResetSlot();
	//--------------------------------------------------------------------------------------------
	// INVENTORY SLOT PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------
	
	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UBorder> ItemIcon;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UTextBlock> ItemNameText;
	
	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UTextBlock> QuantityText;
	
	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<USizeBox> ItemSlotSizeBox;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UBorder> ItemHoverBorder;

	UPROPERTY(BlueprintReadWrite, Category = "Slot Data")
	int32 ItemIndex;

	UPROPERTY(BlueprintReadWrite, Category = "Slot Data")
	EContainerType ContainerType;

	UPROPERTY(BlueprintReadWrite, Category = "Slot Data")
	FItemStructure ItemInfoData;

	UPROPERTY(BlueprintReadWrite, Category = "Slot Data")
	TObjectPtr<UItemInfo> ItemAssetInfo;

	UPROPERTY(BlueprintReadWrite, Category = "Slot Data")
	bool bHasItemInSlot = false;
	
	UPROPERTY(BlueprintReadWrite, Category = "Slot Data")
	TObjectPtr<UCraftingItemContainerGrid> Parent;

	UPROPERTY(BlueprintReadWrite, Category = "Slot Data")
	TObjectPtr<USizeBox> SizeBox_Input;
};

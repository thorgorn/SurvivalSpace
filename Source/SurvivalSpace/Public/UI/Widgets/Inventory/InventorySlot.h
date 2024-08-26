// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "Structs/Structs.h"
#include "Enums/Enums.h"
#include "InventorySlot.generated.h"

class USizeBox;
class UItemInfoWidget;
class UItemContainerGrid;
class UDraggedItem;
class UProgressBar;
class UTextBlock;
class UBorder;
/**
 * 
 */
UCLASS()
class SURVIVALSPACE_API UInventorySlot : public UCommonButtonBase
{
	GENERATED_BODY()

public:
	
	//--------------------------------------------------------------------------------------------
	// INVENTORY SLOT FUNCTIONS
	//--------------------------------------------------------------------------------------------

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual void NativeOnPressed() override;

	virtual void OnInputMethodChanged(ECommonInputType CurrentInputType) override;

	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;

	virtual FReply NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	virtual void NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent) override;

	virtual void NativeDestruct() override;

	virtual void NativeOnHovered() override;

	virtual void NativeOnUnhovered() override;
	
	UFUNCTION(BlueprintCallable)
	void UpdateSlot(FItemStructure ItemInfo);

	UFUNCTION(BlueprintCallable)
	void OnItemAssetLoaded(FSoftObjectPath AssetPath, FItemStructure ItemInfo);

	UFUNCTION(BlueprintCallable)
	void ResetSlot();

	UFUNCTION(BlueprintCallable)
	void DisplayItemInfoWidget();

	UFUNCTION()
	void DisplayItemInfoWidgetDelay();

	UFUNCTION(BlueprintCallable)
	void DisplayItemInfoInventory();

	UFUNCTION(BlueprintCallable)
	void GetItemToolTip();
	
	//--------------------------------------------------------------------------------------------
	// INVENTORY SLOT PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UBorder> ItemBGHotBar;

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

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<USizeBox> ItemSlotSizeBox;

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

	UPROPERTY(EditAnywhere ,BlueprintReadWrite, Category = "Slot Data")
	TSubclassOf<UDraggedItem> DraggedItemWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "Slot Data")
	TObjectPtr<UDraggedItem> DraggedItemWidget;

	UPROPERTY(BlueprintReadWrite, Category = "Slot Data")
	TObjectPtr<UItemContainerGrid> Parent;

	UPROPERTY(BlueprintReadWrite, Category = "Slot Data")
	TObjectPtr<USizeBox> SizeBox_Input;

	UPROPERTY(EditAnywhere ,BlueprintReadWrite, Category = "ItemInfoWidget Data")
	TSubclassOf<UItemInfoWidget> ItemInfoWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "ItemInfoWidget Data")
	TObjectPtr<UItemInfoWidget> ItemInfoWidget;
	
	UPROPERTY(BlueprintReadWrite, Category = "ItemInfoWidget Data")
	bool bAddedToFocusPath;

	UPROPERTY(BlueprintReadWrite, Category = "ItemInfoWidget Data")
	bool bIsCraftingSlot = false;

	FTimerHandle ItemInfoWidgetDelayHandle;
};

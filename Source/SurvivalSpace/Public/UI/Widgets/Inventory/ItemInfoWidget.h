// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Structs/Structs.h"
#include "ItemInfoWidget.generated.h"

class UCommonButtonBase;
class UInventorySlot;
class UVerticalBox;
class UTextBlock;
class UProgressBar;
class UHorizontalBox;
class UBorder;
class UImage;
class UCommonButton;
/**
 * 
 */
UCLASS()
class SURVIVALSPACE_API UItemInfoWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------------------------
	// ITEMINFOWIDGET OVERRIDEN FUNCTIONS
	//--------------------------------------------------------------------------------------------
	virtual void NativeConstruct() override;

	//--------------------------------------------------------------------------------------------
	// ITEMINFOWIDGET BUTTON FUNCTIONS
	//--------------------------------------------------------------------------------------------
	UFUNCTION()
	void DestroyButtonClicked();

	UFUNCTION()
	void TransferButtonClicked();
	//--------------------------------------------------------------------------------------------
	// ITEMINFOWIDGET VARIABLES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	FText ItemNameText;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	FText ItemDescriptionText;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	FText ItemTypeText;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	FText ItemRarityText;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	FText ItemLocationText;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	int32 ItemQuantityAmount;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	int32 ItemStackSize;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	int32 ItemIndex;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	TObjectPtr<UTexture2D> ItemImage;

	UPROPERTY(EditAnywhere ,BlueprintReadWrite, Category = "Data")
	TObjectPtr<UTexture2D> BorderTexture;;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	float GatherPercent;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	float ItemDamageAmount;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	float ItemCurrentHP;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	float ItemMaxHP;

	UPROPERTY(BlueprintReadWrite, Category = "Data|Slate")
	FSlateColor Common;

	UPROPERTY(BlueprintReadWrite, Category = "Data|Slate")
	FSlateColor Uncommon;

	UPROPERTY(BlueprintReadWrite, Category = "Data|Slate")
	FSlateColor Rare;

	UPROPERTY(BlueprintReadWrite, Category = "Data|Slate")
	FSlateColor Epic;

	UPROPERTY(BlueprintReadWrite, Category = "Data|Slate")
	FSlateColor Legendary;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	EResourceType ItemResourceType;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	EItemRarity ItemRarityType;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	EItemType ItemTypes;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	EContainerType ItemContainerType;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	FItemStructure ItemToDestroy;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	TObjectPtr<UInventorySlot> ItemSlotWidget;
	
	UPROPERTY(BlueprintReadWrite, Category = "Data")
	bool bIsStackable;

protected:

	//--------------------------------------------------------------------------------------------
	// ITEMINFOWIDGET FUNCTIONS
	//--------------------------------------------------------------------------------------------
		UFUNCTION()
		void InitializeItemInfo();
	//--------------------------------------------------------------------------------------------
	// ITEMINFOWIDGET PROPERTIES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UImage> BGAlpha;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UBorder> BorderColor;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UHorizontalBox> DurabilityBox;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UHorizontalBox> GatherBox;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UProgressBar> GatherProgress;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UTextBlock> ItemDamage;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UTextBlock> ItemDescription;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UHorizontalBox> ItemDescriptionBox;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UTextBlock> ItemDurability;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UProgressBar> ItemDurabilityProgress;
	
	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UImage> ItemGatherIcon;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UImage> ItemIcon;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UTextBlock> ItemLocation;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UHorizontalBox> ItemLocationBox;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UTextBlock> ItemName;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UTextBlock> ItemQuantity;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UTextBlock> ItemRarity;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UVerticalBox> ItemStatsBox;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UVerticalBox> ItemStatsBox1;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UTextBlock> ItemType;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UImage> WeaponImage;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UCommonButtonBase> W_ItemMoveButton;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UCommonButtonBase> W_ItemTransferButton;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UCommonButtonBase> W_ItemDestroyButton;
};

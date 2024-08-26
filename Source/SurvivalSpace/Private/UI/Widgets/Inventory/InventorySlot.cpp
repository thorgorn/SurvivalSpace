// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.


#include "UI/Widgets/Inventory/InventorySlot.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Border.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "DataAssets/PrimaryAssets/ItemInfo.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Interfaces/SurvivalCharacterInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetTextLibrary.h"
#include "UI/Widgets/Inventory/DraggedItem.h"
#include "UI/Widgets/Inventory/Operations/ItemDrag.h"
#include "CommonInputSubsystem.h"
#include "Components/SizeBox.h"
#include "GameFramework/Character.h"
#include "Interfaces/ControllerInterface.h"
#include "UI/Widgets/Inventory/ItemContainerGrid.h"
#include "UI/Widgets/Inventory/ItemInfoWidget.h"

void UInventorySlot::NativeConstruct()
{
    Super::NativeConstruct();

    switch (ContainerType) {
    case EContainerType::Inventory:
        ItemBGHotBar->SetVisibility(ESlateVisibility::Hidden);
        break;
    case EContainerType::HotBar:
        ItemBGHotBar->SetVisibility(ESlateVisibility::Visible);
        break;
    case EContainerType::Storage:
        ItemBGHotBar->SetVisibility(ESlateVisibility::Hidden);
        break;
    case EContainerType::Armor:
        ItemBGHotBar->SetVisibility(ESlateVisibility::Hidden);
        break;
    case EContainerType::Crafting:
        break;
    }

}

void UInventorySlot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (bIsCraftingSlot)
    {
        // should delete this....
    }
    else
    {
        switch (ContainerType) {
        case EContainerType::Inventory:
            if (IsValid(ItemAssetInfo))
            {
                SizeBox_Input->SetVisibility(ESlateVisibility::Visible);
            }
            else
            {
                SizeBox_Input->SetVisibility(ESlateVisibility::Collapsed);
            }
            break;
        case EContainerType::HotBar:
            SizeBox_Input->SetVisibility(ESlateVisibility::Collapsed);
            break;
        case EContainerType::Storage:
            SizeBox_Input->SetVisibility(ESlateVisibility::Collapsed);
            break;
        case EContainerType::Armor:
            SizeBox_Input->SetVisibility(ESlateVisibility::Collapsed);
            break;
        case EContainerType::Crafting:
            break;
        }
    }
}

FReply UInventorySlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    
    FEventReply EventReply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);

    if (bIsCraftingSlot)
    {
        // should delete this check
    }
    else
    {
        if (EventReply.NativeReply.IsEventHandled())
        {
            return EventReply.NativeReply;
        }
    }
    
    return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

FReply UInventorySlot::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
    {
        if (bIsCraftingSlot)
        {
            // should delete this check
        }
        else
        {
            FEventReply EventReply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
            return EventReply.NativeReply;
        }
    }

    return Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
}

void UInventorySlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
    Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

    if (!bHasItemInSlot)
    {
        return;
    }
    if (bIsCraftingSlot)
    {
        return;
    }

    DraggedItemWidget = CreateWidget<UDraggedItem>(GetWorld(), DraggedItemWidgetClass);
    if (DraggedItemWidget)
    {
        DraggedItemWidget->ImageIcon = ItemAssetInfo->ItemIcon;
        DraggedItemWidget->TextTop = FText::FromString(FString::FromInt(ItemAssetInfo->ItemDamage));
        DraggedItemWidget->ItemType = ItemAssetInfo->ItemType;
        DraggedItemWidget->Quantity = FText::AsNumber(ItemInfoData.ItemQuantity);
        DraggedItemWidget->bUseAmmo = ItemAssetInfo->bUseAmmo;
        DraggedItemWidget->CurrentHP = ItemInfoData.CurrentHP;
        DraggedItemWidget->MaxHP = ItemInfoData.MaxHP;
        DraggedItemWidget->CurrentAmmo = ItemInfoData.CurrentAmmo;
        DraggedItemWidget->MaxAmmo = ItemInfoData.MaxAmmo;
        double ItemWeight = ItemInfoData.ItemQuantity * ItemAssetInfo->ItemWeight;
        DraggedItemWidget->Weight = UKismetTextLibrary::Conv_DoubleToText(ItemWeight, ERoundingMode::HalfToEven, false, true, 1, 324, 1, 3);

        UItemDrag* DragOperation = Cast<UItemDrag>(UWidgetBlueprintLibrary::CreateDragDropOperation(UItemDrag::StaticClass()));
        if (DragOperation)
        {
            DragOperation->SlotIndex = ItemIndex;
            DragOperation->FromContainer = ContainerType;
            DragOperation->ItemType = ItemAssetInfo->ItemType;
            DragOperation->ArmorType = ItemAssetInfo->ArmorType;

            DragOperation->DefaultDragVisual = DraggedItemWidget;
            OutOperation = DragOperation;
        }
    }
}

bool UInventorySlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
    UDragDropOperation* InOperation)
{
    IItemDragInterface* ItemDragOperationInterface = Cast<IItemDragInterface>(InOperation);
    if (!ItemDragOperationInterface)
    {
        return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
    }
    
    int32 SlotIndex;
    EContainerType FromContainer;
    EArmorType ArmorType;
    EItemType ItemType;
    ItemDragOperationInterface->GetItemDragInfo(SlotIndex, FromContainer, ArmorType, ItemType);
    
    int32 LocalSlotIndex = SlotIndex;
    EContainerType LocalFromContainer = FromContainer;
    EArmorType LocalArmorType = ArmorType;
    EItemType LocalItemType = ItemType;
    
    ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (!PlayerCharacter)
    {
        return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
    }
    
    ISurvivalCharacterInterface* SurvivalCharacterInterface = Cast<ISurvivalCharacterInterface>(PlayerCharacter);
    if (!SurvivalCharacterInterface)
    {
        return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
    }
    
    SurvivalCharacterInterface->OnSlotDrop(ContainerType, LocalFromContainer, LocalSlotIndex, ItemIndex, LocalArmorType);

    return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void UInventorySlot::NativeOnPressed()
{
    Super::NativeOnPressed();

    if (ULocalPlayer* LocalPlayer = GetOwningLocalPlayer())
    {
        UCommonInputSubsystem* CommonInputSubsystem = LocalPlayer->GetSubsystem<UCommonInputSubsystem>();

        if (CommonInputSubsystem)
        {
            ECommonInputType InputType = CommonInputSubsystem->GetCurrentInputType();
            
            if (InputType == ECommonInputType::Gamepad)
            {
                ISurvivalCharacterInterface* CharacterInterface = Cast<ISurvivalCharacterInterface>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
                switch (ContainerType) {
                case EContainerType::Inventory:
                    DisplayItemInfoWidget();
                    break;
                case EContainerType::HotBar:

                    if (CharacterInterface)
                    {
                        CharacterInterface->DoublePressSlot(ContainerType, ItemIndex);
                    }
                    break;
                case EContainerType::Storage:
                    break;
                case EContainerType::Armor:
                    break;
                case EContainerType::Crafting:
                    break;
                }
            
            }
        }
    }
}

void UInventorySlot::OnInputMethodChanged(ECommonInputType CurrentInputType)
{
    Super::OnInputMethodChanged(CurrentInputType);

    if (IsValid(ItemInfoWidget))
    {
        switch (CurrentInputType) {
        case ECommonInputType::MouseAndKeyboard:
            ItemInfoWidget->RemoveFromParent();
            break;
        case ECommonInputType::Gamepad:
            ItemInfoWidget->RemoveFromParent();
            break;
        case ECommonInputType::Touch:
            break;
        case ECommonInputType::Count:
            break;
        } 
    }
}

FReply UInventorySlot::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
    if (IsValid(Parent))
    {
        Parent->DesiredSlotToFocus = ItemIndex;
        return FReply::Handled();
    }
    return Super::NativeOnFocusReceived(InGeometry, InFocusEvent);
}

FReply UInventorySlot::NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
    if (InKeyEvent.GetKey() == EKeys::Gamepad_FaceButton_Left)
    {
        IControllerInterface* ControllerInterface = Cast<IControllerInterface>(GetOwningPlayer());

        if (IsValid(ItemInfoWidget))
        {
            ItemInfoWidget->RemoveFromParent();
        }
        
        if (ControllerInterface)
        {
            ControllerInterface->SetSelectedItem(ContainerType, ItemIndex, bHasItemInSlot, EArmorType::Helmet);
        }
        
        return FReply::Handled();
    }
    
    return Super::NativeOnPreviewKeyDown(InGeometry, InKeyEvent);
}

void UInventorySlot::NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent)
{
    Super::NativeOnRemovedFromFocusPath(InFocusEvent);
    
    bAddedToFocusPath = false;

    if (IsValid(ItemInfoWidget))
    {
        ItemInfoWidget->RemoveFromParent();
    }
}

void UInventorySlot::NativeDestruct()
{
    Super::NativeDestruct();

    bAddedToFocusPath = false;

    if (IsValid(ItemInfoWidget))
    {
        ItemInfoWidget->RemoveFromParent();
    }
}

void UInventorySlot::NativeOnHovered()
{
    Super::NativeOnHovered();

    switch (ContainerType)
    {
    case EContainerType::Inventory:
        GetItemToolTip();
        break;
    case EContainerType::HotBar:
        break;
    case EContainerType::Storage:
        break;
    case EContainerType::Armor:
        break;
    case EContainerType::Crafting:
        break;
    }
}

void UInventorySlot::NativeOnUnhovered()
{
    Super::NativeOnUnhovered();

    ItemSlotSizeBox->SetToolTip(nullptr);
}


void UInventorySlot::UpdateSlot(FItemStructure ItemInfo)
{
    ItemInfoData = ItemInfo;
    
    bHasItemInSlot = ItemInfo.ItemID != 0;
    
    if (ItemInfo.ItemAsset.ToSoftObjectPath().IsValid())
    {
        FStreamableManager& AssetLoader = UAssetManager::GetStreamableManager();
        AssetLoader.RequestAsyncLoad(ItemInfo.ItemAsset.ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this, &UInventorySlot::OnItemAssetLoaded, ItemInfo.ItemAsset.ToSoftObjectPath(), ItemInfo));
    }
    else
    {
        ItemAssetInfo = nullptr;
    }
}

void UInventorySlot::OnItemAssetLoaded(FSoftObjectPath AssetPath, FItemStructure ItemInfo)
{
    UObject* LoadedAsset = AssetPath.ResolveObject();

    if (LoadedAsset)
    {
        ItemAssetInfo = Cast<UItemInfo>(LoadedAsset);
        if (ItemAssetInfo)
        {
            double ItemWeight = ItemInfo.ItemQuantity * ItemAssetInfo->ItemWeight;
            FText NewWeightText = UKismetTextLibrary::Conv_DoubleToText(ItemWeight, HalfToEven, false, true, 1, 324, 1, 3);
            if (WeightText)
            {
                WeightText->SetText(NewWeightText);
                WeightText->SetVisibility(ESlateVisibility::Visible);
            }

            if (ItemIcon && ItemAssetInfo->ItemIcon)
            {
                ItemIcon->SetBrushFromTexture(ItemAssetInfo->ItemIcon);
                ItemIcon->SetVisibility(ESlateVisibility::Visible);
            }

            switch (ItemAssetInfo->ItemType) 
            {
            case EItemType::Resource:
                {
                    // Formated Text for Quantity
                    FFormatNamedArguments Args;
                    Args.Add(TEXT("Quantity"), FText::AsNumber(ItemInfo.ItemQuantity));
                    FText FormattedTextQuantity = FText::Format(NSLOCTEXT("InventorySlot", "QuantityFormat", "x{Quantity}"), Args);
                    if (QuantityText)
                    {
                        QuantityText->SetText(FormattedTextQuantity);
                        QuantityText->SetVisibility(ESlateVisibility::Visible);
                    }

                    if (TopText) TopText->SetVisibility(ESlateVisibility::Hidden);
                    if (BottomText) BottomText->SetVisibility(ESlateVisibility::Hidden);
                    if (ItemHP) ItemHP->SetVisibility(ESlateVisibility::Hidden);
                    break;
                }
            case EItemType::Equippable:
                {
                    // Formated Text for DMG
                    FFormatNamedArguments ArgsDMG;
                    ArgsDMG.Add(TEXT("ItemDamage"), FText::AsNumber(ItemAssetInfo->ItemDamage));
                    FText FormattedTextDamage = FText::Format(NSLOCTEXT("InventorySlot", "DamageFormat", "DMG {ItemDamage}%"), ArgsDMG);

                    // Formated Text for Ammo
                    FFormatNamedArguments ArgsAmmo;
                    ArgsAmmo.Add(TEXT("Current"), FText::AsNumber(ItemInfoData.CurrentAmmo));
                    ArgsAmmo.Add(TEXT("Max"), FText::AsNumber(ItemInfoData.MaxAmmo));
                    FText FormattedTextAmmo = FText::Format(NSLOCTEXT("InventorySlot", "AmmoFormat", "{Current}/{Max}"), ArgsAmmo);
                    if (TopText)
                    {
                        TopText->SetText(FormattedTextDamage);
                        TopText->SetVisibility(ESlateVisibility::Visible);
                        ItemHP->SetVisibility(ESlateVisibility::Visible);
                        float DamagePercent = ItemInfo.CurrentHP / ItemInfo.MaxHP;
                        ItemHP->SetPercent(DamagePercent);
                        QuantityText->SetVisibility(ESlateVisibility::Hidden);
                        
                        if (ItemAssetInfo->bUseAmmo)
                        {
                            BottomText->SetVisibility(ESlateVisibility::Visible);

                            BottomText->SetText(FormattedTextAmmo);
                        }
                        else
                        {
                            BottomText->SetVisibility(ESlateVisibility::Hidden);
                        }
                    }
                    break;
                }
            case EItemType::Armor:
                {
                    // Formated Text for Armor
                    FFormatNamedArguments ArgsArmor;
                    ArgsArmor.Add(TEXT("ArmorAmount"), FText::AsNumber(ItemAssetInfo->ItemDamage));
                    FText FormattedTextArmor = FText::Format(NSLOCTEXT("InventorySlot", "ArmorFormat", "{ArmorAmount}Armor"), ArgsArmor);
                    if (TopText)
                    {
                        TopText->SetText(FormattedTextArmor);
                        TopText->SetVisibility(ESlateVisibility::Visible);
                        ItemHP->SetVisibility(ESlateVisibility::Visible);
                        float ArmorPercent = ItemInfo.CurrentHP / ItemInfo.MaxHP;
                        ItemHP->SetPercent(ArmorPercent);
                        QuantityText->SetVisibility(ESlateVisibility::Hidden);
                        BottomText->SetVisibility(ESlateVisibility::Hidden);
                    }
                    break;
                }
            case EItemType::Consumable:
                {
                    // Formated Text for Quantity
                    FFormatNamedArguments Args;
                    Args.Add(TEXT("Quantity"), FText::AsNumber(ItemInfo.ItemQuantity));
                    FText FormattedTextQuantity = FText::Format(NSLOCTEXT("InventorySlot", "QuantityFormat", "x{Quantity}"), Args);
                    if (QuantityText)
                    {
                        QuantityText->SetText(FormattedTextQuantity);
                        QuantityText->SetVisibility(ESlateVisibility::Visible);
                        ItemHP->SetVisibility(ESlateVisibility::Visible);
                        float ConsumableAmount = ItemInfo.CurrentHP / ItemInfo.MaxHP;
                        ItemHP->SetPercent(ConsumableAmount);
                    }

                    if (TopText) TopText->SetVisibility(ESlateVisibility::Hidden);
                    if (BottomText) BottomText->SetVisibility(ESlateVisibility::Hidden);
                    break;
                }
            case EItemType::Buildable:
                {
                    // Formated Text for Quantity
                    FFormatNamedArguments Args;
                    Args.Add(TEXT("Quantity"), FText::AsNumber(ItemInfo.ItemQuantity));
                    FText FormattedTextQuantity = FText::Format(NSLOCTEXT("InventorySlot", "QuantityFormat", "x{Quantity}"), Args);
                    if (QuantityText)
                    {
                        QuantityText->SetText(FormattedTextQuantity);
                        QuantityText->SetVisibility(ESlateVisibility::Visible);
                    }

                    if (TopText) TopText->SetVisibility(ESlateVisibility::Hidden);
                    if (BottomText) BottomText->SetVisibility(ESlateVisibility::Hidden);
                    if (ItemHP) ItemHP->SetVisibility(ESlateVisibility::Hidden);
                    break;
                }
            default:
                break;
            }
        }
    }
}

void UInventorySlot::ResetSlot()
{
    BottomText->SetVisibility(ESlateVisibility::Hidden);
    ItemHP->SetVisibility(ESlateVisibility::Hidden);
    ItemIcon->SetVisibility(ESlateVisibility::Hidden);
    QuantityText->SetVisibility(ESlateVisibility::Hidden);
    TopText->SetVisibility(ESlateVisibility::Hidden);
    WeightText->SetVisibility(ESlateVisibility::Hidden);
    bHasItemInSlot = false;
    ItemInfoData = FItemStructure();
}

void UInventorySlot::DisplayItemInfoWidget()
{
    if (ULocalPlayer* LocalPlayer = GetOwningLocalPlayer())
    {
        UCommonInputSubsystem* CommonInputSubsystem = LocalPlayer->GetSubsystem<UCommonInputSubsystem>();

        if (CommonInputSubsystem)
        {
            ECommonInputType InputType = CommonInputSubsystem->GetCurrentInputType();
            
            if (InputType == ECommonInputType::Gamepad)
            {
                bAddedToFocusPath = true;
                
                GetWorld()->GetTimerManager().SetTimer(ItemInfoWidgetDelayHandle, this, &UInventorySlot::DisplayItemInfoWidgetDelay, 0.5f, false);
            }
        }
    }
}

void UInventorySlot::DisplayItemInfoWidgetDelay()
{
    switch (ContainerType) {
    case EContainerType::Inventory:
        DisplayItemInfoInventory();
        break;
    case EContainerType::HotBar:
        break;
    case EContainerType::Storage:
        break;
    case EContainerType::Armor:
        break;
    case EContainerType::Crafting:
        break;
    }
}

void UInventorySlot::DisplayItemInfoInventory()
{
    if (ItemInfoData.ItemAsset.ToSoftObjectPath().IsValid())
    {
        UItemInfo* LoadedAsset = ItemInfoData.ItemAsset.LoadSynchronous();
        if (LoadedAsset)
        {
            if (IsValid(LoadedAsset))
            {
                if (ItemInfoWidgetClass)
                {
                    ItemInfoWidget = CreateWidget<UItemInfoWidget>(GetOwningPlayer(), ItemInfoWidgetClass);

                    ItemInfoWidget->ItemNameText = LoadedAsset->ItemName;
                    FText ItemTypeText = StaticEnum<EItemType>()->GetDisplayValueAsText(LoadedAsset->ItemType);
                    ItemInfoWidget->ItemTypeText = ItemTypeText;
                    FText ItemRarityText = StaticEnum<EItemRarity>()->GetDisplayValueAsText(LoadedAsset->ItemRarity);
                    ItemInfoWidget->ItemRarityText = ItemRarityText;
                    ItemInfoWidget->ItemQuantityAmount = ItemInfoData.ItemQuantity;
                    ItemInfoWidget->ItemImage = LoadedAsset->ItemIcon;
                    ItemInfoWidget->ItemDescriptionText = LoadedAsset->ItemDescription;
                    ItemInfoWidget->ItemResourceType = LoadedAsset->ResourceType;
                    ItemInfoWidget->ItemStackSize = ItemInfoData.StackSize;
                    ItemInfoWidget->ItemLocationText = LoadedAsset->ItemLocationText;
                    ItemInfoWidget->GatherPercent = ItemInfoData.ItemQuantity / ItemInfoData.StackSize;
                    ItemInfoWidget->ItemTypes = LoadedAsset->ItemType;
                    ItemInfoWidget->bIsStackable = LoadedAsset->bIsStackable;
                    ItemInfoWidget->ItemDamageAmount = LoadedAsset->ItemDamage;
                    ItemInfoWidget->ItemCurrentHP = ItemInfoData.CurrentHP;
                    ItemInfoWidget->ItemMaxHP = ItemInfoData.MaxHP;
                    ItemInfoWidget->ItemRarityType = LoadedAsset->ItemRarity;
                    ItemInfoWidget->ItemToDestroy = ItemInfoData;
                    ItemInfoWidget->ItemIndex = ItemIndex;
                    ItemInfoWidget->ItemContainerType = ContainerType;
                    ItemInfoWidget->ItemSlotWidget = this;

                    FVector2D Size(400.f, 280.f);
                    ItemInfoWidget->SetDesiredSizeInViewport(Size);
                    FVector2D Plus(30.0f, -80.0f);
                    FVector2D CurrentPosition = GetCachedGeometry().GetAbsolutePosition();
                    FVector2D Position = CurrentPosition + Plus;
                    ItemInfoWidget->SetPositionInViewport(Position);
                    ItemInfoWidget->AddToViewport();
                    ItemInfoWidget->ActivateWidget();
                }
            }
        }
    }
}

void UInventorySlot::GetItemToolTip()
{
    if (ULocalPlayer* LocalPlayer = GetOwningLocalPlayer())
    {
        UCommonInputSubsystem* CommonInputSubsystem = LocalPlayer->GetSubsystem<UCommonInputSubsystem>();

        if (CommonInputSubsystem)
        {
            ECommonInputType InputType = CommonInputSubsystem->GetCurrentInputType();
            
            if (InputType == ECommonInputType::MouseAndKeyboard)
            {
                if (bHasItemInSlot)
                {
                    if (ItemInfoData.ItemAsset.ToSoftObjectPath().IsValid())
                    {
                        UItemInfo* LoadedAsset = ItemInfoData.ItemAsset.LoadSynchronous();
                        if (LoadedAsset)
                        {
                            if (IsValid(LoadedAsset))
                            {
                                if (ItemInfoWidgetClass)
                                {
                                    ItemInfoWidget = CreateWidget<UItemInfoWidget>(GetOwningPlayer(), ItemInfoWidgetClass);

                                    ItemInfoWidget->ItemNameText = LoadedAsset->ItemName;
                                    FText ItemTypeText = StaticEnum<EItemType>()->GetDisplayValueAsText(LoadedAsset->ItemType);
                                    ItemInfoWidget->ItemTypeText = ItemTypeText;
                                    FText ItemRarityText = StaticEnum<EItemRarity>()->GetDisplayValueAsText(LoadedAsset->ItemRarity);
                                    ItemInfoWidget->ItemRarityText = ItemRarityText;
                                    ItemInfoWidget->ItemQuantityAmount = ItemInfoData.ItemQuantity;
                                    ItemInfoWidget->ItemImage = LoadedAsset->ItemIcon;
                                    ItemInfoWidget->ItemDescriptionText = LoadedAsset->ItemDescription;
                                    ItemInfoWidget->ItemResourceType = LoadedAsset->ResourceType;
                                    ItemInfoWidget->ItemStackSize = ItemInfoData.StackSize;
                                    ItemInfoWidget->ItemLocationText = LoadedAsset->ItemLocationText;
                                    ItemInfoWidget->GatherPercent = ItemInfoData.ItemQuantity / ItemInfoData.StackSize;
                                    ItemInfoWidget->ItemTypes = LoadedAsset->ItemType;
                                    ItemInfoWidget->bIsStackable = LoadedAsset->bIsStackable;
                                    ItemInfoWidget->ItemDamageAmount = LoadedAsset->ItemDamage;
                                    ItemInfoWidget->ItemCurrentHP = ItemInfoData.CurrentHP;
                                    ItemInfoWidget->ItemMaxHP = ItemInfoData.MaxHP;
                                    ItemInfoWidget->ItemRarityType = LoadedAsset->ItemRarity;
                                    ItemInfoWidget->ItemToDestroy = ItemInfoData;
                                    ItemInfoWidget->ItemIndex = ItemIndex;
                                    ItemInfoWidget->ItemContainerType = ContainerType;
                                    ItemInfoWidget->ItemSlotWidget = this;
                                    ItemSlotSizeBox->SetToolTip(ItemInfoWidget);
                                    ItemInfoWidget->ActivateWidget();
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}







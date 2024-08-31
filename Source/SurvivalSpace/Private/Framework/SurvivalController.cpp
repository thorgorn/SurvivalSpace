// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/SurvivalController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Character/ASurvivalCharacter.h"
#include "Components/Inventory/Children/PlayerHotBar.h"
#include "Components/Inventory/Children/PlayerInventory.h"
#include "DataAssets/PrimaryAssets/ItemInfo.h"
#include "UI/Widgets/MainUILayout.h"
#include "UI/Widgets/Crafting/Crafting.h"
#include "UI/Widgets/Crafting/CraftingItemContainerGrid.h"
#include "UI/Widgets/Crafting/CraftingSlot.h"
#include "UI/Widgets/Hotbar/HotBarWidget.h"
#include "UI/Widgets/HUD/DefaultHUDLayout.h"
#include "UI/Widgets/HUD/GameInventoryLayout.h"
#include "UI/Widgets/Inventory/Inventory.h"
#include "UI/Widgets/Inventory/InventorySlot.h"
#include "UI/Widgets/Inventory/ItemContainerGrid.h"


void ASurvivalController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalPlayerController())
	{
		if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
			{
				
				if (DefaultMappingContext)
				{
					Subsystem->AddMappingContext(DefaultMappingContext, 0);
				}
			}
		}
	}

	SetupMainUIWidget();
}

void ASurvivalController::CloseInventory()
{
	GetWorld()->GetTimerManager().SetTimer(InventoryTimerHandle, this, &ASurvivalController::DelayOpenInventory, 0.1f, false);
}

void ASurvivalController::DestroyItem(int32 Index)
{
DestroyItemWidget(Index);
}

void ASurvivalController::ResetItemSlot(EContainerType Container, int32 Index)
{
	ResetOnClient(Container, Index);
}

void ASurvivalController::ResetCraftItemSlot(EContainerType Container, int32 Index)
{
	ResetCraftSlotOnClient(Container, Index);
}

void ASurvivalController::UpdateItemSlot(EContainerType Container, int32 Index, FItemStructure ItemInfo)
{
	UpdateSlotOnClient(Container, Index, ItemInfo);
}

void ASurvivalController::UpdateCraftItemSlot(EContainerType Container, int32 Index, FItemStructure ItemInfo)
{
	UpdateCraftingSlotOnClient(Index, ItemInfo);
}

void ASurvivalController::UpdateCraftResourceUI()
{
	UpdateCraftingUI();
}

void ASurvivalController::ShowItemCollected(UTexture2D* ResourceImage, int32 ResourceQuantity, FText ResourceName)
{
	ShowItemOnClient(ResourceImage, ResourceQuantity, ResourceName);
}

void ASurvivalController::ShowItemDestroyed(UTexture2D* ResourceImage, int32 ResourceQuantity, FText ResourceName)
{
	ShowItemDestroyOnClient(ResourceImage, ResourceQuantity, ResourceName);
}

void ASurvivalController::SetSelectedItem(EContainerType ContainerType, int32 SelectedIndex, bool ItemInFirstSlot,
	EArmorType ArmorType)
{
	if (bItemSelected)
	{
		
		if (AASurvivalCharacter* SurvivalCharacter = Cast<AASurvivalCharacter>(GetPawn()))
		{
			
			ISurvivalCharacterInterface* CharacterInterface = Cast<ISurvivalCharacterInterface>(SurvivalCharacter);
			if (CharacterInterface)
			{
				CharacterInterface->OnSlotDrop(ContainerType, SelectedContainer, SelectedItemIndex, SelectedIndex, ArmorType);

				bItemSelected = false;
			}
		}
	}
	else
	{
		if (ItemInFirstSlot)
		{
			bItemSelected = true;
			SelectedItemIndex = SelectedIndex;
			SelectedContainer = ContainerType;
			GetWorld()->GetTimerManager().SetTimer(SelectedItemTimerHandle, this, &ASurvivalController::ResetSelectedItemStatus, 5.0f, false);
		}
	}
}

void ASurvivalController::SetupCraftableItems(ECraftingType CraftingType, TArray<FSimpleItemStructure> ItemArray)
{
	CraftWidgetOnClient(CraftingType, ItemArray);
}

void ASurvivalController::DisplayCraftProgress()
{
	if (!RootLayout)
	{
		return;
	}

	RootLayout->GameInventoryLayout->ShowCraftingProgress();
}


void ASurvivalController::ResetSelectedItemStatus()
{
	bItemSelected = false;
}

void ASurvivalController::UpdateCraftingUI_Implementation()
{
	ISurvivalCharacterInterface* CharacterInterface = Cast<ISurvivalCharacterInterface>(GetPawn());
	if (CharacterInterface)
	{
		TObjectPtr<AASurvivalCharacter> CharRef;
		CharacterInterface->GetCharRef(CharRef);
		if (CharRef)
		{
			int32 CraftingIndex = 0; 
			
			for (int32 InventoryIndex = 0; InventoryIndex < CharRef->PlayerInventory->GetItems().Num(); ++InventoryIndex)
			{
				TSoftObjectPtr<UItemInfo> LoadedAsset = CharRef->PlayerInventory->GetItems()[InventoryIndex].ItemAsset.LoadSynchronous();

				if (LoadedAsset && LoadedAsset->ItemType == EItemType::Resource)
				{
					CharacterInterface->UpdateCraftItem(EContainerType::Crafting, CraftingIndex, CharRef->PlayerInventory->GetItems()[InventoryIndex]);
					CraftingIndex++;
				}
				else
				{
					CharacterInterface->ResetCraftItem(EContainerType::Crafting, CraftingIndex);
				}
			}

			
			for (int32 HotbarIndex = 0; HotbarIndex < CharRef->PlayerHotBar->GetItems().Num(); ++HotbarIndex)
			{
				TSoftObjectPtr<UItemInfo> LoadedAsset = CharRef->PlayerHotBar->GetItems()[HotbarIndex].ItemAsset.LoadSynchronous();

				if (LoadedAsset && LoadedAsset->ItemType == EItemType::Resource)
				{
					CharacterInterface->UpdateCraftItem(EContainerType::Crafting, CraftingIndex, CharRef->PlayerHotBar->GetItems()[HotbarIndex]);
					CraftingIndex++; 
				}
				else
				{
					CharacterInterface->ResetCraftItem(EContainerType::Crafting, CraftingIndex);
				}
			}
		}
	}
}


void ASurvivalController::UpdateHotBarUI_Implementation()
{
	ISurvivalCharacterInterface* CharacterInterface = Cast<ISurvivalCharacterInterface>(GetPawn());
	if (CharacterInterface)
	{
		TObjectPtr<AASurvivalCharacter> CharRef;
		CharacterInterface->GetCharRef(CharRef);
		if (CharRef)
		{
			for (int32 Index = 0; Index < CharRef->PlayerHotBar->GetItems().Num(); ++Index)
			{
				if (CharRef->PlayerHotBar->GetItems()[Index].ItemID == 0)
				{
					CharacterInterface->ResetItem(EContainerType::HotBar, Index);
				}
				else
				{
					CharacterInterface->UpdateItem(EContainerType::HotBar, Index, CharRef->PlayerHotBar->GetItems()[Index]);
				}
			}
		}
	}
}

void ASurvivalController::InventoryOnClient_Implementation()
{
	if (bInventoryShown)
	{
		FInputModeGameOnly GameInput;
		SetInputMode(GameInput);
		bInventoryShown = false;
		SetShowMouseCursor(false);
		SetIgnoreLookInput(false);
		SetIgnoreMoveInput(false);
		RootLayout->DefaultHUDLayout->HotBarWidget->SetVisibility(ESlateVisibility::Visible);
		UpdateHotBarUI();
	}
	else
	{
		if (RootLayoutClass)
		{
			RootLayout->PushGameInventoryLayout();
			RootLayout->DefaultHUDLayout->HotBarWidget->SetVisibility(ESlateVisibility::Collapsed);
			FInputModeUIOnly InputMode;
			SetInputMode(InputMode);
			bInventoryShown = true;
			SetShowMouseCursor(true);
		}
	}
}

void ASurvivalController::DelayOpenInventory()
{
	InventoryOnClient();
}

void ASurvivalController::OpenInventory()
{
	GetWorld()->GetTimerManager().SetTimer(InventoryTimerHandle, this, &ASurvivalController::DelayOpenInventory, 0.1f, false);
}

void ASurvivalController::SetupMainUIWidget()
{
	if (RootLayoutClass)
	{
		
		if (!HasAuthority())
		{
			RootLayout = CreateWidget<UMainUILayout>(this, RootLayoutClass);
			if (RootLayout)
			{
				RootLayout->AddToViewport();
				RootLayout->PushDefaultHUDLayout();
				InitialiseInventoryWidget();
			}
		}
		else
		{
			if (IsLocalPlayerController())
			{
				RootLayout = CreateWidget<UMainUILayout>(this, RootLayoutClass);
				if (RootLayout)
				{
					RootLayout->AddToViewport();
					RootLayout->PushDefaultHUDLayout();
					InitialiseInventoryWidget();
				}
			}
		}
	}
}

void ASurvivalController::DestroyItemWidget_Implementation(int32 ItemIndex)
{
	
	if (AASurvivalCharacter* SurvivalCharacter = Cast<AASurvivalCharacter>(GetPawn()))
	{
		
		ISurvivalCharacterInterface* CharacterInterface = Cast<ISurvivalCharacterInterface>(SurvivalCharacter);
		if (CharacterInterface)
		{
			CharacterInterface->DestroyItem(ItemIndex);
			UpdateCraftingUI();
		}
	}
}


void ASurvivalController::InitialiseInventoryWidget()
{
	if (RootLayoutClass)
	{
		RootLayout->PushGameInventoryLayout();
		
		bInventoryShown = true;
		
		if (RootLayout->GameInventoryLayout)
		{
			RootLayout->GameInventoryLayout->DeactivateWidget();
		}
	}	
}

void ASurvivalController::ShowItemDestroyOnClient_Implementation(UTexture2D* InIcon, int32 InQuantity,
	const FText& InName)
{
	if (RootLayout)
	{
		if (RootLayout->DefaultHUDLayout)
		{
			RootLayout->DefaultHUDLayout->RemoveResource(InIcon, InQuantity, InName);
		}
	}
}

void ASurvivalController::ShowItemOnClient_Implementation(UTexture2D* InIcon, int32 InQuantity, const FText& InName)
{
	if (RootLayout)
	{
		if (RootLayout->DefaultHUDLayout)
		{
			RootLayout->DefaultHUDLayout->AddResource(InIcon, InQuantity, InName);
		}
	}
}


void ASurvivalController::UpdateSlotOnClient_Implementation(EContainerType Container, int32 Index,
                                                            FItemStructure ItemInfo)
{
	TObjectPtr<UInventorySlot> Widget = nullptr;

	GetInventoryWidget(Container, Index, Widget);

	if (Widget)
	{
		Widget->UpdateSlot(ItemInfo);
	}
}

void ASurvivalController::CraftWidgetOnClient_Implementation(ECraftingType CraftingType, const TArray<FSimpleItemStructure>& ItemsArray) const
{
	RootLayout->GameInventoryLayout->UpdateCraftWidget(CraftingType, ItemsArray);
}


void ASurvivalController::GetInventoryWidget(EContainerType Container, int32 SlotIndex, TObjectPtr<UInventorySlot>& ItemSlot)
{
	ItemSlot = nullptr;

	if (!RootLayoutClass)
	{
		return;
	}
    
	switch (Container)
	{
	case EContainerType::Inventory:
		if (!RootLayout)
		{
			return;
		}

		ItemSlot = RootLayout->GameInventoryLayout->InventoryWidget->ItemContainerGrid->GetSlots()[SlotIndex];
		break;

	case EContainerType::HotBar:
		if (!RootLayout)
		{
			return;
		}
		if (bInventoryShown)
		{
			ItemSlot = RootLayout->GameInventoryLayout->HotBarWidget->ItemContainerGrid->GetSlots()[SlotIndex];
		}
		else
		{
			ItemSlot = RootLayout->DefaultHUDLayout->HotBarWidget->ItemContainerGrid->GetSlots()[SlotIndex];
		}
		break;
	case EContainerType::Storage:
		// Implement logic for Storage
			break;
	case EContainerType::Armor:
		// Implement logic for Armor
			break;
	default:
		break;
	}
}

void ASurvivalController::GetCraftingItemWidget(int32 SlotIndex, TObjectPtr<UCraftingSlot>& CraftingSlot)
{
	CraftingSlot = nullptr;

	if (!RootLayoutClass)
	{
		return;
	}

	CraftingSlot = RootLayout->GameInventoryLayout->CraftingWidget->CraftingItemContainerGrid->GetSlots()[SlotIndex];
}

void ASurvivalController::ResetCraftSlotOnClient_Implementation(EContainerType Container, int32 Index)
{
	TObjectPtr<UCraftingSlot> Widget = nullptr;

	GetCraftingItemWidget(Index, Widget);

	if (Widget)
	{
		Widget->ResetSlot();
	}
}

void ASurvivalController::UpdateCraftingSlotOnClient_Implementation(int32 Index, FItemStructure ItemInfo)
{
	TObjectPtr<UCraftingSlot> CraftingSlot = nullptr;
	GetCraftingItemWidget(Index, CraftingSlot);

	if (CraftingSlot)
	{
		TSoftObjectPtr<UItemInfo> LoadedAsset = ItemInfo.ItemAsset.LoadSynchronous();
		if (LoadedAsset && LoadedAsset->ItemType == EItemType::Resource)
		{
			CraftingSlot->UpdateSlot(ItemInfo);
		}
		else
		{
			CraftingSlot->ResetSlot();
		}
	}
}


void ASurvivalController::ResetOnClient_Implementation(EContainerType Container, int32 Index)
{
	TObjectPtr<UInventorySlot> ItemSlot = nullptr;

	GetInventoryWidget(Container, Index, ItemSlot);

	if (ItemSlot)
	{
		ItemSlot->ResetSlot();
	}
}

void ASurvivalController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent)
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
		{
			EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &ASurvivalController::OpenInventory);
		}
	}
}
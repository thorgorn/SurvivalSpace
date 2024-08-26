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
				// Add default mapping context
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
	if (ItemSelected)
	{
		// GetOwner returns a pointer to the owning character
		if (AASurvivalCharacter* SurvivalCharacter = Cast<AASurvivalCharacter>(GetPawn()))
		{
			// Check if the character implements the ISurvivalCharacterInterface
			ISurvivalCharacterInterface* CharacterInterface = Cast<ISurvivalCharacterInterface>(SurvivalCharacter);
			if (CharacterInterface)
			{
				CharacterInterface->OnSlotDrop(ContainerType, SelectedContainer, SelectedItemIndex, SelectedIndex, ArmorType);
				UE_LOG(LogTemp, Warning, TEXT("SetSelectedItem Controller called"));
				UE_LOG(LogTemp, Warning, TEXT("Container Type = %s, SelectedContainer = %s, SelectedItemIndex = %d, SelectedIndex = %d"), 
									*UEnum::GetValueAsString(ContainerType),
									*UEnum::GetValueAsString(SelectedContainer),
									SelectedItemIndex,
									SelectedIndex);
				ItemSelected = false;
			}
		}
	}
	else
	{
		if (ItemInFirstSlot)
		{
			ItemSelected = true;
			SelectedItemIndex = SelectedIndex;
			SelectedContainer = ContainerType;
			GetWorld()->GetTimerManager().SetTimer(SelectedItemTimerHandle, this, &ASurvivalController::ResetSelectedItemStatus, 5.0f, false);
		}
	}
}

void ASurvivalController::SetupCraftableItems(ECraftingType CraftingType, TArray<FItem> ItemArray)
{
	CraftWidgetOnClient(CraftingType, ItemArray);
}


void ASurvivalController::ResetSelectedItemStatus()
{
	ItemSelected = false;
	//UE_LOG(LogTemp, Warning, TEXT("ResetSelectedItem Controller called"));
}

void ASurvivalController::UpdateCraftingUI_Implementation()
{
	ISurvivalCharacterInterface* CharacterInterface = Cast<ISurvivalCharacterInterface>(GetPawn());
	if (CharacterInterface)
	{
		AASurvivalCharacter* CharRef;
		CharacterInterface->GetCharRef(CharRef);
		if (CharRef)
		{
			int32 CraftingIndex = 0;  // Index for the crafting grid slots

			// Check PlayerInventory for resource items
			for (int32 InventoryIndex = 0; InventoryIndex < CharRef->PlayerInventory->Items.Num(); ++InventoryIndex)
			{
				UItemInfo* LoadedAsset = CharRef->PlayerInventory->Items[InventoryIndex].ItemAsset.LoadSynchronous();

				if (LoadedAsset && LoadedAsset->ItemType == EItemType::Resource)
				{
					CharacterInterface->UpdateCraftItem(EContainerType::Crafting, CraftingIndex, CharRef->PlayerInventory->Items[InventoryIndex]);
					CraftingIndex++;  // Increment crafting index only when a resource is placed
				}
				else
				{
					CharacterInterface->ResetCraftItem(EContainerType::Crafting, CraftingIndex);
				}
			}

			// Check PlayerHotbar for resource items
			for (int32 HotbarIndex = 0; HotbarIndex < CharRef->PlayerHotBar->Items.Num(); ++HotbarIndex)
			{
				UItemInfo* LoadedAsset = CharRef->PlayerHotBar->Items[HotbarIndex].ItemAsset.LoadSynchronous();

				if (LoadedAsset && LoadedAsset->ItemType == EItemType::Resource)
				{
					CharacterInterface->UpdateCraftItem(EContainerType::Crafting, CraftingIndex, CharRef->PlayerHotBar->Items[HotbarIndex]);
					CraftingIndex++;  // Increment crafting index only when a resource is placed
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
		AASurvivalCharacter* CharRef;
		CharacterInterface->GetCharRef(CharRef);
		if (CharRef)
		{
			for (int32 Index = 0; Index < CharRef->PlayerHotBar->Items.Num(); ++Index)
			{
				if (CharRef->PlayerHotBar->Items[Index].ItemID == 0)
				{
					CharacterInterface->ResetItem(EContainerType::HotBar, Index);
				}
				else
				{
					CharacterInterface->UpdateItem(EContainerType::HotBar, Index, CharRef->PlayerHotBar->Items[Index]);
				}
			}
		}
	}
}

void ASurvivalController::InventoryOnClient_Implementation()
{
	if (InventoryShown)
	{
		FInputModeGameOnly GameInput;
		SetInputMode(GameInput);
		InventoryShown = false;
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
			InventoryShown = true;
			SetShowMouseCursor(true);
			//UpdateCraftingUI();
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
		// Create the widget if this is a remote controller
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
		else // HasAuthority() is true, which includes listen server and dedicated server
		{
			// Ensure this is a local player controller (including the host in a listen server setup)
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
	// GetOwner returns a pointer to the owning character
	if (AASurvivalCharacter* SurvivalCharacter = Cast<AASurvivalCharacter>(GetPawn()))
	{
		// Check if the character implements the ISurvivalCharacterInterface
		ISurvivalCharacterInterface* CharacterInterface = Cast<ISurvivalCharacterInterface>(SurvivalCharacter);
		if (CharacterInterface)
		{
			CharacterInterface->DestroyItem(ItemIndex);
			//UE_LOG(LogTemp, Warning, TEXT("DestroyItem Controller called"));
		}
	}
}


void ASurvivalController::InitialiseInventoryWidget()
{
	if (RootLayoutClass)
	{
		RootLayout->PushGameInventoryLayout();
		InventoryShown = true;
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
		// Assuming DefaultHUDLayout is a member of RootLayout and AddResource is a method in DefaultHUDLayout
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
		// Assuming DefaultHUDLayout is a member of RootLayout and AddResource is a method in DefaultHUDLayout
		if (RootLayout->DefaultHUDLayout)
		{
			RootLayout->DefaultHUDLayout->AddResource(InIcon, InQuantity, InName);
		}
	}
}


void ASurvivalController::UpdateSlotOnClient_Implementation(EContainerType Container, int32 Index,
                                                            FItemStructure ItemInfo)
{
	UInventorySlot* Widget = nullptr;

	GetInventoryWidget(Container, Index, Widget);

	if (Widget)
	{
		Widget->UpdateSlot(ItemInfo);
	}
}

void ASurvivalController::CraftWidgetOnClient_Implementation(ECraftingType CraftingType, const TArray<FItem>& ItemsArray) const
{
	RootLayout->GameInventoryLayout->UpdateCraftWidget(CraftingType, ItemsArray);
}


void ASurvivalController::GetInventoryWidget(EContainerType Container, int32 SlotIndex, UInventorySlot*& Widget)
{
	Widget = nullptr;

	if (!RootLayoutClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("RootLayoutClass is not valid"));
		return;
	}
    
	switch (Container)
	{
	case EContainerType::Inventory:
		if (!RootLayout)
		{
			return;
		}

		Widget = RootLayout->GameInventoryLayout->InventoryWidget->ItemContainerGrid->Slots[SlotIndex];
		break;

	case EContainerType::HotBar:
		if (!RootLayout)
		{
			return;
		}
		if (InventoryShown)
		{
			Widget = RootLayout->GameInventoryLayout->HotBarWidget->ItemContainerGrid->Slots[SlotIndex];
		}
		else
		{
			Widget = RootLayout->DefaultHUDLayout->HotBarWidget->ItemContainerGrid->Slots[SlotIndex];
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

void ASurvivalController::GetCraftingItemWidget(int32 SlotIndex, UCraftingSlot*& Widget)
{
	Widget = nullptr;

	if (!RootLayoutClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("RootLayoutClass is not valid"));
		return;
	}

	Widget = RootLayout->GameInventoryLayout->CraftingWidget->CraftingItemContainerGrid->Slots[SlotIndex];
}

void ASurvivalController::ResetCraftSlotOnClient_Implementation(EContainerType Container, int32 Index)
{
	UCraftingSlot* Widget = nullptr;

	GetCraftingItemWidget(Index, Widget);

	if (Widget)
	{
		Widget->ResetSlot();
	}
}

void ASurvivalController::UpdateCraftingSlotOnClient_Implementation(int32 Index, FItemStructure ItemInfo)
{
	UCraftingSlot* Widget = nullptr;
	GetCraftingItemWidget(Index, Widget);

	if (Widget)
	{
		UItemInfo* LoadedAsset = ItemInfo.ItemAsset.LoadSynchronous();
		if (LoadedAsset && LoadedAsset->ItemType == EItemType::Resource)
		{
			Widget->UpdateSlot(ItemInfo);
		}
		else
		{
			Widget->ResetSlot(); // Reset the slot if it's not a resource item
		}
	}
}


void ASurvivalController::ResetOnClient_Implementation(EContainerType Container, int32 Index)
{
	UInventorySlot* Widget = nullptr;

	GetInventoryWidget(Container, Index, Widget);

	if (Widget)
	{
		Widget->ResetSlot();
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
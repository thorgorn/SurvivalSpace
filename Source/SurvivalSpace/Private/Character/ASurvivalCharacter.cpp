// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ASurvivalCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/Inventory/Children/PlayerHotBar.h"
#include "Components/Inventory/Children/PlayerInventory.h"
#include "DataAssets/PrimaryAssets/HarvestingResource.h"
#include "DataAssets/PrimaryAssets/ItemInfo.h"
#include "Framework/SurvivalController.h"
#include "Interfaces/ControllerInterface.h"
#include "Interfaces/EquippableItemInterface.h"
#include "Interfaces/GroundItemInterface.h"
#include "Interfaces/InteractableInterface.h"
#include "Items/ItemMaster.h"
#include "HarvestingSystem/DestructableHarvestableMaster.h"
#include "Kismet/GameplayStatics.h"


AASurvivalCharacter::AASurvivalCharacter()
{
	FPSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("FPSpringArm");
	FPSpringArmComponent->SetupAttachment(GetMesh(), FName("head"));
	
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	FirstPersonCamera->SetupAttachment(FPSpringArmComponent);

	TPSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("TPSpringArm");
	TPSpringArmComponent->SetupAttachment(GetMesh());
	
	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>("TPCameraComponent");
	ThirdPersonCamera->SetupAttachment(TPSpringArmComponent);

	PlayerInventory = CreateDefaultSubobject<UPlayerInventory>("PlayerInventory");
	PlayerHotBar = CreateDefaultSubobject<UPlayerHotBar>("PlayerHotBar");

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;
}

void AASurvivalCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AASurvivalCharacter, CurrentState);
	DOREPLIFETIME(AASurvivalCharacter, EquippedState);
	DOREPLIFETIME(AASurvivalCharacter, ResourceEffectsArray);
}

void AASurvivalCharacter::BeginPlay()
{
	Super::BeginPlay();

	ControllerRef = Cast<ASurvivalController>(GetController());
}

void AASurvivalCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AASurvivalCharacter::ToggleFirstPerson()
{
	FirstPersonCamera->SetActive(true);
	ThirdPersonCamera->SetActive(false);
	bFirstPersonActive = true;
}

void AASurvivalCharacter::ToggleThirdPerson()
{
	ThirdPersonCamera->SetActive(true);
	FirstPersonCamera->SetActive(false);
	bFirstPersonActive = false;
}

void AASurvivalCharacter::SwitchCamera()
{
	if (!ControllerRef->bInventoryShown)
	{
		if (!bFirstPersonActive)
		{
			ToggleFirstPerson();
		}
		else
		{
			ToggleThirdPerson();
		}
	}
}

void AASurvivalCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation{0, Rotation.Yaw, 0};

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(RightDirection, MovementVector.X);
	AddMovementInput(ForwardDirection, MovementVector.Y);
	
}

void AASurvivalCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
	
}


void AASurvivalCharacter::StartJump()
{	
	if (!ControllerRef->bInventoryShown)
	{
		if (CurrentState == ECharacterStates::Idle)
		{
			Jump();
		}
	}
}

void AASurvivalCharacter::ToggleCrouch()
{
	if (!ControllerRef->bInventoryShown)
	{
		if (!GetCharacterMovement()->IsFalling())
		{
			ClientCrouch();
		}
	}
}

void AASurvivalCharacter::ClientCrouch()
{
	if (HasAuthority())
	{
		if (CurrentState == ECharacterStates::Proning)
		{
			CurrentState = ECharacterStates::Idle;
			OnRep_CharacterState();
		}

		CurrentState = (CurrentState == ECharacterStates::Crouching) ? ECharacterStates::Idle : ECharacterStates::Crouching;
		OnRep_CharacterState();
	}
	else
	{
		CrouchOnServer();
	}
}

void AASurvivalCharacter::CrouchOnServer_Implementation()
{
	if (CurrentState == ECharacterStates::Proning)
	{
		CurrentState = ECharacterStates::Idle;
		OnRep_CharacterState();
	}

	CurrentState = (CurrentState == ECharacterStates::Crouching) ? ECharacterStates::Idle : ECharacterStates::Crouching;
	OnRep_CharacterState();
}

void AASurvivalCharacter::OnRep_CharacterState()
{
	switch (CurrentState)
	{
	case ECharacterStates::Crouching:
		GetCharacterMovement()->MaxWalkSpeed = 230.0f;
		break;
	case ECharacterStates::Proning:
		GetCharacterMovement()->MaxWalkSpeed = 100.0f;
		break;
	default:
		GetCharacterMovement()->MaxWalkSpeed = 335.0f;
		break;
	}
}

void AASurvivalCharacter::ToggleProne()
{
	if (!ControllerRef->bInventoryShown)
	{
		ClientProne();
	}
}

void AASurvivalCharacter::ClientProne()
{
	if (HasAuthority())
	{
		if (CurrentState == ECharacterStates::Crouching)
		{
			CurrentState = ECharacterStates::Idle;
			OnRep_CharacterState();
		}

		CurrentState = (CurrentState == ECharacterStates::Proning) ? ECharacterStates::Idle : ECharacterStates::Proning;
		OnRep_CharacterState();
	}
	else
	{
		ProneOnServer();
	}
}


void AASurvivalCharacter::ProneOnServer_Implementation()
{
	if (CurrentState == ECharacterStates::Crouching)
	{
		CurrentState = ECharacterStates::Idle;
		OnRep_CharacterState();
	}

	CurrentState = (CurrentState == ECharacterStates::Proning) ? ECharacterStates::Idle : ECharacterStates::Proning;
	OnRep_CharacterState();
}

void AASurvivalCharacter::GetAnimationStates(ECharacterStates& OutCurrentState, EEquippableState& OutEquippableState)
{
	OutCurrentState = CurrentState;
	OutEquippableState = EquippedState;
}

void AASurvivalCharacter::UpdateItem(EContainerType Container, int32 Index, FItemStructure ItemInfo)
{
	if (APlayerController* PlayerController = GetController<APlayerController>())
	{
		IControllerInterface* ControllerInterface = Cast<IControllerInterface>(PlayerController);
		if (ControllerInterface)
		{
			ControllerInterface->UpdateItemSlot(Container, Index, ItemInfo);
		}
	}
}

void AASurvivalCharacter::UpdateCraftItem(EContainerType Container, int32 Index, FItemStructure ItemInfo)
{
	UItemInfo* LoadedAsset = ItemInfo.ItemAsset.LoadSynchronous();
	if (LoadedAsset && LoadedAsset->ItemType == EItemType::Resource)
	{
		if (APlayerController* PlayerController = GetController<APlayerController>())
		{
			IControllerInterface* ControllerInterface = Cast<IControllerInterface>(PlayerController);
			if (ControllerInterface)
			{
				ControllerInterface->UpdateCraftItemSlot(Container, Index, ItemInfo);
			}
		}
	}
}

void AASurvivalCharacter::OnSlotDrop(EContainerType TargetContainer, EContainerType FromContainer, int32 FromIndex,
                                     int32 DroppedIndex, EArmorType ArmorType)
{
	SlotDropOnServer(TargetContainer, FromContainer, FromIndex, DroppedIndex, ArmorType);
}

void AASurvivalCharacter::ResetItem(EContainerType Container, int32 Index)
{
	if (APlayerController* PlayerController = GetController<APlayerController>())
	{
		IControllerInterface* ControllerInterface = Cast<IControllerInterface>(PlayerController);
		if (ControllerInterface)
		{
			ControllerInterface->ResetItemSlot(Container, Index);
		}
	}
}

void AASurvivalCharacter::ResetCraftItem(EContainerType Container, int32 Index)
{
	if (APlayerController* PlayerController = GetController<APlayerController>())
	{
		IControllerInterface* ControllerInterface = Cast<IControllerInterface>(PlayerController);
		if (ControllerInterface)
		{
			ControllerInterface->ResetCraftItemSlot(Container, Index);
		}
	}
}

void AASurvivalCharacter::UpdateCraftResourcesUI()
{
	if (APlayerController* PlayerController = GetController<APlayerController>())
	{
		IControllerInterface* ControllerInterface = Cast<IControllerInterface>(PlayerController);
		if (ControllerInterface)
		{
			ControllerInterface->UpdateCraftResourceUI();
		}
	}
}

void AASurvivalCharacter::ThirdPersonMontage(UAnimMontage* Montage)
{
	MontageMultiCast(Montage);
}

void AASurvivalCharacter::GetCameraRotation(FRotator& Rotation) const
{
	if (bFirstPersonActive)
	{
		Rotation = FirstPersonCamera->GetComponentRotation();
	}
	else
	{
		Rotation = ThirdPersonCamera->GetComponentRotation();
	}
}

void AASurvivalCharacter::GetCameraLocation(FVector& Location) const
{
	Location = FirstPersonCamera->GetComponentLocation();
}

void AASurvivalCharacter::HarvestItem(FItemStructure Resource)
{

	HarvestLargeItem(Resource);
}

void AASurvivalCharacter::DestroyItem(int32 Index)
{
	if (PlayerInventory)
	{
		UItemsContainerMaster* ContainerMaster = Cast<UItemsContainerMaster>(PlayerInventory);

		if (ContainerMaster)
		{
			ContainerMaster->RemoveItemAtIndex(Index);
		}
	}
}

void AASurvivalCharacter::GetHitFXInfo(FVector HitLocation, EResourceType ResourceType)
{
	MultiCastHarvestItemFX(HitLocation, ResourceType);
}

void AASurvivalCharacter::DoublePressSlot(EContainerType ContainerType, int32 Index)
{
	DoublePressOnServer(ContainerType, Index);
}

void AASurvivalCharacter::GetCharRef(TObjectPtr<AASurvivalCharacter> &CharRef)
{
	CharRef = this;
}

void AASurvivalCharacter::GetCraftingRecipesAndItems(ECraftingType CraftingType)
{
	GetItemsOnServer(CraftingType);
}

void AASurvivalCharacter::GetItemsOnServer_Implementation(ECraftingType CraftingType)
{
	
	IControllerInterface* ControllerInterface = Cast<IControllerInterface>(GetController());
	
	switch (CraftingType) {
	case ECraftingType::PlayerInventory:
		if (ControllerInterface)
		{
			TArray<FItem> ItemsArray = PlayerInventory->GetItemQuantities();
			ControllerInterface->SetupCraftableItems(CraftingType, ItemsArray);
		}
		break;
	case ECraftingType::CookingPot:
		break;
	case ECraftingType::CraftingBench:
		break;
	case ECraftingType::SmeltingForge:
		break;
	case ECraftingType::AdvancedWorkBench:
		break;
	case ECraftingType::StorageBox:
		break;
	case ECraftingType::CropPlot:
		break;
	}
}

void AASurvivalCharacter::HarvestLargeItem(FItemStructure Resource)
{
	PlayerInventory->AddItemOnServer_Implementation(Resource);

	if (APlayerController* PlayerController = GetController<APlayerController>())
	{
		IControllerInterface* ControllerInterface = Cast<IControllerInterface>(PlayerController);
		if (ControllerInterface)
		{
			if (Resource.ItemAsset.ToSoftObjectPath().IsValid())
			{
				UItemInfo* LoadedAsset = Resource.ItemAsset.LoadSynchronous();
				if (LoadedAsset)
				{
					ControllerInterface->ShowItemCollected(LoadedAsset->ItemIcon, Resource.ItemQuantity, LoadedAsset->ItemName);
				}
			}
			else
			{
			}
		}
	}
}

void AASurvivalCharacter::Interact()
{
	FRotator InteractRotation;
	GetCameraRotation(InteractRotation);
	InteractOnServer(InteractRotation);
}

void AASurvivalCharacter::Interaction(FRotator CameraRotation)
{
	if (!bIsHarvesting || !bIsDead)
	{
		bIsHarvesting = true;

		FVector LocalCamLocation = FirstPersonCamera->GetComponentLocation();

		float LocalInteractDistance = 200.0f;
		FVector StartTrace = LocalCamLocation;
		FVector EndTrace = CameraRotation.Vector() * LocalInteractDistance + LocalCamLocation;
		
		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);
		
		FCollisionShape CollisionShape;
		CollisionShape.SetSphere(20.0f);
		
		bool bHit = GetWorld()->SweepSingleByChannel(
			HitResult,
			StartTrace,
			EndTrace,
			FQuat::Identity,
			ECC_Camera,
			CollisionShape,
			CollisionParams
			);
		
		if (bHit)
		{
			if (HitResult.GetActor()->Implements<UInteractableInterface>())
			{
				if (HitResult.GetActor()->Implements<UGroundItemInterface>())
				{
					if (IsValid(EquipItemRef))
					{
						// Setup a widget notification to tell player to put tool away
						bIsHarvesting = false;
					}
					else
					{
						IGroundItemInterface* GroundItemInterface = Cast<IGroundItemInterface>(HitResult.GetActor());
						if (GroundItemInterface)
						{
							EResourceType ResourceType;
							GroundItemInterface->GetResourceType(ResourceType);
							UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
							if (AnimInstance && !AnimInstance->Montage_IsPlaying(InteractMontage))
							{
								HarvestGroundItem(HitResult.GetActor());
								MontageMultiCast(InteractMontage);
								MultiCastHarvestItemFX(HitResult.ImpactPoint, ResourceType);
							}
							bIsHarvesting = false;
						}
					}
				}
				else
				{
					bIsHarvesting = false;
				}
			}
			else
			{
				bIsHarvesting = false;
			}
		}
		else
		{
			bIsHarvesting = false;
		}
	}
}


void AASurvivalCharacter::HarvestGroundItem(AActor* Actor)
{
	IGroundItemInterface* GroundItemInterface = Cast<IGroundItemInterface>(Actor);
	if (GroundItemInterface)
	{
		float GroundItemHealth;
		
		TSoftObjectPtr<UHarvestingResource> GroundItemResource;
		
		GroundItemInterface->GetResourceHealth(GroundItemHealth);
		
		float LocalGroundItemHealth = GroundItemHealth - 15.0f;
		
		if (LocalGroundItemHealth <= 0.0f)
		{
			GroundItemInterface->GetGivenResources(GroundItemResource);
			
			if (GroundItemResource.ToSoftObjectPath().IsValid())
			{
				UHarvestingResource* LoadedAsset = GroundItemResource.LoadSynchronous();
				if (LoadedAsset)
				{
					AddResources(LoadedAsset->GivenItems);
					
					TSoftClassPtr<ADestructableHarvestableMaster> LocalDestructableClass = LoadedAsset->DestructableClass;
					
					if (IsValid(Actor))
					{
						FTransform LocalActorTransform = Actor->GetTransform();
						Actor->Destroy();
						
						TSubclassOf<ADestructableHarvestableMaster> ItemClass = LocalDestructableClass.LoadSynchronous();
						if (ItemClass)
						{
							GetWorld()->SpawnActor<AActor>(ItemClass, LocalActorTransform);
						}
					}
				}
			}
		}
		else
		{
			GroundItemInterface->UpdateHealth(LocalGroundItemHealth);
			GroundItemInterface->GetGivenResources(GroundItemResource);
			
			if (GroundItemResource.ToSoftObjectPath().IsValid())
			{
				UHarvestingResource* LoadedAsset = GroundItemResource.LoadSynchronous();
				if (LoadedAsset)
				{
					ResourceEffectsArray = LoadedAsset->ResourceEffectsArray;
					AddResources(LoadedAsset->GivenItems);
				}
			}
		}
	}
}

void AASurvivalCharacter::AddResources(TArray<FResourceStructure> GivenResources)
{
	TArray<FResourceStructure> LocalGivenResources = GivenResources;

	for (const FResourceStructure& ResourceStruct : LocalGivenResources)
	{
		FResourceStructure LocalResourceStruct = ResourceStruct;

		TSoftObjectPtr<UItemInfo> LocalResourceToAdd = ResourceStruct.Resource;

		float BaseVar = ResourceStruct.Quantity;

		float RateVar = 1.0f;

		float RandomVar = FMath::RandRange(0.3f, 1.2f);

		float Result = BaseVar * RateVar * RandomVar;

		int32 LocalResourceQuantity = Result;

		if (LocalResourceQuantity > 0)
		{
			if (LocalResourceToAdd.ToSoftObjectPath().IsValid())
			{
				UItemInfo* LoadedAsset = LocalResourceToAdd.LoadSynchronous();
				if (LoadedAsset)
				{
					FItemStructure  NewItemToAdd;
					
					NewItemToAdd.ItemID = LoadedAsset->ItemID;
					NewItemToAdd.ItemQuantity = LocalResourceQuantity;
					NewItemToAdd.ItemAsset = LocalResourceToAdd;
					NewItemToAdd.CurrentHP = LoadedAsset->ItemCurrentHP;
					NewItemToAdd.MaxHP = LoadedAsset->ItemMaxHP;
					NewItemToAdd.StackSize = LoadedAsset->StackSize;

					PlayerInventory->AddItemOnServer_Implementation(NewItemToAdd);

					IControllerInterface* ControllerInterface = Cast<IControllerInterface>(GetController());
					{
						if (ControllerInterface)
						{
							ControllerInterface->ShowItemCollected(LoadedAsset->ItemIcon, LocalResourceQuantity, LoadedAsset->ItemName);
						}
					}
				}
			}
		}
	}
}

void AASurvivalCharacter::MultiCastHarvestItemFX_Implementation(FVector HitLocation, EResourceType ResourceType)
{
	const FResourceEffects* ResourceEffects = ResourceEffectsArray.FindByPredicate(
		[&](const FResourceEffects& Effects)
		{
			return Effects.ResourceType == ResourceType;
		});
	
	if (ResourceEffects)
	{
		if (ResourceEffects->VFX)
		{
			UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(),
				ResourceEffects->VFX,
				HitLocation,
				FRotator::ZeroRotator,
				FVector(1.0f, 1.0f, 1.0f),
				true
			);
		}

		if (ResourceEffects->SFX)
		{
			UGameplayStatics::PlaySoundAtLocation(
				GetWorld(),
				ResourceEffects->SFX,
				HitLocation,
				1.0f,
				1.0f,
				0.0f,
				HarvestSoundAttenuation
			);
		}
	}
}

void AASurvivalCharacter::InteractOnServer_Implementation(FRotator CameraRotation)
{
	Interaction(CameraRotation);
}

void AASurvivalCharacter::SlotDrop(EContainerType TargetContainer, EContainerType FromContainer, int32 FromIndex,
                                   int32 DroppedIndex, EArmorType ArmorType)
{
	if (!PlayerInventory)
	{
		return;
	}

	// Select Target Container
	UItemsContainerMaster* SelectedTargetContainer = nullptr;
	switch (TargetContainer)
	{
	case EContainerType::Inventory:
		SelectedTargetContainer = PlayerInventory;
		break;
	case EContainerType::HotBar:
		SelectedTargetContainer = PlayerHotBar;
		break;
	case EContainerType::Storage:

		break;
	case EContainerType::Armor:

		break;
	default:
		break;
	}

	// Select From Container
	UItemsContainerMaster* SelectedFromContainer = nullptr;
	switch (FromContainer)
	{
	case EContainerType::Inventory:
		SelectedFromContainer = PlayerInventory;
		break;
	case EContainerType::HotBar:
		SelectedFromContainer = PlayerHotBar;
		break;
	case EContainerType::Storage:

		break;
	case EContainerType::Armor:

		break;
	default:
		break;
	}
	
	if (IsValid(SelectedTargetContainer) && IsValid(SelectedFromContainer))
	{
		// Check if the item is being moved from the hotbar and is currently equipped
		if (FromContainer == EContainerType::HotBar && IsEquippedItemInHotbar(FromIndex))
		{
			UnequipItem(FromIndex);
		}
		
		// Call OnSlotDrop on the target container
		SelectedTargetContainer->OnSlotDrop(SelectedFromContainer, FromIndex, DroppedIndex);
	}
}


void AASurvivalCharacter::DoublePressOnServer_Implementation(EContainerType ContainerType, int32 Index)
{
	UItemsContainerMaster* SelectedTargetContainer = nullptr;
	switch (ContainerType)
	{
	case EContainerType::Inventory:
		SelectedTargetContainer = PlayerInventory;
		break;
	case EContainerType::HotBar:
		SelectedTargetContainer = PlayerHotBar;
		break;
	case EContainerType::Storage:

		break;
	case EContainerType::Armor:

		break;
	default:
		break;
	}

	if (IsValid(SelectedTargetContainer))
	{
		if (SelectedTargetContainer->IsSlotEmpty(Index))
		{
			
		}
		else
		{
			FItemStructure ItemInfo =SelectedTargetContainer->GetItemAtIndex(Index);
			if (ItemInfo.ItemAsset.ToSoftObjectPath().IsValid())
			{
				UItemInfo* LoadedAsset = ItemInfo.ItemAsset.LoadSynchronous();
				if (LoadedAsset)
				{
					switch (ContainerType) {
					case EContainerType::Inventory:
						PlayerHotBar->TransferItemHotKey(PlayerInventory, Index);
						break;
					case EContainerType::HotBar:
						PlayerInventory->TransferItemHotKey(PlayerHotBar, Index);
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
}


void AASurvivalCharacter::SlotDropOnServer_Implementation(EContainerType TargetContainer, EContainerType FromContainer,
                                                          int32 FromIndex, int32 DroppedIndex, EArmorType ArmorType)
{
	SlotDrop(TargetContainer, FromContainer, FromIndex, DroppedIndex, ArmorType);
}



void AASurvivalCharacter::HotBarOnServer_Implementation(int32 Index)
{
	UseHotBar(Index);
}

void AASurvivalCharacter::HotBarTriggered(int32 Index)
{
	HotBarOnServer(Index);
}

void AASurvivalCharacter::UseHotBar(int32 Index)
{
	if (!bUsingItem)
	{
		HotBarIndex = Index;

		if (PlayerHotBar)
		{
			bool bHasItemInSlot;
			EItemType ItemType;
			PlayerHotBar->CheckHotBar(Index, bHasItemInSlot, ItemType);

			if (bHasItemInSlot)
			{
				switch (ItemType)
				{
				case EItemType::Resource:
					break;
				case EItemType::Equippable:
					if (IsValid(EquipItemRef))
					{
						EquipItemRef->Destroy();
						MulticastDeEquipItem();
					}
					else
					{
						FItemStructure ItemInfo = PlayerHotBar->GetItemAtIndex(Index);
						
						UItemInfo* LoadedAsset = ItemInfo.ItemAsset.LoadSynchronous();
						if (LoadedAsset)
						{
							ResourceEffectsArray = LoadedAsset->ResourceEffectsArray;
							TSubclassOf<AItemMaster> ItemClass = LoadedAsset->ItemClassRef.LoadSynchronous();
							if (ItemClass)
							{
								SpawnEquippableOnServer(ItemClass, HotBarIndex);
								UAnimMontage* MontageData = ItemInfo.ItemAsset->AttackMontage.LoadSynchronous();
								if (MontageData)
								{
									EquippedItemAttackMontage = MontageData;
								}
							}
						}
					}
					break;
				case EItemType::Armor:
					break;
				case EItemType::Consumable:
					break;
				case EItemType::Buildable:
					break;
				}
			}
		}
	}
}


void AASurvivalCharacter::SpawnEquippableOnServer_Implementation(TSubclassOf<AActor> Class, int32 EquippedIndex)
{
	SpawnEquipItem(Class, EquippedIndex);
}

void AASurvivalCharacter::MultiCastEquipItem_Implementation(AActor* Target, FName SocketName,
	EEquippableState InEquippedState)
{
	AttachItem(Target, SocketName, InEquippedState);
}

void AASurvivalCharacter::MulticastDeEquipItem_Implementation()
{
	EquippedState = EEquippableState::Default;
}

void AASurvivalCharacter::SpawnEquipItem(TSubclassOf<AActor> Class, int32 EquippedIndex)
{
	EquippedItemIndex = EquippedIndex;
	
	FTransform SpawnTransform;
	
	SpawnTransform.SetLocation(FVector::ZeroVector);
	
	SpawnTransform.SetRotation(FQuat::Identity);
	
	SpawnTransform.SetScale3D(FVector::OneVector);
	
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(Class, SpawnTransform);
	if (SpawnedActor)
	{
		EquipItemRef = SpawnedActor;
		EquipItemRef->SetOwner(this);
		
		IEquippableItemInterface* EquippableInterface = Cast<IEquippableItemInterface>(EquipItemRef);
		if (EquippableInterface)
		{
			FName NewSocketName;
			EEquippableState NewEquippedState;
			
			EquippableInterface->GetEquippableInfo(NewSocketName, NewEquippedState);
			
			MultiCastEquipItem(EquipItemRef, NewSocketName, NewEquippedState);
		}
	}
}

void AASurvivalCharacter::AttachItem(AActor* ActorRef, FName SocketName, EEquippableState InEquippedState)
{
	if (IsValid(ActorRef))
	{
		ActorRef->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
		EquippedState = InEquippedState;
	}
}

void AASurvivalCharacter::LeftMouseOnServer_Implementation()
{
	if (IsValid(EquipItemRef))
	{
		IEquippableItemInterface* EquippableInterface = Cast<IEquippableItemInterface>(EquipItemRef);
		if (EquippableInterface)
		{
			if (EquippedItemAttackMontage)
			{
				EquippableInterface->UseItem(this, EquippedItemAttackMontage);
				bUsingItem = true;
			}
		}
	}
	else
	{
		bUsingItem = false;
	}
}

void AASurvivalCharacter::MontageMultiCast_Implementation(UAnimMontage* Montage)
{
	if (Montage)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance)
		{
			FOnMontageEnded MontageEndedDelegate;
			MontageEndedDelegate.BindUObject(this, &AASurvivalCharacter::OnMontageEnded);

			AnimInstance->Montage_Play(Montage);
			AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, Montage);
			
			AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &AASurvivalCharacter::OnNotifyBegin);
		}
		else
		{
			bUsingItem = false;
		}
	}
	else
	{
		bUsingItem = false;
	}
}

void AASurvivalCharacter::OnNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->OnPlayMontageNotifyBegin.RemoveDynamic(this, &AASurvivalCharacter::OnNotifyBegin);
	}
	if (IsValid(EquipItemRef))
	{
		IEquippableItemInterface* EquippableInterface = Cast<IEquippableItemInterface>(EquipItemRef);
		if (EquippableInterface)
		{
			EquippableInterface->NotifyInterface();
			if (AnimInstance)
			{
				AnimInstance->OnPlayMontageNotifyBegin.RemoveDynamic(this, &AASurvivalCharacter::OnNotifyBegin);
			}
		}
	}
}

void AASurvivalCharacter::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->OnPlayMontageNotifyBegin.RemoveDynamic(this, &AASurvivalCharacter::OnNotifyBegin);
	}
	
	if (!bInterrupted)
	{
		if (IsValid(EquipItemRef))
		{
			IEquippableItemInterface* EquippableInterface = Cast<IEquippableItemInterface>(EquipItemRef);
			if (EquippableInterface)
			{
				EquippableInterface->EndAnimation();
			}
		}
	}
	bUsingItem = false;
}

void AASurvivalCharacter::OnRep_EquippedState()
{
	switch (EquippedState) {
	case EEquippableState::Default:
		break;
	case EEquippableState::Hatchet:
		break;
	case EEquippableState::Bow:
		break;
	case EEquippableState::Rock:
		break;
	case EEquippableState::Rifle:
		break;
	case EEquippableState::RocketLauncher:
		break;
	case EEquippableState::Spear:
		break;
	case EEquippableState::Swimming:
		break;
	}
}

bool AASurvivalCharacter::IsEquippedItemInHotbar(int32 Index) const
{
	if (!EquipItemRef || !PlayerHotBar) {
		return false;
	}

	
	FItemStructure HotbarItem = PlayerHotBar->GetItemAtIndex(Index);

	if (HotbarItem.ItemAsset.ToSoftObjectPath().IsValid())
	{
		UItemInfo* LoadedAsset = HotbarItem.ItemAsset.LoadSynchronous();
		if (LoadedAsset)
		{
			TSubclassOf<AActor> ItemClass = LoadedAsset->ItemClassRef.LoadSynchronous();
			if (ItemClass)
			{
				return EquipItemRef->IsA(ItemClass);
			}
		}
	}
	return false;
}

void AASurvivalCharacter::UnequipItem(int32 Index)
{
	if (IsEquippedItemInHotbar(Index))
	{
		if (EquipItemRef)
		{
			EquipItemRef->Destroy();
			EquipItemRef = nullptr;
			MulticastDeEquipItem();
			
			EquippedState = EEquippableState::Default;
			OnRep_EquippedState();
		}
	}
}

void AASurvivalCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent)
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AASurvivalCharacter::Move);
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AASurvivalCharacter::Look);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AASurvivalCharacter::StartJump);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AASurvivalCharacter::StopJumping);
			EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AASurvivalCharacter::Interact);
			EnhancedInputComponent->BindAction(FirstPersonAction, ETriggerEvent::Triggered, this, &AASurvivalCharacter::ToggleFirstPerson);
			EnhancedInputComponent->BindAction(SwitchCameraAction, ETriggerEvent::Triggered, this, &AASurvivalCharacter::SwitchCamera);
			EnhancedInputComponent->BindAction(ThirdPersonAction, ETriggerEvent::Triggered, this, &AASurvivalCharacter::ToggleThirdPerson);
			EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &AASurvivalCharacter::ToggleCrouch);
			EnhancedInputComponent->BindAction(ProneAction, ETriggerEvent::Triggered, this, &AASurvivalCharacter::ToggleProne);
			EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AASurvivalCharacter::LeftMouseOnServer);
			EnhancedInputComponent->BindAction(HotBarAction1, ETriggerEvent::Triggered, this, &AASurvivalCharacter::HotBarTriggered, 0);
			EnhancedInputComponent->BindAction(HotBarAction2, ETriggerEvent::Triggered, this, &AASurvivalCharacter::HotBarTriggered, 1);
			EnhancedInputComponent->BindAction(HotBarAction3, ETriggerEvent::Triggered, this, &AASurvivalCharacter::HotBarTriggered, 2);
			EnhancedInputComponent->BindAction(HotBarAction4, ETriggerEvent::Triggered, this, &AASurvivalCharacter::HotBarTriggered, 3);
			EnhancedInputComponent->BindAction(HotBarAction5, ETriggerEvent::Triggered, this, &AASurvivalCharacter::HotBarTriggered, 4);
			EnhancedInputComponent->BindAction(HotBarAction6, ETriggerEvent::Triggered, this, &AASurvivalCharacter::HotBarTriggered, 5);
			EnhancedInputComponent->BindAction(HotBarAction7, ETriggerEvent::Triggered, this, &AASurvivalCharacter::HotBarTriggered, 6);
			EnhancedInputComponent->BindAction(HotBarAction8, ETriggerEvent::Triggered, this, &AASurvivalCharacter::HotBarTriggered, 7);
			
		}
	}
}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/Enums.h"
#include "GameFramework/Character.h"
#include "Interfaces/SurvivalCharacterInterface.h"
#include "ASurvivalCharacter.generated.h"

class ASurvivalController;
class UPlayerHotBar;
class UItemsContainerMaster;
class UPlayerInventory;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class SURVIVALSPACE_API AASurvivalCharacter : public ACharacter, public ISurvivalCharacterInterface
{
	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------------------------
	// CHARACTER CONSTRUCTOR
	//--------------------------------------------------------------------------------------------
	AASurvivalCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sockets")
	FName InitialEquipSocketName;

	UPROPERTY(BlueprintReadWrite, Category = "HotBar Data")
	TObjectPtr<AActor> HolsteredItemRef;

	bool bIsItemEquipped; 

protected:

	//--------------------------------------------------------------------------------------------
	// CHARACTER FUNCTIONS
	//--------------------------------------------------------------------------------------------
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//--------------------------------------------------------------------------------------------
	// CHARACTER PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UCameraComponent> FirstPersonCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USpringArmComponent> FPSpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UCameraComponent> ThirdPersonCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USpringArmComponent> TPSpringArmComponent;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UPlayerInventory> PlayerInventory;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UPlayerHotBar> PlayerHotBar;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller Ref")
	TObjectPtr<ASurvivalController> ControllerRef;


	
	//--------------------------------------------------------------------------------------------
	// CHARACTER INPUT MAPPING & ACTIONS 
	//--------------------------------------------------------------------------------------------
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> InteractAction;


	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> FirstPersonAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> ThirdPersonAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> SwitchCameraAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> CrouchAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> ProneAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> AttackAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> HotBarAction1;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> HotBarAction2;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> HotBarAction3;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> HotBarAction4;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> HotBarAction5;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> HotBarAction6;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> HotBarAction7;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> HotBarAction8;
	
	//--------------------------------------------------------------------------------------------
	// TOGGLE CAMERA FUNCTIONS
	//--------------------------------------------------------------------------------------------

	UFUNCTION(BlueprintCallable, Category = "ToggleCameraFunctions")
	void ToggleFirstPerson();

	UFUNCTION(BlueprintCallable, Category = "ToggleCameraFunctions")
	void ToggleThirdPerson();

	UFUNCTION(BlueprintCallable, Category = "ToggleCameraFunctions")
	void SwitchCamera();
	
	//--------------------------------------------------------------------------------------------
	// CAMERA FUNCTION VARIABLES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(BlueprintReadWrite, Category = "ToggleCameraVariables")
	bool bFirstPersonActive = true;
	
	//--------------------------------------------------------------------------------------------
	// CHARACTER MOVEMENT FUNCTIONS
	//--------------------------------------------------------------------------------------------

	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void Look(const FInputActionValue& Value);

	UFUNCTION()
	void StartJump();

	UFUNCTION()
	void ToggleCrouch();
	
	UFUNCTION(BlueprintCallable, Category = "CharacterMovementFunctions")
	void ClientCrouch();

	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "CharacterMovementFunctions")
	void CrouchOnServer();
	
	UFUNCTION()
	void OnRep_CharacterState();
	
	UFUNCTION()
	void ToggleProne();

	UFUNCTION(BlueprintCallable, Category = "CharacterMovementFunctions")
	void ClientProne();

	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "CharacterMovementFunctions")
	void ProneOnServer();
	
	
	//--------------------------------------------------------------------------------------------
	// CHARACTER MOVEMENT VARIABLES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(BlueprintReadWrite, Category = "CharacterMovementVariables", ReplicatedUsing=OnRep_CharacterState)
	ECharacterStates CurrentState = ECharacterStates::Idle;
	
	//--------------------------------------------------------------------------------------------
	// CHARACTER MONTAGE VARIABLES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvest Montages")
	TObjectPtr<UAnimMontage> InteractMontage;
	
	//--------------------------------------------------------------------------------------------
	// CHARACTER INTERFACE FUNCTIONS
	//--------------------------------------------------------------------------------------------

	virtual void GetAnimationStates(ECharacterStates& OutCurrentState, EEquippableState& OutEquippableState) override;

	virtual void UpdateItem(EContainerType Container, int32 Index, FItemStructure ItemInfo) override;

	virtual void UpdateCraftItem(EContainerType Container, int32 Index, FItemStructure ItemInfo) override;

	virtual void OnSlotDrop(EContainerType TargetContainer, EContainerType FromContainer, int32 FromIndex, int32 DroppedIndex, EArmorType ArmorType) override;

	virtual void ResetItem(EContainerType Container, int32 Index) override;

	virtual void ResetCraftItem(EContainerType Container, int32 Index) override;

	virtual void UpdateCraftResourcesUI() override;

	virtual void ThirdPersonMontage(UAnimMontage* Montage) override;

	virtual void GetCameraRotation(FRotator& Rotation) const override;

	virtual void GetCameraLocation(FVector& Location) const override;

	virtual void HarvestItem(FItemStructure Resource) override;

	virtual void DestroyItem(int32 Index) override;

	virtual void GetHitFXInfo(FVector HitLocation, EResourceType ResourceType) override;

	virtual void DoublePressSlot(EContainerType ContainerType, int32 Index) override;

	virtual void GetCharRef(AASurvivalCharacter*& Ref) override;

	virtual void GetCraftingRecipesAndItems(ECraftingType CraftingType) override;

	//--------------------------------------------------------------------------------------------
	// CHARACTER CRAFTING FUNCTIONS
	//--------------------------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable, Server, Unreliable, Category = "Character Crafting Functions")
	void GetItemsOnServer(ECraftingType CraftingType);
	//--------------------------------------------------------------------------------------------
	// CHARACTER HARVEST FUNCTIONS
	//--------------------------------------------------------------------------------------------

	UFUNCTION(BlueprintCallable, Category = "Character Harvest Functions")
	void HarvestLargeItem(FItemStructure Resource);

	UFUNCTION(BlueprintCallable,Server, Unreliable, Category = "Character Harvest Functions")
	void InteractOnServer(FRotator CameraRotation);

	UFUNCTION(BlueprintCallable, Category = "Character Harvest Functions")
	void Interact();

	UFUNCTION(BlueprintCallable, Category = "Character Harvest Functions")
	void Interaction(FRotator CameraRotation);

	UFUNCTION(BlueprintCallable, Category = "Character Harvest Functions")
	void HarvestGroundItem(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "Character Harvest Functions")
	void AddResources(TArray<FResourceStructure> GivenResources);

	UFUNCTION(BlueprintCallable, NetMulticast, Unreliable, Category = "Character Harvest Functions")
	void MultiCastHarvestItemFX(FVector HitLocation, EResourceType ResourceType);
	

	//--------------------------------------------------------------------------------------------
	// CHARACTER HARVEST PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Harvest Data")
	bool bIsHarvesting = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Harvest Data")
	bool bIsDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Harvest Data")
	TObjectPtr<USoundAttenuation> HarvestSoundAttenuation;

	UPROPERTY(Replicated)
	TArray<FResourceEffects> ResourceEffectsArray;
	//--------------------------------------------------------------------------------------------
	// CHARACTER ITEM SLOT FUNCTIONS
	//--------------------------------------------------------------------------------------------
	
	UFUNCTION(BlueprintCallable, Server, Unreliable, Category = "Inventory Functions")
	void SlotDropOnServer(EContainerType TargetContainer, EContainerType FromContainer, int32 FromIndex, int32 DroppedIndex, EArmorType ArmorType);

	UFUNCTION(BlueprintCallable, Category = "Inventory Functions")
	void SlotDrop(EContainerType TargetContainer, EContainerType FromContainer, int32 FromIndex,
	int32 DroppedIndex, EArmorType ArmorType);

	UFUNCTION(BlueprintCallable, Server, Unreliable, Category = "Inventory Functions")
	void DoublePressOnServer(EContainerType ContainerType, int32 Index);
	
	//--------------------------------------------------------------------------------------------
	// CHARACTER HOTBAR FUNCTIONS
	//--------------------------------------------------------------------------------------------

	UFUNCTION(BlueprintCallable, Server, Unreliable, Category = "Character HotBar Functions")
	void HotBarOnServer(int32 Index);
	
	UFUNCTION()
	void HotBarTriggered(int32 Index);

	UFUNCTION(BlueprintCallable, Category = "Character HotBar Functions")
	void UseHotBar(int32 Index);

	UFUNCTION(BlueprintCallable, Server, Unreliable, Category = "Character HotBar Functions")
	void SpawnEquippableOnServer(TSubclassOf<AActor> Class, int32 EquippedIndex);

	UFUNCTION(BlueprintCallable, NetMulticast, Unreliable, Category = "Character HotBar Functions")
	void MultiCastEquipItem(AActor* Target, FName SocketName, EEquippableState InEquippedState);

	UFUNCTION(BlueprintCallable, NetMulticast, Unreliable, Category = "Character HotBar Functions")
	void MulticastDeEquipItem();

	UFUNCTION(BlueprintCallable, Category = "Character HotBar Functions")
	void SpawnEquipItem(TSubclassOf<AActor> Class, int32 EquippedIndex);

	UFUNCTION(BlueprintCallable, Category = "Character HotBar Functions")
	void AttachItem(AActor* ActorRef, FName SocketName, EEquippableState InEquippedState);
	
	//--------------------------------------------------------------------------------------------
	// CHARACTER HOTBAR PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(BlueprintReadWrite, Category = "HotBar Data")
	bool bUsingItem = false;

	UPROPERTY(BlueprintReadWrite, Category = "HotBar Data")
	int32 HotBarIndex;
	
	//--------------------------------------------------------------------------------------------
	// CHARACTER EQUIPPED ITEM FUNCTIONS
	//--------------------------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable, Server, Unreliable, Category = "Character Attack Item Functions")
	void LeftMouseOnServer();

	UFUNCTION(BlueprintCallable, NetMulticast, Unreliable, Category = "Character Attack Item Functions")
	void MontageMultiCast(UAnimMontage* Montage);

	UFUNCTION()
	void OnNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
	void OnRep_EquippedState();

	UFUNCTION(BlueprintCallable)
	bool IsEquippedItemInHotbar(int32 Index) const;

	UFUNCTION(BlueprintCallable)
	void UnequipItem(int32 Index);
	
	//--------------------------------------------------------------------------------------------
	// CHARACTER EQUIPPED ITEM PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(BlueprintReadWrite, Category = "HotBar Data")
	TObjectPtr<AActor> EquipItemRef;

	UPROPERTY(BlueprintReadWrite, Category = "HotBar Data")
	int32 EquippedItemIndex;
	
	UPROPERTY(BlueprintReadWrite, Category = "CharacterMovementVariables", ReplicatedUsing=OnRep_EquippedState)
	EEquippableState EquippedState = EEquippableState::Default;

	//--------------------------------------------------------------------------------------------
	// CHARACTER EQUIPPED ITEM MONTAGES
	//--------------------------------------------------------------------------------------------

	UPROPERTY()
	TObjectPtr<UAnimMontage> EquippedItemAttackMontage;
};

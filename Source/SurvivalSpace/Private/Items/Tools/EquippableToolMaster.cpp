// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.


#include "Items/Tools/EquippableToolMaster.h"

#include "GameFramework/Character.h"
#include "Interfaces/LargeItemInterface.h"
#include "Interfaces/SurvivalCharacterInterface.h"

AEquippableToolMaster::AEquippableToolMaster()
{
	// Create the DefaultSceneRoot component and set it as the root
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(DefaultSceneRoot);

	// Create the StaticMesh component and attach it to the DefaultSceneRoot
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(DefaultSceneRoot);
}

void AEquippableToolMaster::UseItem(AActor* CharacterRef, UAnimMontage* MontageToPlay)
{
	if (bUsingItem)
	{
		// Do nothing
	}
	else
	{
		bUsingItem = true;
		CharRef = CharacterRef;

		if (IsValid(MontageToPlay))
		{
			if (ACharacter* Character = Cast<ACharacter>(CharRef))
			{
				ISurvivalCharacterInterface* CharacterInterface = Cast<ISurvivalCharacterInterface>(Character);
				if (CharacterInterface)
				{
					CharacterInterface->ThirdPersonMontage(MontageToPlay);
				}
			}
		}
		else
		{
			MontageToPlay = nullptr;
			EndAnimation();
		}
	}
}

void AEquippableToolMaster::EndAnimation()
{
	bUsingItem = false;
}

void AEquippableToolMaster::NotifyInterface()
{
	GetRotationClient();
}

void AEquippableToolMaster::GetRotationClient_Implementation()
{
	if (ACharacter* Character = Cast<ACharacter>(GetOwner()))
	{
		ISurvivalCharacterInterface* CharacterInterface = Cast<ISurvivalCharacterInterface>(Character);
		if (CharacterInterface)
		{
			FRotator Rotation;
			CharacterInterface->GetCameraRotation(Rotation);
			OverLapOnServer(Rotation);
		}
	}
}

void AEquippableToolMaster::OverLapOnServer_Implementation(FRotator InRotator)
{
	OverLap(InRotator);
}

void AEquippableToolMaster::OverLap(FRotator Rotation)
{
	FRotator LocalCameraRotation = Rotation;

	if (IsValid(CharRef))
	{
		if (ACharacter* Character = Cast<ACharacter>(CharRef))
		{
			ISurvivalCharacterInterface* CharacterInterface = Cast<ISurvivalCharacterInterface>(Character);
			if (CharacterInterface)
			{
				FVector LocalCameraLocation;
				CharacterInterface->GetCameraLocation(LocalCameraLocation);
            	
				float LocalInteractDistance = 200.0f;
				FVector StartTrace = LocalCameraLocation;
				FVector EndTrace = LocalCameraRotation.Vector() * LocalInteractDistance + LocalCameraLocation;

				FHitResult HitResult;
				FCollisionQueryParams CollisionParams;
				CollisionParams.AddIgnoredActor(this);
				CollisionParams.AddIgnoredActor(Character);
				
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
            	
				if (bHit && HitResult.GetActor()->Implements<ULargeItemInterface>())
				{
					//HarvestFoliage(ItemDamage, HitResult.GetActor(), HitResult.ImpactPoint);
					ILargeItemInterface* LargeItemInterface = Cast<ILargeItemInterface>(HitResult.GetActor());
					if (LargeItemInterface)
					{
						LargeItemInterface->HarvestFoliage(ItemDamage, ToolType, ToolTier, CharRef);
						EResourceType ItemResourceType;
						LargeItemInterface->GetResourceType(ItemResourceType);
						if (CharacterInterface)
						{
							CharacterInterface->GetHitFXInfo(HitResult.ImpactPoint, ItemResourceType);
							
							// Add rumble effect here
							APawn* PawnRef = Cast<APawn>(CharRef);
							if (PawnRef)
							{
								APlayerController* PlayerController = Cast<APlayerController>(PawnRef->GetController());
								if (PlayerController)
								{
									// Parameters: intensity, duration, flag for affecting large motors, flag for affecting small motors
									PlayerController->PlayDynamicForceFeedback(0.5f, 0.3f, true, true, true, true);
								}
							}
						}
					}
				}
			}
		}
	}
}

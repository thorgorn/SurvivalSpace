// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.


#include "Interfaces/EquippableItemInterface.h"

// Add default functionality here for any IEquippableItemInterface functions that are not pure virtual.
void IEquippableItemInterface::GetEquippableInfo(FName& OutSocketName, EEquippableState& OutAnimationState)
{
}

void IEquippableItemInterface::GetInitialSocketInfo(FName& InitialSocket)
{
}

void IEquippableItemInterface::UseItem(AActor* CharacterRef, UAnimMontage* MontageToPlay)
{
}

void IEquippableItemInterface::EndAnimation()
{
}

void IEquippableItemInterface::NotifyInterface()
{
}

void IEquippableItemInterface::GetAttackMontage(UAnimMontage* &AttackMontage)
{
}

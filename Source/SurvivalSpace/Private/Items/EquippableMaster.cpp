// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.


#include "Items/EquippableMaster.h"

void AEquippableMaster::GetEquippableInfo(FName& OutSocketName, EEquippableState& OutAnimationState)
{
	OutSocketName = SocketName;
	OutAnimationState = AnimationState;
}

void AEquippableMaster::GetInitialSocketInfo(FName& InitialSocket)
{
	InitialSocket = InitialSocketName;
}

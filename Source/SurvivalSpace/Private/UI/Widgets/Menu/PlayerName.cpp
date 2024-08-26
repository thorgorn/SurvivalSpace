// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.


#include "UI/Widgets/Menu/PlayerName.h"

#include "Components/TextBlock.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/KismetTextLibrary.h"

void UPlayerName::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(GetOwningPlayerState()))
	{
		FText PlayerName = UKismetTextLibrary::Conv_StringToText(GetOwningPlayerState()->GetPlayerName());
		PlayerNameText->SetText(PlayerName);
	}
}

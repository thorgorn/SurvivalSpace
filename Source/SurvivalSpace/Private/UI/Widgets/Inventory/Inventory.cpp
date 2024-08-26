// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Inventory/Inventory.h"
#include "Character/ASurvivalCharacter.h"
#include "Components/TextBlock.h"
#include "Components/Inventory/Children/PlayerInventory.h"
#include "Interfaces/SurvivalCharacterInterface.h"
#include "Kismet/GameplayStatics.h"

class ISurvivalCharacterInterface;

void UInventory::NativeConstruct()
{
	Super::NativeConstruct();

	if (ISurvivalCharacterInterface* CharacterInterface = Cast<ISurvivalCharacterInterface>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		TObjectPtr<AASurvivalCharacter> SurvivalCharacter = nullptr;
		
		CharacterInterface->GetCharRef(SurvivalCharacter);

		if (SurvivalCharacter)
		{
			FFormatNamedArguments Args;
			Args.Add(TEXT("Amount"), SurvivalCharacter->PlayerInventory->GetItems().Num());
			FText FormattedTextAmount = FText::Format(NSLOCTEXT("Slots", "AmountFormat", "({Amount} SLOTS)"), Args);
			
			SlotText->SetText(FormattedTextAmount);
		}
	}
}

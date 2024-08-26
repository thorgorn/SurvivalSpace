// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Common/Buttons/CommonButton.h"

#include "Components/TextBlock.h"

void UCommonButton::NativeConstruct()
{
	Super::NativeConstruct();

	//if (bUseText)
	//{
		//DefaultText->SetText(ButtonText);
	//}
}

void UCommonButton::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (bUseText)
	{
		DefaultText->SetText(ButtonText);
	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "CommonButton.generated.h"

class UBorder;
class UTextBlock;
/**
 * 
 */
UCLASS()
class SURVIVALSPACE_API UCommonButton : public UCommonButtonBase
{
	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------------------------
	// BUTTON FUNCTIONS
	//--------------------------------------------------------------------------------------------
	virtual void NativeConstruct() override;

	virtual void NativePreConstruct() override;
	//--------------------------------------------------------------------------------------------
	// BUTTON PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UTextBlock> DefaultText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta=(ExposeOnSpawn))
	bool bUseText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta=(ExposeOnSpawn))
	FText ButtonText;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UBorder> SelectedImage;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "ActivatableWidgetStackCustom.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALSPACE_API UActivatableWidgetStackCustom : public UCommonActivatableWidgetStack
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "ActivatableWidgetStack")
	UCommonActivatableWidget* PushWidgetInstance(UCommonActivatableWidget* WidgetInstance, bool& success);
	
};

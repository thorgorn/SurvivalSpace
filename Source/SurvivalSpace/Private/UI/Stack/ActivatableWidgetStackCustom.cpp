// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Stack/ActivatableWidgetStackCustom.h"

UCommonActivatableWidget* UActivatableWidgetStackCustom::PushWidgetInstance(UCommonActivatableWidget* WidgetInstance,
	bool& success)
{
	if (ensure(WidgetInstance && !WidgetList.Contains(WidgetInstance)))
	{
		WidgetList.Add(WidgetInstance);
		OnWidgetAddedToList(*WidgetInstance);
		success = true;
		return WidgetInstance;
	}
	else
	{
		success = false;
		return nullptr;
	}
}

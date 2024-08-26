// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.


#include "UI/Widgets/Menu/WidgetInfo.h"

#include "Components/TextBlock.h"

void UWidgetInfo::UpdateText(FText WidgetName, FText WidgetDescription)
{
	WidgetInfoText->SetText(WidgetName);
	WidgetInfoDescription->SetText(WidgetDescription);
}

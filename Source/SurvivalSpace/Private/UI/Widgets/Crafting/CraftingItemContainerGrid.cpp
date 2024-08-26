// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.


#include "UI/Widgets/Crafting/CraftingItemContainerGrid.h"

#include "Character/ASurvivalCharacter.h"
#include "Components/ScrollBox.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/Inventory/Children/PlayerInventory.h"
#include "DataAssets/PrimaryAssets/ItemInfo.h"
#include "Framework/SurvivalController.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/Widgets/Crafting/CraftingSlot.h"

void UCraftingItemContainerGrid::NativeConstruct()
{
	Super::NativeConstruct();

	if (bShowScrollBar)
	{
		ScrollBox->SetAlwaysShowScrollbar(true);
	}
	else
	{
		ScrollBox->SetAlwaysShowScrollbar(false);
	}
	
}

void UCraftingItemContainerGrid::AddSlots(int32 Amount)
{
	if (!CraftingSlotClass) return;

	for (int32 Index = 0; Index < Amount; ++Index)
	{
		CraftingSlot = CreateWidget<UCraftingSlot>(GetWorld(), CraftingSlotClass);
		if (CraftingSlot) 
		{
			CraftingSlot->ContainerType = ContainerType;
			CraftingSlot->Parent = this;
			
			CraftingSlot->ItemIndex = Slots.Emplace(CraftingSlot);

			AddSlotToGrid(CraftingSlot->ItemIndex, CraftingSlot);
		}
	}
}

void UCraftingItemContainerGrid::AddSlotToGrid(int32 Index, UCraftingSlot* CraftingItemSlot)
{
	if (IsValid(CraftingItemSlot))
	{
		if (TObjectPtr<UUniformGridSlot> GridSlot = Grid->AddChildToUniformGrid(CraftingItemSlot); IsValid(GridSlot))
		{
			int32 SlotsPerRowValue = SlotsPerRow;
	
			double LocalSlotIndexAsDouble = UKismetMathLibrary::Conv_IntToDouble(Index);
			double SlotsPerRowAsDouble = UKismetMathLibrary::Conv_IntToDouble(SlotsPerRowValue);

			double Remainder;
			int32 ReturnValue = UKismetMathLibrary::FMod(LocalSlotIndexAsDouble, SlotsPerRowAsDouble, Remainder);
			int32 Column = UKismetMathLibrary::FTrunc(Remainder);
			int32 Row = UKismetMathLibrary::FTrunc(ReturnValue);
	
			GridSlot->SetRow(Row);
			GridSlot->SetColumn(Column);
		}
	}
}



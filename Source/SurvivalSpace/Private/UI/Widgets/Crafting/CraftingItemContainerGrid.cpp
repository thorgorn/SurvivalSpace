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
	//int32 LocalLoopIndex = Amount;
	
	int32 FirstIndex = 1;

	for (int32 Index = FirstIndex; Index <= Amount; ++Index)
	{
		if (CraftingSlotClass)
		{
			CraftingSlot = CreateWidget<UCraftingSlot>(GetWorld(), CraftingSlotClass);
			
			if (CraftingSlot)
			{
				CraftingSlot->ContainerType = ContainerType;
				CraftingSlot->Parent = this;
				Slots.Add(CraftingSlot);
				CraftingSlot->ItemIndex = Slots.Num() - 1;
				AddSlotToGrid(CraftingSlot->ItemIndex, CraftingSlot);
			}
		}
	}
}

void UCraftingItemContainerGrid::AddSlotToGrid(int32 Index, UCraftingSlot* CraftingItemSlot)
{
	if (!Grid || !CraftingSlot)
	{
		return;
	}
	
	//int32 LocalSlotIndex = Index;
	//UCraftingSlot* LocalSlot = CraftingSlot;
	
	UUniformGridSlot* GridSlot = Grid->AddChildToUniformGrid(CraftingSlot);
	if (!GridSlot)
	{
		return;
	}
	
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



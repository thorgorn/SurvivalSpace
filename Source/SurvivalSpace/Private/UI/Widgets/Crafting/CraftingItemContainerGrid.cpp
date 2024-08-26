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
	int32 LocalLoopIndex = Amount;
	int32 FirstIndex = 1;

	for (int32 Index = FirstIndex; Index <= LocalLoopIndex; ++Index)
	{
		// Create a new Inventory Slot Widget
		if (CraftingSlotClass)
		{
			CraftingSlot = CreateWidget<UCraftingSlot>(GetWorld(), CraftingSlotClass);

			// Set the ContainerType of the new slot
			if (CraftingSlot)
			{
				CraftingSlot->ContainerType = ContainerType;
				CraftingSlot->Parent = this;
				Slots.Add(CraftingSlot);
				CraftingSlot->ItemIndex = Slots.Num() - 1; // Correcting the ItemIndex to zero-based index
				// Add the new slot to the grid
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

	// Define local variables as in the blueprint logic
	int32 LocalSlotIndex = Index;
	UCraftingSlot* LocalSlot = CraftingSlot;

	// Add the slot to the grid
	UUniformGridSlot* GridSlot = Grid->AddChildToUniformGrid(LocalSlot);
	if (!GridSlot)
	{
		return;
	}

	// Calculate row and column separately
	int32 SlotsPerRowValue = SlotsPerRow;

	// Calculate Row and Column
	double LocalSlotIndexAsDouble = UKismetMathLibrary::Conv_IntToDouble(LocalSlotIndex);
	double SlotsPerRowAsDouble = UKismetMathLibrary::Conv_IntToDouble(SlotsPerRowValue);

	double Remainder;
	int32 ReturnValue = UKismetMathLibrary::FMod(LocalSlotIndexAsDouble, SlotsPerRowAsDouble, Remainder);
	int32 Column = UKismetMathLibrary::FTrunc(Remainder);
	int32 Row = UKismetMathLibrary::FTrunc(ReturnValue);

	// Set row and column for the slot
	GridSlot->SetRow(Row);
	GridSlot->SetColumn(Column);
}



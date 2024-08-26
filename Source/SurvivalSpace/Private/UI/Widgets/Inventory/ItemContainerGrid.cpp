// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.


#include "UI/Widgets/Inventory/ItemContainerGrid.h"

#include "Components/ScrollBar.h"
#include "Components/ScrollBox.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/Widgets/Inventory/InventorySlot.h"

void UItemContainerGrid::NativeConstruct()
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

void UItemContainerGrid::AddSlots(const int32 Amount)
{
	
	int32 LocalLoopIndex = Amount;
	int32 FirstIndex = 1;

	for (int32 Index = FirstIndex; Index <= LocalLoopIndex; ++Index)
	{
		// Create a new Inventory Slot Widget
		if (InventorySlotClass)
		{
			InventorySlot = CreateWidget<UInventorySlot>(GetWorld(), InventorySlotClass);

			// Set the ContainerType of the new slot
			if (InventorySlot)
			{
				InventorySlot->ContainerType = ContainerType;
				InventorySlot->Parent = this;
				InventorySlot->bIsCraftingSlot = bIsCraftingSlot;
				Slots.Add(InventorySlot);
				InventorySlot->ItemIndex = Slots.Num() - 1; // Correcting the ItemIndex to zero-based index
				// Add the new slot to the grid
				AddSlotToGrid(InventorySlot->ItemIndex, InventorySlot);
			}
		}
	}
}

void UItemContainerGrid::AddSlotToGrid(int32 Index, UInventorySlot* ItemSlot)
{
	if (!Grid || !ItemSlot)
	{
		return;
	}

	// Define local variables as in the blueprint logic
	int32 LocalSlotIndex = Index;
	UInventorySlot* LocalSlot = ItemSlot;

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

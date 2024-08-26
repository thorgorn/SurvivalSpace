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

TArray<UInventorySlot*> UItemContainerGrid::GetSlots() const
{
	return Slots;
}

void UItemContainerGrid::AddSlots(const int32 Amount)
{
	if (!InventorySlotClass) return;

	for (int32 Index = 0; Index < Amount; ++Index)
	{
		InventorySlot = CreateWidget<UInventorySlot>(GetWorld(), InventorySlotClass);
		if (InventorySlot) 
		{
			InventorySlot->ContainerType = ContainerType;
			InventorySlot->Parent = this;
			InventorySlot->bIsCraftingSlot = bIsCraftingSlot;
			
			InventorySlot->ItemIndex = Slots.Emplace(InventorySlot);

			AddSlotToGrid(InventorySlot->ItemIndex, InventorySlot);
		}
	}
}


void UItemContainerGrid::AddSlotToGrid(int32 Index, UInventorySlot* ItemSlot)
{
		
	if (IsValid(ItemSlot))
	{
		if (TObjectPtr<UUniformGridSlot> GridSlot = Grid->AddChildToUniformGrid(ItemSlot); IsValid(GridSlot))
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

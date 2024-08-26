// Survival Space developed by TroubleInSpace, all rights reserved to Spaced Out Studios.


#include "UI/Widgets/Inventory/Operations/ItemDrag.h"

void UItemDrag::GetItemDragInfo(int32 &OutSlotIndex, EContainerType &OutFromContainer, EArmorType &OutArmorType, EItemType &OutItemType)
{
	OutSlotIndex = SlotIndex;
	OutFromContainer = FromContainer;
	OutArmorType = ArmorType;
	OutItemType = ItemType;
}

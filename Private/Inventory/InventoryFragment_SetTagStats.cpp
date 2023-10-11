// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryFragment_SetTagStats.h"
#include "Inventory/InventoryItemInstance.h"

void UInventoryFragment_SetTagStats::OnInstanceCreated(UInventoryItemInstance* Instance) const
{
	for (const auto& KVP : InitialItemStats)
	{
		Instance->AddStatTagStack(KVP.Key, KVP.Value);
	}
}

int32 UInventoryFragment_SetTagStats::GetItemStatByTag(FGameplayTag Tag) const
{
	if (const int32* StatPtr = InitialItemStats.Find(Tag))
	{
		return *StatPtr;
	}

	return 0;
}

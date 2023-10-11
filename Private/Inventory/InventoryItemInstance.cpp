// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryItemInstance.h"
#include "GameplayTagContainer.h"
#include "LassevaniaCommonTypes.h"
#include "Containers/Array.h"
#include "GameplayTagContainer.h"
#include "Inventory/InventoryItemDefinition.h"
#include "Misc/AssertionMacros.h"
#include "Net/UnrealNetwork.h"
#include "UObject/Class.h"





UInventoryItemInstance::UInventoryItemInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UInventoryItemInstance::AddStatTagStack(FGameplayTag Tag, int32 StackCount)
{
	StatTags.AddStack(Tag, StackCount);
}

void UInventoryItemInstance::RemoveStatTagStack(FGameplayTag Tag, int32 StackCount)
{
	StatTags.RemoveStack(Tag, StackCount);
}

int32 UInventoryItemInstance::GetStatTagStackCount(FGameplayTag Tag) const
{
	return StatTags.GetStackCount(Tag);
}


bool UInventoryItemInstance::HasStatTag(FGameplayTag Tag) const
{
	return StatTags.ContainsTag(Tag);
}

void UInventoryItemInstance::SetItemDef(TSubclassOf<UInventoryItemDefinition> InDef)
{
	ItemDef = InDef;
	if (InDef)
	{
		UInventoryItemDefinition* Definition = InDef->GetDefaultObject< UInventoryItemDefinition>();
		SetStackSize(Definition->StackSize);
		bIsStackable = StackSize > 1;
	}

}

const UInventoryItemFragment* UInventoryItemInstance::FindFragmentByClass(TSubclassOf<UInventoryItemFragment> FragmentClass) const
{
	if ((ItemDef != nullptr) && (FragmentClass != nullptr))
	{
		UE_LOG(LogTemp, Warning, TEXT("Getting fragment by class"));
		return GetDefault<UInventoryItemDefinition>(ItemDef)->FindFragmentByClass(FragmentClass);
	}

	return nullptr;
}

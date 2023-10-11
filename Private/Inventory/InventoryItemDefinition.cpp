// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryItemDefinition.h"
#include "UObject/Class.h"

/* Joku macro mik‰ tekee CPP nimen perusteella t‰nne ?? koska hInventoryItemDefinition headeriss‰ classi m‰‰ritelmn‰ eik‰ erillist‰ filua*/


#include UE_INLINE_GENERATED_CPP_BY_NAME(InventoryItemDefinition)

UInventoryItemDefinition::UInventoryItemDefinition(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
}


const UInventoryItemFragment* UInventoryItemDefinition::FindFragmentByClass(TSubclassOf<UInventoryItemFragment> FragmentClass) const
{
	if (FragmentClass != nullptr)
	{
		for (UInventoryItemFragment* Fragment : Fragments)
		{
			if (Fragment && Fragment->IsA(FragmentClass))
			{
				UE_LOG(LogTemp, Warning, TEXT("Fragment: %s"), *Fragment->GetName());
				return Fragment;
			}
		}
	}

	return nullptr;
}

const UInventoryItemFragment* UInventoryFunctionLibrary::FindItemDefinitionFragment(TSubclassOf<UInventoryItemDefinition> ItemDef, TSubclassOf<UInventoryItemFragment> FragmentClass)
{
	if ((ItemDef != nullptr) && (FragmentClass != nullptr))
	{
		return GetDefault<UInventoryItemDefinition>(ItemDef)->FindFragmentByClass(FragmentClass);
	}
	return nullptr;
}

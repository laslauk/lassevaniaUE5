// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GameplayAbility_FromEquipment.h"
#include "Inventory/InventoryItemInstance.h"

UInventoryItemInstance* UGameplayAbility_FromEquipment::GetAssociatedItem() const
{
	/* huom, SourceObjectissa pit‰‰ olla laitettu liittyv‰ item instance*/
	if (FGameplayAbilitySpec* Spec = UGameplayAbility::GetCurrentAbilitySpec())
	{
		return Cast<UInventoryItemInstance>(Spec->SourceObject.Get());
	}
	
	return nullptr;
}

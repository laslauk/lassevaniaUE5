// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/LassevaniaAbilitySystemGlobals.h"
#include "LassevaniaAbilityTypes.h"

FGameplayEffectContext* ULassevaniaAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FLassevaniaGameplayEffectContext();
}

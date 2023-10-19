// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "LassevaniaAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class LASSEVANIA_API ULassevaniaAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()

		virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;

public:
	
};

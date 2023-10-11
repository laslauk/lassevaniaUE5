// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/GameplayAbilityBase.h"
#include "GameplayAbility_HitStunKnockback.generated.h"

/**
 * 
 */
UCLASS()
class LASSEVANIA_API UGameplayAbility_HitStunKnockback : public UGameplayAbilityBase
{
	GENERATED_BODY()

public:

	virtual void OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	
};

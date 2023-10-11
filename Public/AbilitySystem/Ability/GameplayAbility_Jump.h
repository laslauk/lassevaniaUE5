// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/GameplayAbilityBase.h"
#include "GameplayAbility_Jump.generated.h"

/**
 * 
 */
UCLASS()
class LASSEVANIA_API UGameplayAbility_Jump : public UGameplayAbilityBase
{
	GENERATED_BODY()
	
public:


	/* ~UGameplayAbilityBase interface start*/
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	/* ~UGameplayAbilityBase interface end*/



	UFUNCTION(BlueprintCallable, Category = "Lyra|Ability")
		void CharacterJumpStart();

	UFUNCTION(BlueprintCallable, Category = "Lyra|Ability")
		void CharacterJumpStop();

};

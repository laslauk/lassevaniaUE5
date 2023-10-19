// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GameplayAbilityBase.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "LassevaniaAbilityTypes.h"
#include "AbilitySystem/LassevaniaAbilitySystemLibrary.h"

#include "CharacterZDBase.h"

UGameplayAbilityBase::UGameplayAbilityBase(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	ActivationPolicy = EAbilityActivationPolicy::OnInputTriggered;
}

void UGameplayAbilityBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UGameplayAbilityBase::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
//	OnAbilityEndedDeligate.Broadcast();
}

AController* UGameplayAbilityBase::GetControllerFromActorInfo() const
{
	return nullptr;
}

ACharacterZDBase* UGameplayAbilityBase::GetLVCharacterFromActorInfo()
{
	return (CurrentActorInfo ? Cast<ACharacterZDBase>(CurrentActorInfo->AvatarActor.Get()) : nullptr);
}


void UGameplayAbilityBase::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	if (bActivateAbilityOnGranted)
	{
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
}

void UGameplayAbilityBase::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	K2_OnAbilityRemoved();
	Super::OnRemoveAbility(ActorInfo, Spec);
}


void UGameplayAbilityBase::CauseDamage(AActor* TargetActor)
{

	if (!IsValid(DamageEffectClass))  return;

	FGameplayEffectSpecHandle DamageSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass, 1.0f);

	for (TTuple<FGameplayTag, FScalableFloat> Pair : DamageTypes)
	{
		float ScaledDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageSpecHandle, Pair.Key, ScaledDamage);

		/* Set Properties of Gameplay Effect - Damage , handled in ExecCalc Damage cpp*/
		FGameplayEffectContextHandle EffectContext = DamageSpecHandle.Data->GetContext();

		ULassevaniaAbilitySystemLibrary::SetIsParryableAbility(
			EffectContext, bIsParryable
		);

		ULassevaniaAbilitySystemLibrary::SetDamageCasuesHitStun(
			EffectContext, bDamageCausesHitStun
		);


		/* Apply to target */
		GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*DamageSpecHandle.Data.Get(),
			UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor)
		);
	}

}
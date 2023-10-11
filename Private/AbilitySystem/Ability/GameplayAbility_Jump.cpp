// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/GameplayAbility_Jump.h"
#include "CharacterZDBase.h"


bool UGameplayAbility_Jump::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!ActorInfo || !ActorInfo->AvatarActor.IsValid())
	{
		return false;
	}


	const ACharacterZDBase* CharacterRef = Cast<ACharacterZDBase>(ActorInfo->AvatarActor.Get());
	if (!CharacterRef || !CharacterRef->CanJump())
	{
		return false;
	}


	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	return true;


}

void UGameplayAbility_Jump::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{

	// Stop jumping in case the ability blueprint doesn't call it.
	CharacterJumpStop();

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}

void UGameplayAbility_Jump::CharacterJumpStart()
{
	if (ACharacterZDBase* CharacterZD = GetLVCharacterFromActorInfo())
	{
		if (CharacterZD->IsLocallyControlled() && !CharacterZD->bPressedJump)
		{
			CharacterZD->UnCrouch();
			CharacterZD->Jump();
		}
	}

}

void UGameplayAbility_Jump::CharacterJumpStop()
{
	if (ACharacterZDBase* CharacterZD = GetLVCharacterFromActorInfo())
	{
		if (CharacterZD->IsLocallyControlled() && CharacterZD->bPressedJump)
		{
			CharacterZD->StopJumping();
		}
	}

}

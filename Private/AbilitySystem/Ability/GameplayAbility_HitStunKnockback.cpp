// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/GameplayAbility_HitStunKnockback.h"
#include "Character/PlayerCharacterBase.h"


void UGameplayAbility_HitStunKnockback::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	UE_LOG(LogTemp, Warning, TEXT("UGameplayAbility_HitStunKnockback::OnRemoveAbilit"));

	if (AActor* Actor = ActorInfo->AvatarActor.Get())
	{
		Cast<APlayerCharacterBase>(Actor)->SetCanMove(true);
		UE_LOG(LogTemp, Warning, TEXT("setting can move true"));
	}
	else
	{

		UE_LOG(LogTemp, Warning, TEXT("NO AAVATR for knockback"));
	}
	Super::OnRemoveAbility(ActorInfo, Spec);

}

// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/LassevaniaAbilitySet.h"
#include "AbilitySystem/GameplayAbilityBase.h"
#include "AbilitySystem/LVAbilitySystemComponent.h"

void FLassevaniaAbilitySet_GrantedHandles::AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle)
{
	if (Handle.IsValid())
	{
		AbilitySpecHandles.Add(Handle);
	}

}

void FLassevaniaAbilitySet_GrantedHandles::AddGameplayEffectHandle(const FActiveGameplayEffectHandle& Handle)
{
	if (Handle.IsValid())
	{

		GameplayEffectHandles.Add(Handle);
	}
}

void FLassevaniaAbilitySet_GrantedHandles::AddAttributeSet(UAttributeSet* Set)
{
	GrantedAttributeSets.Add(Set);

}

void FLassevaniaAbilitySet_GrantedHandles::TakeFromAbilitySystem(ULVAbilitySystemComponent* LVASC)
{
	for (const FGameplayAbilitySpecHandle& Handle : AbilitySpecHandles)
	{
		if (Handle.IsValid())
		{
			LVASC->ClearAbility(Handle);
		}
	}

	for (const FActiveGameplayEffectHandle& Handle : GameplayEffectHandles)
	{
		if (Handle.IsValid())
		{
			LVASC->RemoveActiveGameplayEffect(Handle);
		}
	}
	for (UAttributeSet* Set : GrantedAttributeSets)
	{
		LVASC->RemoveSpawnedAttribute(Set);
	}


	AbilitySpecHandles.Reset();
	GameplayEffectHandles.Reset();
	GrantedAttributeSets.Reset();

}

ULassevaniaAbilitySet::ULassevaniaAbilitySet(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
}


// Grants the ability set to the specified ability system component.
// The returned handles can be used later to take away anything that was granted.
void ULassevaniaAbilitySet::GiveToAbilitySystem(ULVAbilitySystemComponent* LVASC, FLassevaniaAbilitySet_GrantedHandles* OutGrantedHandles, UObject* SourceObject) const
{

	if (!LVASC) { return; }

	// Grant the gameplay abilities.
	for (int32 AbilityIndex = 0; AbilityIndex < GrantedGameplayAbilities.Num(); ++AbilityIndex)
	{
		const FLassevaniaAbilitySet_GameplayAbility& AbilityToGrant = GrantedGameplayAbilities[AbilityIndex];

		if (!IsValid(AbilityToGrant.Ability))
		{
			UE_LOG(LogTemp, Error, TEXT("GrantedGameplayAbilities[%d] on ability set [%s] is not valid."), AbilityIndex, *GetNameSafe(this));
			continue;
		}

		UGameplayAbilityBase* AbilityCD0 = AbilityToGrant.Ability->GetDefaultObject<UGameplayAbilityBase>();
		FGameplayAbilitySpec AbilitySpec(AbilityCD0, AbilityToGrant.AbilityLevel);


		AbilitySpec.SourceObject = SourceObject;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilityToGrant.InputTag);

		const FGameplayAbilitySpecHandle AbilitySpecHandle = LVASC->GiveAbility(AbilitySpec);

		/* TODO BINDING SIELLÄ AbilitySystemCompont*/
		//AbilityCD0->OnGameplayAbilityEnded.AddUObject(LVASC, &ULVAbilitySystemComponent::OnAbilityEnded);


		//AbilityCD0->OnGameplayAbilityEnded


		if (OutGrantedHandles)
		{
			OutGrantedHandles->AddAbilitySpecHandle(AbilitySpecHandle);
		}

	}

	// Grant the gameplay effects.
	for (int32 EffectIndex = 0; EffectIndex < GrantedGameplayEffects.Num(); ++EffectIndex)
	{
		/* TODO !!!*/
	}
	for (int32 SetIndex = 0; SetIndex < GrantedAttributes.Num(); ++SetIndex)
	{
		/* TODO !!*/
	}

}

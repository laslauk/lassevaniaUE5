// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterZDBase.h"
#include "AttributeSetBase.h"
#include "Inventory/InventoryComponent.h"
#include "PlayerStateBase.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "DataAssets/CharacterDataAsset.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/LVAbilitySystemComponent.h"
#include "AbilitySystem/LassevaniaAbilitySet.h"
#include "Interfaces/InteractInterface.h"


ACharacterZDBase::ACharacterZDBase() {


}

void ACharacterZDBase::GiveAbilities()
{
	TArray<TObjectPtr<ULassevaniaAbilitySet>> AbilitySets = CharacterDataAsset->AbilitySets;

	for (const ULassevaniaAbilitySet* AbilitySet : AbilitySets)
	{
		if (AbilitySet)
		{
			UE_LOG(LogTemp, Warning, TEXT("Granted Ability"));
			AbilitySet->GiveToAbilitySystem(Cast<ULVAbilitySystemComponent>(GetAbilitySystemComponent()), nullptr);
		}
	}

}

void ACharacterZDBase::PossessedBy(AController* NewController)
{

	Super::PossessedBy(NewController);

	UE_LOG(LogTemp, Warning, TEXT("Character: %s - possessed by Controller: %s"), *GetName(), *(NewController->GetName()));

}

UAbilitySystemComponent* ACharacterZDBase::GetAbilitySystemComponent() const
{
	
	UE_LOG(LogTemp, Warning, TEXT("HEI EI TÄTÄ TÄTÄ EI PITÄISI KUTSUA Calling NULL CharacterZD GetAbilitySystemComponent()"));
	return nullptr;
}





void ACharacterZDBase::AquireAbility(TSubclassOf<UGameplayAbilityBase> AbilityToAquire)
{
	if (GetAbilitySystemComponent())
	{
		//run at server
		if (AbilityToAquire)
		{
			//GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(AbilityToAquire, 1, 0));
		}
		GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);
	}
}

UInventoryComponent* ACharacterZDBase::GetInventoryComponent()
{
	return Cast<APlayerStateBase>(GetPlayerState())->GetInventoryComponent();
}

UAttributeSetBase* ACharacterZDBase::GetAttributeSetComponent()
{
	return  Cast<APlayerStateBase>(GetPlayerState())->GetAttributeSetComponent();;
}

void ACharacterZDBase::TryMovement(float ScaleValue)
{
	if (bCanMove)
	{
		AddMovementInput(FVector(1.0f, 0.f, 0.f), ScaleValue, false);

		if (ScaleValue > 0 )
		{
			FRotator Rotator(0.f, 0.f, 0.f);
			GetController()->SetControlRotation(Rotator);
		}
		else if (ScaleValue < 0)
		{
			FRotator Rotator(0.f, 180.f, 0.f);
			GetController()->SetControlRotation(Rotator);
		}
	}
}

const UCharacterDataAsset* ACharacterZDBase::GetCharacterData() const
{
	return CharacterDataAsset;
}

void ACharacterZDBase::SetCharacterData(const UCharacterDataAsset* InCharacterDataAsset)
{
	CharacterDataAsset = InCharacterDataAsset;
}


bool ACharacterZDBase::ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> gameplayEffect, FGameplayEffectContextHandle IneffectContext)
{

	if (!gameplayEffect.Get()) return false;

	FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(gameplayEffect, 1, IneffectContext);
	if (SpecHandle.IsValid())
	{

		FActiveGameplayEffectHandle ActiveGEHandle = GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		return ActiveGEHandle.WasSuccessfullyApplied();

	}

	return false;
}



void ACharacterZDBase::ApplyStartupEffects()
{

		UE_LOG(LogTemp, Warning, TEXT("Calling ACharacterZDBase::ApplyStartupEffects()"));
		if (GetAbilitySystemComponent() == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("GetAbilitySystemComponent() nullptr"));

			return;
		}

		FGameplayEffectContextHandle EffectContext = GetAbilitySystemComponent()->MakeEffectContext();

		EffectContext.AddSourceObject(this);

		/*
		for (auto CharEffect : CharacterData.EffectsDefault)
		{
			ApplyGameplayEffectToSelf(CharEffect, EffectContext);
		}




		*/

	
}

void ACharacterZDBase::Die()
{
}

void ACharacterZDBase::InitializeDefaultAttributes()
{

	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.0f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.0f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.0f);

}


void ACharacterZDBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> Effect, float level)
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();

	check(IsValid(GetAbilitySystemComponent()));
	check(Effect);

	FGameplayEffectContextHandle Handle = ASC->MakeEffectContext();
	Handle.AddSourceObject(this);

	FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(Effect, level, Handle);
	ASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());

}


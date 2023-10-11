// Fill out your copyright notice in the Description page of Project Settings.


#include "Character3DBase.h"

// Sets default values
ACharacter3DBase::ACharacter3DBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComp");

}



UAbilitySystemComponent* ACharacter3DBase::GetAbilitySystemComponent() const {
	return AbilitySystemComp;
}


void ACharacter3DBase::AquireAbility(TSubclassOf<UGameplayAbility> AbilityToAquire) {

	if (AbilitySystemComp) {
		//run at server
		if (AbilityToAquire) {
			AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(AbilityToAquire, 1, 0));
		}
		AbilitySystemComp->InitAbilityActorInfo(this, this);
	}

}
// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyCharacterBase.h"

#include "Components/WidgetComponent.h"
#include "UI/UserWidgetBase.h"
#include "AttributeSetBase.h"
#include "AbilitySystem/LVAbilitySystemComponent.h"


AEnemyCharacterBase::AEnemyCharacterBase()
{

	AbilitySystemComponent = CreateDefaultSubobject<ULVAbilitySystemComponent>(TEXT("Ability System Component"));
	AttributeSetBaseComp = CreateDefaultSubobject<UAttributeSetBase>(TEXT("AttributeSetBaseComponent"));
	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());

}

void AEnemyCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	ApplyStartupEffects();
		
}

UAbilitySystemComponent* AEnemyCharacterBase::GetAbilitySystemComponent() const
{
	return GetLVAbilitySystemComponent();
}

UAttributeSetBase* AEnemyCharacterBase::GetAttributeSetComponent()
{
	return AttributeSetBaseComp;
}

int32 AEnemyCharacterBase::GetAvatarLevel() {
	return Level;
}

void AEnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();

	if (UUserWidgetBase* UserWidgetBase = Cast<UUserWidgetBase>(HealthBar->GetUserWidgetObject()))
	{
		UserWidgetBase->SetWidgetController(this);

	}

	
	if (AbilitySystemComponent)
	{
		UAttributeSetBase* AS = CastChecked<UAttributeSetBase>(AttributeSetBaseComp);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);

		OnHealthChanged.Broadcast(AS->GetHealth());
		OnMaxHealthChanged.Broadcast(AS->GetMaxHealth());
	}



}

void AEnemyCharacterBase::InitAbilityActorInfo()
{
	InitializeDefaultAttributes();

}




/*
void AEnemyCharacterBase::ApplyStartupEffects()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling CHARACYTER ZD BASE GetAbilitySysteMComp()"));
	if (GetAbilitySystemComponent() == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("homo"));

		return;
	}
	FGameplayEffectContextHandle EffectContext = GetAbilitySystemComponent()->MakeEffectContext();


	EffectContext.AddSourceObject(this);

	for (auto CharEffect : CharacterData.EffectsDefault)
	{
		ApplyGameplayEffectToSelf(CharEffect, EffectContext);
	}

}

*/
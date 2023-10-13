// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyCharacterBase.h"

#include "Components/WidgetComponent.h"
#include "UI/UserWidgetBase.h"
#include "AttributeSetBase.h"
#include "AbilitySystem/LassevaniaAbilitySystemLibrary.h"
#include "AbilitySystem/LVAbilitySystemComponent.h"
#include "LassevaniaGameplayTags.h"



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

void AEnemyCharacterBase::Die()
{
	Super::Die();
	Destroy();
}

void AEnemyCharacterBase::InitializeDefaultAttributes()
{
	if (!AbilitySystemComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT(" ------ AbilitySystemComponent : null ASC"));
		return;
	}
	ULassevaniaAbilitySystemLibrary::InitializeDefaultAttributes
	(
		this, /*world contextr obj*/
		CharacterClass, /*class enum type of this char */
		Level, /*character level*/
		AbilitySystemComponent /*ASC ptr of this char*/
	);

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




		for (const TSubclassOf<UGameplayAbility> AbilityClass : CommonAbilities)
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		
			if (const UGameplayAbilityBase* GameplayAbiltiyBase = Cast<UGameplayAbilityBase>(AbilitySpec.Ability))
			{
				FGameplayAbilitySpecHandle AbilitySpecHandle = GetAbilitySystemComponent()->GiveAbility(AbilitySpec);


				if (AbilitySpecHandle.IsValid())
				{

					UE_LOG(LogTemp, Warning, TEXT("Granted ability "));

				}
			}
		}


	}

	/* Listen for tag add / removal */
	BindToGameplayTags();
	InitializeDefaultAttributes();


}

void AEnemyCharacterBase::BindToGameplayTags()
{
	if (AbilitySystemComponent)
	{

		AbilitySystemComponent->RegisterGameplayTagEvent(FLassevaniaGameplayTags::Get().Effects_HitReact,
			EGameplayTagEventType::AnyCountChange).AddUObject(this, &AEnemyCharacterBase::HitReactTagChanged);

	}

}	

void AEnemyCharacterBase::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewTagCount)
{
	UE_LOG(LogTemp, Warning, TEXT("ASDDASDASDADSASDADS"));
	 bHitReacting = NewTagCount > 0;
	
	 /*
	 if (IsValid(HitReactEffectClass))
	 {
		 FGameplayEffectContextHandle ContextHandle;
		 FGameplayEffectSpecHandle GE_Handle = AbilitySystemComponent->MakeOutgoingSpec(HitReactEffectClass, 1, ContextHandle);
		 AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*GE_Handle.Data.Get());

	 }
	*/


	K2_OnHitReact();

}

void AEnemyCharacterBase::InitAbilityActorInfo()
{
	
	AbilitySystemComponent->InitAbilityActorInfo(this, this);


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
// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyCharacterBase.h"

#include "Components/WidgetComponent.h"
#include "UI/UserWidgetBase.h"
#include "AttributeSetBase.h"
#include "AbilitySystem/LassevaniaAbilitySystemLibrary.h"
#include "AbilitySystem/GameplayAbilityBase.h"
#include "AI/LassevaniaAIController.h"
#include "AbilitySystem/LVAbilitySystemComponent.h"
#include "AbilitySystem/LassevaniaAbilitySet.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "PaperZD/Public/PaperZDAnimationComponent.h"
#include "LassevaniaGameplayTags.h"



AEnemyCharacterBase::AEnemyCharacterBase()
{

	AbilitySystemComponent = CreateDefaultSubobject<ULVAbilitySystemComponent>(TEXT("Ability System Component"));
	AttributeSetBaseComp = CreateDefaultSubobject<UAttributeSetBase>(TEXT("AttributeSetBaseComponent"));
	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());

	//GetAnimationComponent()->Rename(TEXT("ass"));

	

}

void AEnemyCharacterBase::SetupAI(AController* NewController)
{
	if (!NewController) return;
	if (BehaviorTree.IsNull()) return;

	LassevaniaAIController = Cast<ALassevaniaAIController>(NewController);

	if (!HasAuthority()) return; //AI only controlled on server, client see replicated

	LassevaniaAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	LassevaniaAIController->RunBehaviorTree(BehaviorTree);
	LassevaniaAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), false);
}

void AEnemyCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	SetupAI(NewController);

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



	K2_OnDeath();
	//Destroy(); handled in BP now atm
	
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



void AEnemyCharacterBase::SetupMovementFor2DCharacter()
{

	UCharacterMovementComponent* CharMoveComp = Cast<UCharacterMovementComponent>(GetMovementComponent());
	bUseControllerRotationYaw = true;
	CharMoveComp->bOrientRotationToMovement = false;
}

void AEnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
	SetupMovementFor2DCharacter();
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
	GiveAbilities();
	/* Listen for tag add / removal */
	BindToGameplayTags();
	InitializeDefaultAttributes();


}


void AEnemyCharacterBase::GiveAbilities()
{
		if (EnemyCharacterAbilitySet)
		{
			EnemyCharacterAbilitySet->GiveToAbilitySystem(Cast<ULVAbilitySystemComponent>(GetAbilitySystemComponent()), nullptr);
		}

	/*
	for (const TSubclassOf<UGameplayAbility> AbilityClass : EnemyCharacterAbilitySet)
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

	*/
}

void AEnemyCharacterBase::BindToGameplayTags()
{
	if (AbilitySystemComponent)
	{

		AbilitySystemComponent->RegisterGameplayTagEvent(FLassevaniaGameplayTags::Get().Effects_HitStunned,
			EGameplayTagEventType::AnyCountChange).AddUObject(this, &AEnemyCharacterBase::HitStunTagChanged);

	}

}	

void AEnemyCharacterBase::HitStunTagChanged(const FGameplayTag CallbackTag, int32 NewTagCount)
{
	/* Set AI blackboard values to follow if HitStunned or not. Tag added through GA_HitStunned Tag adding */
	 bHitStunned = NewTagCount > 0;
	 LassevaniaAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), bHitStunned);
	

	 /*
	 if (IsValid(HitReactEffectClass))
	 {
		 FGameplayEffectContextHandle ContextHandle;
		 FGameplayEffectSpecHandle GE_Handle = AbilitySystemComponent->MakeOutgoingSpec(HitReactEffectClass, 1, ContextHandle);
		 AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*GE_Handle.Data.Get());

	 }
	*/


	K2_OnHitStunned();

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
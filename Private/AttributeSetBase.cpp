// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeSetBase.h"
#include "GameplayEffectExtension.h"
#include "CharacterZDBase.h"
#include "PlayerStateBase.h"
#include "Interfaces/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffect.h"
#include "LassevaniaGameplayTags.h"
#include "PlayerControllerBase.h"



UAttributeSetBase::UAttributeSetBase():Health(100.0f) 
{
	const FLassevaniaGameplayTags& GameplayTags = FLassevaniaGameplayTags::Get();


	/* IF took delegates, but now use function ptr
	FAttributeSignature DexterityDelegate;
	DexterityDelegate.BindStatic(GetDexterityAttribute); /* bind to delegate*/
	//TagsToAttributesMap.Add(GameplayTags.Attributes_Primary_Dexterity, DexterityDelegate);




	TagsToAttributesMap.Add(GameplayTags.Attributes_Primary_Strength, GetStrengthAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Primary_Dexterity, GetDexterityAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Primary_Spirit, GetSpiritAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Primary_Vigor, GetVigorAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Primary_Intelligence, GetIntelligenceAttribute);


	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_ArmorPenetration, GetArmorPenetrationAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_Armor, GetArmorAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_CriticalHitChance, GetCriticalHitAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_DodgeChance, GetDodgeChanceAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_MagicResistance, GetMagicResistanceAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_MaxHealth, GetMaxHealthAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_MaxMana, GetMaxManaAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_MaxStamina, GetMaxStaminaAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_BlockChance, GetBlockChanceAttribute);

	InitMovementSpeed(100.f);
	InitMaxMovementSpeed(100.f);
}



void UAttributeSetBase::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) {

	Super::PostGameplayEffectExecute(Data);
	
	FEffectProperties EffectProperties;
	SetEffectProperties(Data, EffectProperties);
	


	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{

		// Handle health  changes. -- Handle it with meta attribute when taking damage
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));

	}


	/* META ATTRIBUTES */
	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float IncomingDamageVal = GetIncomingDamage();
		SetIncomingDamage(0.f);

		if (IncomingDamageVal > 0.f)
		{
			const float NewHealth = GetHealth() - IncomingDamageVal;

			SetHealth(FMath::Clamp (0.0f, NewHealth, GetMaxHealth()));
		

			const bool FatalDamage = NewHealth <= 0.f;


			if (FatalDamage)
			{
				ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetOwningActor());
				if (CombatInterface)
				{

					CombatInterface->Die();


				}
				
			}

			if (!FatalDamage)
			{
				FGameplayTagContainer TagContainer;
		
				TagContainer.AddTag(FLassevaniaGameplayTags::Get().Effects_HitReact);

				if (ACharacterZDBase* CharacterZDBase = Cast< ACharacterZDBase>(GetOwningActor()))
				{
					if (UAbilitySystemComponent* ASC = CharacterZDBase->GetAbilitySystemComponent())
					{
				
					
						ASC->TryActivateAbilitiesByTag(TagContainer);

						APlayerControllerBase* PlayerController =	Cast<APlayerControllerBase>
							(UGameplayStatics::GetPlayerController(CharacterZDBase, 0));

						if (PlayerController)
						{
;
							PlayerController->ShowDamageNumber(IncomingDamageVal, CharacterZDBase);
						}
				
					}
				} 
				
				else if (APlayerStateBase* PlayerStateBase = Cast< APlayerStateBase>(GetOwningActor()))
				{
					if (UAbilitySystemComponent* ASC = PlayerStateBase->GetAbilitySystemComponent())
					{
					
						ASC->TryActivateAbilitiesByTag(TagContainer);

					}
				}
			}
	

		}
	}





}

void UAttributeSetBase::SetEffectProperties(const  FGameplayEffectModCallbackData& Data, FEffectProperties& EffectProperties)
{

	/* SOURCE DATA */
	EffectProperties.EffectContextHandle = Data.EffectSpec.GetContext();
	EffectProperties.SourceASC = EffectProperties.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(EffectProperties.SourceASC))
	{
		UAbilitySystemComponent* SourceASC = EffectProperties.SourceASC;
		EffectProperties.SourceAvatarActor = SourceASC->GetAvatarActor();
		EffectProperties.SourceController = SourceASC->AbilityActorInfo->PlayerController.Get();


		/* ei saatu ability actor infosta controller, haetaan avatarista */
		if (EffectProperties.SourceController == nullptr && EffectProperties.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(EffectProperties.SourceAvatarActor))
			{
				EffectProperties.SourceController = Pawn->GetController();
			}
		}

		if (EffectProperties.SourceController)
		{
			EffectProperties.SourceCharacter = Cast<ACharacter>(EffectProperties.SourceController->GetPawn());
		}
	}

	/* TARGET DATA */

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		EffectProperties.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		EffectProperties.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		EffectProperties.TargetCharacter = Cast<ACharacter>(EffectProperties.TargetAvatarActor);
		EffectProperties.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(EffectProperties.TargetAvatarActor);
		
	}

}

void UAttributeSetBase::ShowFloatingText(const FEffectProperties& Props, float Damage)
{
}


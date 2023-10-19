// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeSetBase.h"
#include "GameplayEffectExtension.h"
#include "CharacterZDBase.h"
#include "PlayerStateBase.h"
#include "Interfaces/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystem/LassevaniaAbilitySystemLibrary.h"
#include "LassevaniaGameplayTags.h"
#include "LassevaniaAbilityTypes.h"
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


	TagsToAttributesMap.Add(GameplayTags.Attributes_Resistance_Physical, GetPhysicalResistanceAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Resistance_Fire, GetFireResistanceAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Resistance_Frost, GetFrostResistanceAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Resistance_Shadow, GetShadowResistanceAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Resistance_Nature, GetNatureResistanceAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Resistance_Divine, GetDivineResistanceAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Resistance_Arcane, GetArcaneResistanceAttribute);
	


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

		/* dont do anything if damage is 0 - Incoming Damage attribute changed in ExecCalc_Damage.cpp*/
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
				
				bool OwnerIsPlayer = GetOwningActor()->ActorHasTag(FName("Player"));

				UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningActor());

				if (ASC)
				{
					const bool DamageHitStuns = ULassevaniaAbilitySystemLibrary::IsDamageCausesHitStun(EffectProperties.EffectContextHandle);

					if (DamageHitStuns)
					{

						FGameplayTagContainer TagContainer;
						/* hahmoilla GA_HitReact ability joka aktivboidaan tällä*/
						TagContainer.AddTag(FLassevaniaGameplayTags::Get().Effects_HitReact);
						ASC->TryActivateAbilitiesByTag(TagContainer);
					
						/* TODO - Parempi tapa sendata hitreact GA:lle kuka instigator jotta helpommin voi antaa veloicty pushback suunta*/
						FGameplayEventData EventData;
						EventData.Instigator = EffectProperties.SourceAvatarActor;
						UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(EffectProperties.TargetAvatarActor, 
							FLassevaniaGameplayTags::Get().Damage_GameplayEvent_HitReact, EventData);
					}

					const bool bIsCrit = ULassevaniaAbilitySystemLibrary::IsCriticalHit(EffectProperties.EffectContextHandle);
					const bool bIsBlocked = ULassevaniaAbilitySystemLibrary::IsBlockedHit(EffectProperties.EffectContextHandle);


					if (!OwnerIsPlayer)
					{
						ShowFloatingText(EffectProperties, IncomingDamageVal, bIsBlocked, bIsCrit);
					}
					//	const bool bBlocked = ULassevaniaAbilitySystemLibrary::IsBlockedHit(EffectProperties.EffectContextHandle);
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

void UAttributeSetBase::ShowFloatingText(const FEffectProperties& Props, float Damage, bool bBlockingHit, bool bCriticalHit)
{

	if (Props.SourceCharacter == Props.TargetCharacter) return;

	APlayerControllerBase* PlayerController = Cast<APlayerControllerBase>
		(UGameplayStatics::GetPlayerController(Props.SourceCharacter, 0));

	if (PlayerController)
	{
		PlayerController->ShowDamageNumber(Damage, Props.TargetCharacter, bBlockingHit, bCriticalHit);
	}
}


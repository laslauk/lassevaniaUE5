// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeSetBase.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"
#include "LassevaniaGameplayTags.h"



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
	TagsToAttributesMap.Add(GameplayTags.Attributes_Primary_Intelligence, GetIntelligenceAttribute);


	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_ArmorPenetration, GetArmorPenetrationAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_Armor, GetArmorAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_CriticalHitChance, GetCriticalHitAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_DodgeChance, GetDodgeChanceAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_MagicResistance, GetMagicResistanceAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_MaxHealth, GetMaxHealthAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_MaxMana, GetMaxManaAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_MaxStamina, GetMaxStaminaAttribute);


	InitMovementSpeed(100.f);
	InitMaxMovementSpeed(100.f);
}



void UAttributeSetBase::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) {

	Super::PostGameplayEffectExecute(Data);
	

	


	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{

		// Handle health  changes. -- Handle it with meta attribute when taking damage
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));

	}


	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float IncomingDamageVal = GetIncomingDamage();
		SetIncomingDamage(0.f);

		if (IncomingDamageVal > 0.f)
		{
			const float NewHealth = GetHealth() - IncomingDamageVal;

			SetHealth(FMath::Clamp (0.0f, NewHealth, GetMaxHealth()));
		

			const bool FatalDamage = NewHealth <= 0.f;
	

		}
	}





}


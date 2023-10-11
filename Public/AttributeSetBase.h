// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AttributeSetBase.generated.h"

//typedef  TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultDelegateUserPolicy>::FFuncPtr FAttributeFuncPtr;
template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;


/**
 * 
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


// DECLARE_DELEGATE_RetVal(FGameplayAttribute, FAttributeSignature);

class UAbilitySystemComponent;

UCLASS()
class LASSEVANIA_API UAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()

	UAttributeSetBase();

public:


	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data);

	TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultDelegateUserPolicy>::FFuncPtr FunctionPointer;

	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributesMap;



	/* Initial Design:

	Primary:
	Strength: Increase PHYSICAL damage
	Int: Increase mana, Device damage,  reduces magical damage taken
	Dexterity: Damage on RANGED, Dodge chance(?) roll pentalty on stamna, increase crit %
	Spirit: increase magical damage, reduces magical damage taken
	Vigor: Maximum health
	
	Secondary - Derived attributes:

	Armor: reducces PHYSICAL damage taken
	Armor Penetration: ignores % of enemy armor,
	
	Magical Resistance: reduces magical damage

	Critical Hit Chance: Chance to double damage
	
	- no mana / health reg on default -

	Max Health: Maximum amount of health obtainable
	Max Mana: Maximum amount of obtainable mana
	
	
	
	
	*/


	/* Inited with gameplay effects*/
	/* RPG Primary Attributes (stats) */


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase | Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, Strength)


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase | Primary Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, Intelligence)


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase | Primary Attributes")
	FGameplayAttributeData Dexterity;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, Dexterity)


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase | Primary Attributes")
	FGameplayAttributeData Spirit;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, Spirit)


		/* ~RPG Primary Attributes (stats) */


	/* -------------- Vital Attributes --------------*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase | Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, Health)




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase | Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, Mana)





	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase | Vital Attributes")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, Stamina)



	/* ~Vital Attributes */



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase | Vital Attributes")
	FGameplayAttributeData MovementSpeed;
ATTRIBUTE_ACCESSORS(UAttributeSetBase, MovementSpeed)





	/* --------------- SECONDARY ATTRIBUTES --------------- */


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase | Secondary Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, Armor)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase | Secondary Attributes")
	FGameplayAttributeData MagicResistance;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, MagicResistance)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase | Secondary Attributes")
	FGameplayAttributeData DodgeChance;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, DodgeChance)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase | Secondary Attributes")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, ArmorPenetration)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase | Secondary Attributes")
	FGameplayAttributeData CriticalHit;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, CriticalHit)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase | Secondary Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, MaxMana)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase | Secondary Attributes")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, MaxStamina)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase | Secondary Attributes")
	FGameplayAttributeData MaxMovementSpeed;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, MaxMovementSpeed)


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase | Secondary Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, MaxHealth)


	/* ~SECONDARY ATTRIBUTES END */




	/* 
	
	
		MEta attributyes
	
	*/


	UPROPERTY(BlueprintReadOnly, Category ="Meta Attributes") //metas not replicated
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, IncomingDamage)

protected:



};

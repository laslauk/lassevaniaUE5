// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 *  Singleton, containing native  (created from and available at c++) gameplay tags
 */
struct FLassevaniaGameplayTags
{
public:

	static const FLassevaniaGameplayTags& Get() { return GameplayTags; }


	static void InitializeNativeGameplayTags();
	static void SetLassevaniaGameplayTagReferences();

	int32 Testi = 0;

	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Dexterity;
	FGameplayTag Attributes_Primary_Spirit;
	FGameplayTag Attributes_Primary_Vigor;

	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_MagicResistance;
	FGameplayTag Attributes_Secondary_DodgeChance;
	FGameplayTag Attributes_Secondary_ArmorPenetration;

	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxStamina;
	FGameplayTag Attributes_Secondary_MaxMana;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Resistance_Physical;

	FGameplayTag Attributes_Resistance_Fire;
	FGameplayTag Attributes_Resistance_Shadow;
	FGameplayTag Attributes_Resistance_Frost;
	FGameplayTag Attributes_Resistance_Nature;
	FGameplayTag Attributes_Resistance_Divine;
	FGameplayTag Attributes_Resistance_Arcane;

	/* Attack tags*/

	

	FGameplayTag Abilities_Attack;
	FGameplayTag Abilities_Deflect;

	FGameplayTag Abilities_Event_Parried;
	

	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistancesMap;

	FGameplayTag Effects_HitReact;
	FGameplayTag Effects_HitStunned;

	/*damage types*/


	FGameplayTag Damage; 
	FGameplayTag Damage_GameplayEvent_HitReact;


	FGameplayTag Damage_Fire;
	FGameplayTag Damage_Shadow;
	FGameplayTag Damage_Frost;
	FGameplayTag Damage_Nature;
	FGameplayTag Damage_Divine;
	FGameplayTag Damage_Arcane;

	FGameplayTag Damage_Physical;


protected:


private:
	static FLassevaniaGameplayTags GameplayTags;



};
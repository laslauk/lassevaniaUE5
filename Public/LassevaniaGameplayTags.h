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

	static void SetKakka() { GameplayTags.Testi = 50123030; }

	static void InitializeNativeGameplayTags();
	static void SetLassevaniaGameplayTagReferences();

	int32 Testi = 0;

	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Dexterity;
	FGameplayTag Attributes_Primary_Spirit;

	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_MagicResistance;
	FGameplayTag Attributes_Secondary_DodgeChance;
	FGameplayTag Attributes_Secondary_ArmorPenetration;

	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxStamina;
	FGameplayTag Attributes_Secondary_MaxMana;

protected:


private:
	static FLassevaniaGameplayTags GameplayTags;



};
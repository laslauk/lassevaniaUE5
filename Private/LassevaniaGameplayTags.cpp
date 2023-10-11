// Fill out your copyright notice in the Description page of Project Settings.


#include "LassevaniaGameplayTags.h"
#include "GameplayTagsManager.h"

FLassevaniaGameplayTags FLassevaniaGameplayTags::GameplayTags;

void FLassevaniaGameplayTags::InitializeNativeGameplayTags()
{

	 /* Primary */
	GameplayTags.Testi = 666;

	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Strength"),
		FString("Increases physical damage. Increases health.")

	);

	GameplayTags.Attributes_Primary_Dexterity= UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Dexterity"),
		FString("Increaes critical chance. Increases health. Reduces roll penalty.")
	);

	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Intelligence"),
		FString("Increases magical damage. Device damage.")
	);

	GameplayTags.Attributes_Primary_Spirit= UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Spirit"),
		FString("Increases spiritual stuff.")
	);


	/* Secondary */

	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Armor"),
		FString("Reduces physical damage taken.")
	);

	GameplayTags.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitChance"),
		FString("Double damage on hitr.")
	);

	GameplayTags.Attributes_Secondary_MagicResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MagicResistance"),
		FString("Reduces damage taken from magical abiltiies.")
	);
	GameplayTags.Attributes_Secondary_DodgeChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.DodgeChance"),
		FString("Chance to reduce damage taken or avoid.")
	);
	GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ArmorPenetration"),
		FString("Reduces enemys armor effectiviness.")
	);
	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxHealth"),
		FString("Maximum health.")
	);
	GameplayTags.Attributes_Secondary_MaxStamina = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxStamina"),
		FString("Maxium stamina.")
	);
	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxMana"),
		FString("Maximum stamina")
	);

}

void FLassevaniaGameplayTags::SetLassevaniaGameplayTagReferences()
{

	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Attributes.Primary.Strength"), true
	);



	GameplayTags.Attributes_Primary_Dexterity = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Attributes.Primary.Dexterity")

	);

	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Attributes.Primary.Intelligence")

	);

	GameplayTags.Attributes_Primary_Spirit = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Attributes.Primary.Spirit")
	);


	/* Secondary */

	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Attributes.Secondary.Armor")

	);

	GameplayTags.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Attributes.Secondary.CriticalHitChance")

	);

	GameplayTags.Attributes_Secondary_MagicResistance = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Attributes.Secondary.MagicResistance")

	);
	GameplayTags.Attributes_Secondary_DodgeChance = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Attributes.Secondary.DodgeChance")

	);
	GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Attributes.Secondary.ArmorPenetration")

	);
	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Attributes.Secondary.MaxHealth")

	);
	GameplayTags.Attributes_Secondary_MaxStamina = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Attributes.Secondary.MaxStamina")

	);
	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Attributes.Secondary.MaxMana")
	);



}

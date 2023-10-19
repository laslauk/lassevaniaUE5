// Fill out your copyright notice in the Description page of Project Settings.


#include "LassevaniaGameplayTags.h"
#include "GameplayTagsManager.h"

FLassevaniaGameplayTags FLassevaniaGameplayTags::GameplayTags;

/*

	TODO: jostain syyst‰ initalizenative gameplay tags ei tallenna variableihin
	tageja, mutta editoriin kyll‰. t‰ytyy kutsua erikseen Set-funktiota jotta
	
	FLassevaniaGameplayTags static data tallentuu ja voidaan k‰ytt‰‰. TODO selvit‰
	ett‰ ei tarvisi turhaa funktiokutsua vaan init tekisi suoraan.

*/
void FLassevaniaGameplayTags::InitializeNativeGameplayTags()
{

	 /* Primary */


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

	GameplayTags.Attributes_Primary_Spirit = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Vigor"),
		FString("Increases health")
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

	GameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.BlockChance"),
		FString("Maximum stamina")
	);

	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage")
	);

	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Effect.HitReact")
	);


	GameplayTags.Effects_HitStunned = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Effect.HitStunned")
	);



	/* DAMAGE TYPES */

	GameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Type.Physical"),
		FString("Damage physical / normal type")
	);


	GameplayTags.Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Type.Fire"),
		FString("Damage fire type")
	);

	GameplayTags.Damage_Shadow = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Type.Shadow"),
		FString("Damage shadow type")
	);

	GameplayTags.Damage_Divine = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Type.Divine"),
		FString("Damage Divine type")
	);

	GameplayTags.Damage_Frost = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Type.Frost"),
		FString("Damage Frost type")
	);

	GameplayTags.Damage_Nature = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Type.Nature"),
		FString("Damage nature type")
	);

	GameplayTags.Damage_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Type.Arcane"),
		FString("Damage arcane type")
	);


	/*  RESISTANCES  */



	GameplayTags.Attributes_Resistance_Physical  = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Physical"),
		FString("Resistance to damage type: Physical ")
	);


	GameplayTags.Attributes_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Fire"),
		FString("Resistance to damage type:Fire ")
	);

	GameplayTags.Attributes_Resistance_Shadow = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Shadow"),
		FString("Resistance to damage type:Shadow ")
	);

	GameplayTags.Attributes_Resistance_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Arcane"),
		FString("Resistance to damage type: Arcane ")
	);

	GameplayTags.Attributes_Resistance_Nature = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Nature"),
		FString("Resistance to damage type: Nature")
	);


	GameplayTags.Attributes_Resistance_Frost = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Frost"),
		FString("Resistance to damage type: Frost")
	);

	GameplayTags.Attributes_Resistance_Divine = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Divine"),
		FString("Resistance to damage type: Divine ")
	);




	/* add damage types to array*/


	/* ABILITIES 
	
	*/
	GameplayTags.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Attack"),
		FString("attack ability tag ")
	);


	GameplayTags.Abilities_Deflect = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Deflect"),
		FString("deflect ability tag ")
	);

	/* ability events */
	GameplayTags.Abilities_Event_Parried = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Event.Parried"),
		FString("Ability parried event tag ")
	);


	GameplayTags.Damage_GameplayEvent_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.GameplayEvent.Hitreact"),
		FString("Tag to notify on hitreact gameplayevent")

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

	GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Attributes.Primary.Vigor")
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

	GameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Attributes.Secondary.BlockChance")
	);

	

	GameplayTags.Damage = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Damage")
	);

	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Damage.Effect.HitReact")
	);

	GameplayTags.Effects_HitStunned = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Damage.Effect.HitStunned")
	);



	/*  DAMAGE TYPES  */

	GameplayTags.Damage_Physical = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Damage.Type.Physical")
	);


	GameplayTags.Damage_Fire = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Damage.Type.Fire")
	);


	GameplayTags.Damage_Shadow = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Damage.Type.Shadow")

	);

	GameplayTags.Damage_Divine = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Damage.Type.Divine")

	);

	GameplayTags.Damage_Frost = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Damage.Type.Frost")

	);

	GameplayTags.Damage_Nature = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Damage.Type.Nature")
	
	);

	GameplayTags.Damage_Arcane = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Damage.Type.Arcane")

	);


	/*  RESISTANCES  */


	GameplayTags.Attributes_Resistance_Fire = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Attributes.Resistance.Fire")

	);

	GameplayTags.Attributes_Resistance_Shadow = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Attributes.Resistance.Shadow")

	);

	GameplayTags.Attributes_Resistance_Arcane = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Attributes.Resistance.Arcane")

	);

	GameplayTags.Attributes_Resistance_Nature = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Attributes.Resistance.Nature")

	);


	GameplayTags.Attributes_Resistance_Frost = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Attributes.Resistance.Frost")

	);

	GameplayTags.Attributes_Resistance_Divine = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Attributes.Resistance.Divine")
		
	);

	GameplayTags.Attributes_Resistance_Physical = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Attributes.Resistance.Physical")

	);


	GameplayTags.Abilities_Event_Parried = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Abilities.Event.Parried")
	);


	GameplayTags.Abilities_Deflect = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Abilities.Deflect")

	);


	GameplayTags.Damage_GameplayEvent_HitReact = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Damage.GameplayEvent.Hitreact")

	);

	/* Add to map DMG - RESISTANCE */


	GameplayTags.DamageTypesToResistancesMap.Add(GameplayTags.Damage_Fire, GameplayTags.Attributes_Resistance_Fire);
	GameplayTags.DamageTypesToResistancesMap.Add(GameplayTags.Damage_Physical, GameplayTags.Attributes_Resistance_Physical);
	GameplayTags.DamageTypesToResistancesMap.Add(GameplayTags.Damage_Arcane, GameplayTags.Attributes_Resistance_Arcane);
	GameplayTags.DamageTypesToResistancesMap.Add(GameplayTags.Damage_Frost, GameplayTags.Attributes_Resistance_Frost);
	GameplayTags.DamageTypesToResistancesMap.Add(GameplayTags.Damage_Shadow, GameplayTags.Attributes_Resistance_Shadow);
	GameplayTags.DamageTypesToResistancesMap.Add(GameplayTags.Damage_Nature, GameplayTags.Attributes_Resistance_Nature);
	GameplayTags.DamageTypesToResistancesMap.Add(GameplayTags.Damage_Divine, GameplayTags.Attributes_Resistance_Divine);



}

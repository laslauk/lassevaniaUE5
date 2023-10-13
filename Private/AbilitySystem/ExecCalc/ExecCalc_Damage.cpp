// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"
#include "AbilitySystemComponent.h"
#include "AttributeSetBase.h"
#include "Interfaces/CombatInterface.h"

#include "AbilitySystem/LassevaniaAbilitySystemLibrary.h"
#include "LassevaniaGameplayTags.h"


/* raw internal struct, Ei reflection UE:lle*/
struct LassevaniaDamageStatics
{
	/*
	* 
	* Delcare macro MacroName(P)
	* tekee uuden attributenn P##Def
	* Katso tarkemmin macrosta
	*/


	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHit);

	LassevaniaDamageStatics()
	{

		/* attributes from target / attack receiver */
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, Armor, Target, false /*false snapshot*/);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, BlockChance, Target, false /*false snapshot*/);


		/* Stats from attacker / source*/
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, ArmorPenetration, Source, false /*false snapshot*/);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, CriticalHit, Source, false);


		
	}
};


/* funktio palauttaa aina saman static DStatics, sama objekti*/
static const LassevaniaDamageStatics& DamageStatics()
{
	
	static LassevaniaDamageStatics DStatics;
	return DStatics;


}

UExecCalc_Damage::UExecCalc_Damage()
{
	/* use this capture definition for this specific attribute */
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDef);

}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{

	/* -----------------  Boilerplate START -----------------*/
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	 AActor* SourceAvatarActor = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	 AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	 ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(SourceAvatarActor);
	 ICombatInterface* TargetCombatInterface = Cast<ICombatInterface>(TargetAvatar);
	/* ----------------- Boilerplate END ----------------- */



	UCharacterClassInfo* CharClassInfo = ULassevaniaAbilitySystemLibrary::GetCharacterClassInfo(SourceAvatarActor);

	/* ------ Get calculation coefficient curve from game mode's class data curves / tables ------- */
	FRealCurve* ArmorPenCurve = CharClassInfo->DamageCalculationCoefficients->FindCurve(FName("ArmorPenetration"), FString());
	const float ArmorPenCoefficient = ArmorPenCurve->Eval(SourceCombatInterface->GetAvatarLevel());

	FRealCurve* EffectriveArmorCurve = CharClassInfo->DamageCalculationCoefficients->FindCurve(FName("EffectiveArmor"), FString());
	const float EffectriveArmorCoefficient = EffectriveArmorCurve->Eval(TargetCombatInterface->GetAvatarLevel());


	// Get damage from SetByCallerMagnitude
	float Damage = Spec.GetSetByCallerMagnitude(FLassevaniaGameplayTags::Get().Damage);


	/* Block */
	float TargetBlockChance = 0.f;
	TargetBlockChance = FMath::Max<float>(TargetBlockChance, 0.f);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvaluationParameters, TargetBlockChance);

	const bool bBlocked = FMath::RandRange(1.f, 100.f) < TargetBlockChance;
	Damage = bBlocked ? (Damage / 2.f) : Damage; 	/* half the damage if blocked */



	/* Armor penetration flat % ignore of target armor*/
	float SourceArmorPenetration = 0.f;
	SourceArmorPenetration = FMath::Max<float>(SourceArmorPenetration, 0.f);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef, EvaluationParameters, SourceArmorPenetration);


	float TargetArmor = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluationParameters, TargetArmor);
	TargetArmor = FMath::Max<float>(0.f, TargetArmor); 	/* clamp to positive */


	/*---- DAMAGE CALCULATION FROM ALL DATA---- */
	const float EffectiveArmor = (TargetArmor *= (100 - SourceArmorPenetration * EffectriveArmorCoefficient) / 100.f);

	/*Reduce damage with armor after pen 1% per armor */
	Damage *= (100 - EffectiveArmor * EffectriveArmorCoefficient) / 100.f;


	/* Critical hit */
	float SourceCriticalHitDamage = 0.0f; //  PLACEHOLDER FOR CRIT BONUS


	float SourceCriticalHitChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitDef, EvaluationParameters, SourceCriticalHitChance);
	SourceCriticalHitChance = FMath::Max<float>(SourceCriticalHitChance, 0.f);

	float PlaceHolderCriticalHitResistance = 0.0f;
	const float EffectiveCriticalHitChance = (SourceCriticalHitChance - PlaceHolderCriticalHitResistance * 0.15f);




	const bool bIsCritical = FMath::RandRange(1.f, 100.f) < EffectiveCriticalHitChance;

	if (bIsCritical)
	{
		UE_LOG(LogTemp, Warning, TEXT("!!!!!!!!!!!!!!!!!!!!!!!!!!critical hit chance: %f"), EffectiveCriticalHitChance);
	}

	Damage = bIsCritical ? (Damage * 2.0f + SourceCriticalHitDamage) : Damage;
	/* Block test*/


	FGameplayModifierEvaluatedData EvaluatedData(UAttributeSetBase::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);




}

// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"
#include "AbilitySystemComponent.h"
#include "Character/EnemyDummyPawn.h"
#include "AttributeSetBase.h"
#include "LassevaniaAbilityTypes.h"
#include "Interfaces/CombatInterface.h"
#include "AbilitySystemBlueprintLibrary.h"

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




	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArcaneResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(DivineResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(FrostResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ShadowResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(NatureResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistance);



	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagToCaptureDefs;


	LassevaniaDamageStatics()
	{

		/* attributes from target / attack receiver */
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, Armor, Target, false /*false snapshot*/);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, BlockChance, Target, false /*false snapshot*/);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, FireResistance, Target, false /*false snapshot*/);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, ArcaneResistance, Target, false /*false snapshot*/);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, DivineResistance, Target, false /*false snapshot*/);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, FrostResistance, Target, false /*false snapshot*/);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, ShadowResistance, Target, false /*false snapshot*/);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, NatureResistance, Target, false /*false snapshot*/);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, PhysicalResistance, Target, false /*false snapshot*/);

		/* Stats from attacker / source*/
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, ArmorPenetration, Source, false /*false snapshot*/);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, CriticalHit, Source, false);

		const FLassevaniaGameplayTags& Tags = FLassevaniaGameplayTags::Get();


		TagToCaptureDefs.Add(Tags.Attributes_Secondary_Armor, ArmorDef);
		TagToCaptureDefs.Add(Tags.Attributes_Secondary_BlockChance, BlockChanceDef);

		TagToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalHitChance, CriticalHitDef);
		TagToCaptureDefs.Add(Tags.Attributes_Secondary_ArmorPenetration, ArmorPenetrationDef);

		TagToCaptureDefs.Add(Tags.Attributes_Resistance_Fire, FireResistanceDef);
		TagToCaptureDefs.Add(Tags.Attributes_Resistance_Arcane, ArcaneResistanceDef);
		TagToCaptureDefs.Add(Tags.Attributes_Resistance_Nature, NatureResistanceDef);
		TagToCaptureDefs.Add(Tags.Attributes_Resistance_Shadow, ShadowResistanceDef);
		TagToCaptureDefs.Add(Tags.Attributes_Resistance_Frost, FrostResistanceDef);
		TagToCaptureDefs.Add(Tags.Attributes_Resistance_Divine, DivineResistanceDef);
		TagToCaptureDefs.Add(Tags.Attributes_Resistance_Physical, PhysicalResistanceDef);
		
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

	RelevantAttributesToCapture.Add(DamageStatics().FireResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArcaneResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ShadowResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().FrostResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().NatureResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().DivineResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalResistanceDef);

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
	 FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();

	UCharacterClassInfo* CharClassInfo = ULassevaniaAbilitySystemLibrary::GetCharacterClassInfo(SourceAvatarActor);

	/* ------ Get calculation coefficient curve from game mode's class data curves / tables ------- */
	FRealCurve* ArmorPenCurve = CharClassInfo->DamageCalculationCoefficients->FindCurve(FName("ArmorPenetration"), FString());
	const float ArmorPenCoefficient = ArmorPenCurve->Eval(SourceCombatInterface->GetAvatarLevel());

	FRealCurve* EffectriveArmorCurve = CharClassInfo->DamageCalculationCoefficients->FindCurve(FName("EffectiveArmor"), FString());
	const float EffectriveArmorCoefficient = EffectriveArmorCurve->Eval(TargetCombatInterface->GetAvatarLevel());


	// Get damage from SetByCallerMagnitude
	float Damage = 0;

	for (auto& DamageResPair : FLassevaniaGameplayTags::Get().DamageTypesToResistancesMap)
	{

		const FGameplayTag DamageTypeTag = DamageResPair.Key;
		const FGameplayTag ResistanceTag = DamageResPair.Value;

		checkf(LassevaniaDamageStatics().TagToCaptureDefs.Contains(ResistanceTag),
			TEXT("LassevaniaDamageStatics().TagToCaptureDefs - DOES NOT CONTAINS Tag [%s] In ExecCalc_daamge"),
			*ResistanceTag.ToString()
			);

		const FGameplayEffectAttributeCaptureDefinition CaptureDef = LassevaniaDamageStatics().TagToCaptureDefs[ResistanceTag];


		float DamageTypeValue = Spec.GetSetByCallerMagnitude(DamageResPair.Key, false);

		float Resistance = 0.0f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDef, EvaluationParameters, Resistance);
		Resistance = FMath::Clamp(Resistance, 0.f, 100.f); //limit to 100% dmg resistance

		DamageTypeValue = DamageTypeValue * ((100.f - Resistance) / 100.f);

		Damage += DamageTypeValue;
	}



	/* Block */
	float TargetBlockChance = 0.f;
	TargetBlockChance = FMath::Max<float>(TargetBlockChance, 0.f);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvaluationParameters, TargetBlockChance);

	const bool bBlocked = FMath::RandRange(1.f, 100.f) < TargetBlockChance;
	Damage = bBlocked ? (Damage / 2.f) : Damage; 	/* half the damage if blocked */

	UE_LOG(LogTemp, Warning, TEXT("Target block chance chance: %f"), TargetBlockChance);


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


	 bool bIsCritical = FMath::RandRange(1.f, 100.f) < EffectiveCriticalHitChance;

	if (bIsCritical)
	{
		UE_LOG(LogTemp, Warning, TEXT("!!!!!!!!!!!!!!!!!!!!!!!!!!critical hit !!!!!!!!!!!!"));
	}
	UE_LOG(LogTemp, Warning, TEXT("!!!!!!!!!!!!!!!!!!!!!!!!!!critical hit chance: %f"), EffectiveCriticalHitChance);
	UE_LOG(LogTemp, Warning, TEXT("!!!!!!!!!!!!!!!!!!!!!!!!!!critical hit chance: %f"), SourceCriticalHitChance);

	if (bBlocked)
	{
		UE_LOG(LogTemp, Warning, TEXT("Blocked :((((((((((("));
	}

	Damage = bIsCritical ? (Damage * 2.0f + SourceCriticalHitDamage) : Damage;
	/* Block test*/

	/* ----------set spec: crit and block booleans --------*/

	const FLassevaniaGameplayTags& GameplayTags = FLassevaniaGameplayTags::Get();
	bool isParryable = ULassevaniaAbilitySystemLibrary::IsParryable(EffectContextHandle);

	if (isParryable)
	{
		bool IsDeflecting = TargetASC->HasMatchingGameplayTag(GameplayTags.Abilities_Deflect);
		
		if (IsDeflecting)
		{
			FGameplayEventData EventData;
			EventData.Instigator = SourceAvatarActor;
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(TargetAvatar, GameplayTags.Abilities_Event_Parried, EventData);
			Damage = 0.0f;
		}
	}



//  FGameplayEffectSpec * MutableSpec = ExecutionParams.GetOwningSpecForPreExecuteMod();
//	FLassevaniaGameplayEffectContext* Context = static_cast<FLassevaniaGameplayEffectContext*>(Spec->GetContext().Get());
//	ULassevaniaAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, isCrit);
	
//  Context->SetIsCriticalHit(true);

	
	//FLassevaniaGameplayEffectContext* LassevaniaEffectContext = static_cast<FLassevaniaGameplayEffectContext*>(EffectContextHandle.Get());
	//LassevaniaEffectContext->SetIsCriticalHit(true);
	
    ULassevaniaAbilitySystemLibrary::SetIsBlockedHit(EffectContextHandle, bBlocked);
	ULassevaniaAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, bIsCritical);
	
	/* Huom! IncomingDamage attribute*/
	FGameplayModifierEvaluatedData EvaluatedData(UAttributeSetBase::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);




}

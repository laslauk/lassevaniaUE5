// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ExecCalc/ExecCalc_DamageTest.h"
#include "LassevaniaAbilityTypes.h"

struct LVDamageStatics
{
//	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
//	DECLARE_ATTRIBUTE_CAPTUREDEF(Damage);

	LVDamageStatics()
	{
		// Snapshot happens at time of GESpec creation

		// We're not capturing anything from the Source in this example, but there could be like AttackPower attributes that you might want.

		// Capture optional Damage set on the damage GE as a CalculationModifier under the ExecutionCalculation
		//DEFINE_ATTRIBUTE_CAPTUREDEF(UGSAttributeSetBase, Damage, Source, true);

		// Capture the Target's Armor. Don't snapshot.
	//	DEFINE_ATTRIBUTE_CAPTUREDEF(UGSAttributeSetBase, Armor, Target, false);
	}
};





UExecCalc_DamageTest::UExecCalc_DamageTest()
{
	//HeadShotMultiplier = 1.5f;

	//RelevantAttributesToCapture.Add(DamageStatics().DamageDef);
	//RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
}


void UExecCalc_DamageTest::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	FGameplayEffectSpec* MutableSpec = ExecutionParams.GetOwningSpecForPreExecuteMod();
	FGameplayEffectContext* Context = MutableSpec->GetContext().Get();
	
	static_cast<FLassevaniaGameplayEffectContext*>(Context)->SetIsCriticalHit(true);


//	FGameplayModifierEvaluatedData EvaluatedData(UAttributeSetBase::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
//	OutExecutionOutput.AddOutputModifier(EvaluatedData);

}

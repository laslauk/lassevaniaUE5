// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ModMagCalc/MMC_MaxHealth.h"
#include "AttributeSetBase.h"
#include "Interfaces/CombatInterface.h"


UMMC_MaxHealth::UMMC_MaxHealth()
{

	/* Do a capture, from target (playerCharacter) */
	VigorDef.AttributeToCapture = UAttributeSetBase::GetStrengthAttribute();

	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(VigorDef);

}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	/* float passed by ref*/
	float Strength = 0.f; //Strength is set to value of Strength on target
	GetCapturedAttributeMagnitude(VigorDef, Spec, EvaluationParameters, Strength);

	Strength = FMath::Max<float>(Strength, 0.f);


	/* Source object is now player character, effect is from playerchar*/

	/* Source object must be set, Now set in PlayerCharacterbase class*/
	/* set in APlayerCharacterBase::ApplyEffectToSelf()*/
	ICombatInterface* CombatInterface = Cast<ICombatInterface>( Spec.GetContext().GetSourceObject() );

	if (CombatInterface)
	{
		const int32 PlayerLevel = CombatInterface->GetAvatarLevel();

		/* 25f base + Strength*2.f + 5 * playerLevel */
		return 25.0f + 2.0f * Strength + 5 * PlayerLevel;
	}
	UE_LOG(LogTemp, Warning, TEXT("MMC HEALTH PROBLEMS!"));
	return 0.f;

}

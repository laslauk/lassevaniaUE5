// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ScalableFloat.h"
#include "CharacterClassInfo.generated.h"

class UGameplayEffect;

UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	Warrior,
	Knight,
	Sorcerer,
	Archer
};



USTRUCT(BlueprintType)
struct FCharacterClassDefaultInfo
{
	GENERATED_BODY()

public:

		UPROPERTY(EditDefaultsOnly,Category = "Class Defaults")
		TSubclassOf<UGameplayEffect> PrimaryAttributes;

		UPROPERTY(EditDefaultsOnly, Category = "Common Class Defaults | XP Reward Curve")
		FScalableFloat XPReward = FScalableFloat();
};

/**
 * 
 */
UCLASS()
class LASSEVANIA_API UCharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()
public:



	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TMap<ECharacterClass, FCharacterClassDefaultInfo> CharacterClassInformation;

	UPROPERTY(EditDefaultsOnly, Category = "Common Class Defaults")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;

	UPROPERTY(EditDefaultsOnly, Category = "Common Class Defaults")
	TSubclassOf<UGameplayEffect> VitalAttributes;


	FCharacterClassDefaultInfo GetClassDefaultInfo(ECharacterClass CharacterClass);

	UPROPERTY(EditDefaultsOnly, Category = "Common Class Defaults | Damage")
	TObjectPtr<UCurveTable> DamageCalculationCoefficients;



//	TObjectPtr<UCurveTable> XPRewardCurve;


};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/GameplayAbility_FromEquipment.h"
#include "GameplayAbility_MeleeWeapon.generated.h"




class UGameplayEffect;
/**
 * 
 */
UCLASS()
class LASSEVANIA_API UGameplayAbility_MeleeWeapon : public UGameplayAbility_FromEquipment
{
	GENERATED_BODY()

public:


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;



	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	FScalableFloat Damage;

	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/GameplayAbilityBase.h"
#include "GameplayAbility_FromEquipment.generated.h"

class UInventoryItemInstance;

/**
 * 
 */
UCLASS()
class LASSEVANIA_API UGameplayAbility_FromEquipment : public UGameplayAbilityBase
{
	GENERATED_BODY()
public:


	UFUNCTION(BlueprintCallable, Category = "Lassevania|Ability")
		UInventoryItemInstance* GetAssociatedItem() const;



};

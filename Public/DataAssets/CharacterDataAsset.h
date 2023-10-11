// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "../LassevaniaCommonTypes.h"
#include "CharacterDataAsset.generated.h"

class ULassevaniaAbilitySet;
class ULassevaniaInputConfig;
/**
 * 
 */
UCLASS()
class LASSEVANIA_API UCharacterDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:

	// Ability sets to grant to this pawn's ability system.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TArray<TObjectPtr<ULassevaniaAbilitySet>> AbilitySets; /*Data assetteja*/
	

	// Input configuration used by player controlled pawns to create input mappings and bind input actions.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lyra|Input")
		TObjectPtr<ULassevaniaInputConfig> InputConfig;
};

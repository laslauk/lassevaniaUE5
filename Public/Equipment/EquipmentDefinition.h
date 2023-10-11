// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"
#include "Math/Transform.h"
#include "Templates/SubclassOf.h"
#include "UObject/NameTypes.h"
#include "UObject/Object.h"
#include "UObject/ObjectPtr.h"
#include "UObject/UObjectGlobals.h"

#include "UObject/NoExportTypes.h"
#include "EquipmentDefinition.generated.h"

class AActor;
class ULassevaniaAbilitySet;
class UEquipmentInstance;


USTRUCT()
struct FEquipmentActorToSpawn
{
	GENERATED_BODY()


		FEquipmentActorToSpawn()
	{
	}

	UPROPERTY(EditAnywhere, Category = Equipment)
		TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditAnywhere, Category = Equipment)
		FName AttachSocket;

	UPROPERTY(EditAnywhere, Category = Equipment)
		FTransform AttachTransform;

};

/**
 *  *
 * Definition of a piece of equipment that can be applied to a pawn - such as helmet, shield, necklace
 */


UCLASS(Blueprintable, Const, Abstract, BlueprintType)
class LASSEVANIA_API UEquipmentDefinition : public UObject
{
	GENERATED_BODY()
public:

	UEquipmentDefinition(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// Class to spawn
	UPROPERTY(EditDefaultsOnly, Category = Equipment)
		TSubclassOf<UEquipmentInstance> InstanceType;

	// Gameplay ability sets to grant when this is equipped
	UPROPERTY(EditDefaultsOnly, Category = Equipment)
		TArray<TObjectPtr<const ULassevaniaAbilitySet>> AbilitySetsToGrant;

	// Actors to spawn on the pawn when this is equipped
	UPROPERTY(EditDefaultsOnly, Category = Equipment)
		TArray<FEquipmentActorToSpawn> ActorsToSpawn;
	
};

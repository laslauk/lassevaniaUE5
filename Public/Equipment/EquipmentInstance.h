// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Containers/Array.h"
#include "Engine/World.h"
#include "Templates/SubclassOf.h"
#include "UObject/Object.h"
#include "Net/UnrealNetwork.h"
#include "UObject/UObjectGlobals.h"

#include "EquipmentInstance.generated.h"

class AActor;
class APawn;
struct FFrame;
struct FEquipmentActorToSpawn;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class LASSEVANIA_API UEquipmentInstance : public UObject
{
	GENERATED_BODY()

public:

	UEquipmentInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());


	/*
	//~UObject interface
	virtual bool IsSupportedForNetworking() const override { return true; }
		*/
	virtual UWorld* GetWorld() const override final;
	//~End of UObject interface

	UFUNCTION(BlueprintPure, Category = Equipment)
	UObject* GetInstigator() const { return Instigator; }

	void SetInstigator(UObject* InInstigator) { Instigator = InInstigator; }

	UFUNCTION(BlueprintPure, Category = Equipment)
	APawn* GetPawn() const;

	UFUNCTION(BlueprintPure, Category = Equipment, meta = (DeterminesOutputType = PawnType))
	APawn* GetTypedPawn(TSubclassOf<APawn> PawnType) const;

	UFUNCTION(BlueprintPure, Category = Equipment)
	TArray<AActor*> GetSpawnedActors() const { return SpawnedActors; }

	virtual void SpawnEquipmentActors(const TArray<FEquipmentActorToSpawn>& ActorsToSpawn);
	virtual void DestroyEquipmentActors();

	virtual void OnEquipped();
	virtual void OnUnequipped();

	UFUNCTION(BlueprintImplementableEvent, Category = Equipment, meta = (DisplayName = "OnEquipped"))
	void K2_OnEquipped();

	UFUNCTION(BlueprintImplementableEvent, Category = Equipment, meta = (DisplayName = "OnUnequipped"))
	void K2_OnUnequipped();


private:
	UPROPERTY(/*ReplicatedUsing = OnRep_Instigator*/)
		TObjectPtr<UObject> Instigator;

	UPROPERTY(/*Replicated*/)
		TArray<TObjectPtr<AActor>> SpawnedActors;

};

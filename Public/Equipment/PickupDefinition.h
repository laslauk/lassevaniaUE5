// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PickupDefinition.generated.h"


class UInventoryItemDefinition;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Const, Meta = (DisplayName = "PickupDefinition", ShortTooltip = "Data asset used to configure a pickup."))
class LASSEVANIA_API UPickupDefinition : public UDataAsset
{
	GENERATED_BODY()

public:


	UPickupDefinition();

	//Defines the pickup's actors to spawn, abilities to grant, and tags to add
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pickup|Equipment")
	TSubclassOf<UInventoryItemDefinition> InventoryItemDefinition;


	//Visual representation of the pickup in tworld
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pickup|Mesh")
		TObjectPtr<UStaticMesh> DisplayMesh;

	//Visual representation of the pickup in tworld
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup|Stack")
		int32 StackSize;

	//Sound to play when picked up
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pickup")
		TObjectPtr<USoundBase> PickedUpSound;

	//Sound to play when pickup is respawned
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pickup")
		TObjectPtr<USoundBase> DroppedSound;

	//Sets the height of the display mesh above the Weapon spawner
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pickup|Mesh")
		FVector Scale = FVector(1.0f, 1.0f, 1.0f);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "Inventory/InventoryItemDefinition.h"

#include "InventoryFragment_EquippableItem.generated.h"

class UEquipmentDefinition;
class UObject;

UCLASS()
class LASSEVANIA_API UInventoryFragment_EquippableItem : public UInventoryItemFragment
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, Category = Lassevania)
	TSubclassOf<UEquipmentDefinition> EquipmentDefinition;
	
};


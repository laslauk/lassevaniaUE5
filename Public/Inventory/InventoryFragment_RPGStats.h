// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/InventoryItemDefinition.h"
#include "../LassevaniaCommonTypes.h"
#include "InventoryFragment_RPGStats.generated.h"

/**
 * 
 */
UCLASS()
class LASSEVANIA_API UInventoryFragment_RPGStats : public UInventoryItemFragment
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FItemStats ItemStats;

};

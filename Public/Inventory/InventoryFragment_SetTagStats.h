// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/InventoryItemDefinition.h"
#include "GameplayTagContainer.h"
#include "InventoryFragment_SetTagStats.generated.h"


class UInventoryItemInstance;
/**
 * 
 */
UCLASS()
class LASSEVANIA_API UInventoryFragment_SetTagStats : public UInventoryItemFragment
{
	GENERATED_BODY()
public:

	/* TODO BETTER SYSTEM: Tag - FIRST IS !STACK MAX SIZE*/
	UPROPERTY(EditDefaultsOnly, Category = Equipment)
	TMap<FGameplayTag, int32> InitialItemStats;


	virtual void OnInstanceCreated(UInventoryItemInstance* Instance) const override;

	int32 GetItemStatByTag(FGameplayTag Tag) const;
private:
};

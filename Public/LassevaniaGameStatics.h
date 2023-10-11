// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LassevaniaGameStatics.generated.h"

class UInventoryComponent;

/**
 * 
 */
UCLASS()
class LASSEVANIA_API ULassevaniaGameStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static UInventoryComponent* GetPlayerInventoryComponent(UObject* WorldContextObject);

};

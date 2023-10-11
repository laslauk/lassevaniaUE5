// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameModeLassevania.generated.h"

/**
 * 
 */
UCLASS()
class LASSEVANIA_API AGameModeLassevania : public AGameMode
{
	GENERATED_BODY()

public:

	virtual void InitGame(const FString& MapName,
		const FString& Options,
		FString& ErrorMessage) override;
};

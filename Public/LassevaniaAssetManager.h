// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "LassevaniaAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class LASSEVANIA_API ULassevaniaAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:

	static ULassevaniaAssetManager& Get();


protected:


	/* UAssetManager interface*/
	virtual void StartInitialLoading() override;
	
};

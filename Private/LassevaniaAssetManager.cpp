// Fill out your copyright notice in the Description page of Project Settings.


#include "LassevaniaAssetManager.h"
#include "LassevaniaGameplayTags.h"

ULassevaniaAssetManager& ULassevaniaAssetManager::Get()
{
	check(GEngine);

	ULassevaniaAssetManager* LassevaniaAssetManager = Cast< ULassevaniaAssetManager>(GEngine->AssetManager);
	return *LassevaniaAssetManager;
}

void ULassevaniaAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FLassevaniaGameplayTags::InitializeNativeGameplayTags();



}

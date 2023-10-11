// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeLassevania.h"
#include "LassevaniaGameplayTags.h"


void AGameModeLassevania::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	FLassevaniaGameplayTags::Get().SetLassevaniaGameplayTagReferences();
	UE_LOG(LogTemp, Warning, TEXT("helloooo"));
}

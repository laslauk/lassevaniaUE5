// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "LassevaniaInputConfig.generated.h"

class UInputAction;
class UObject;
struct FFrame;
/**
 * FLyraInputAction
 *
 *	Struct used to map a input action to a gameplay input tag.
 * 
 * IMPORTANT!!! MAP INPUT ACTION -> GAS ABiltiy TAG for ACTIVATION !
 */
USTRUCT(BlueprintType)
struct FLVInputAction
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TObjectPtr<const UInputAction> InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "InputTag"))
		FGameplayTag InputTag;
};


/**
 * 
 */
UCLASS()
class LASSEVANIA_API ULassevaniaInputConfig : public UDataAsset
{
	GENERATED_BODY()

		/* CONSTRUCTOR WILL MAP ABILITY TAGS AND INPUTS!*/
		ULassevaniaInputConfig();


public:
	UFUNCTION(BlueprintCallable, Category = "LasseVania|Pawn")
	const UInputAction* FindNativeInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = true) const;

	UFUNCTION(BlueprintCallable, Category = "LasseVania|Pawn")
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = true) const;
	

public:
	// List of input actions used by the owner.  These input actions are mapped to a gameplay tag and must be manually bound.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
		TArray<FLVInputAction> NativeInputActions;

	// List of input actions used by the owner.  These input actions are mapped to a gameplay tag and are automatically bound to abilities with matching input tags.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
		TArray<FLVInputAction> AbilityInputActions;
};

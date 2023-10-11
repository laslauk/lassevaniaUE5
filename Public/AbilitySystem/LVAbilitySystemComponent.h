// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "LVAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class LASSEVANIA_API ULVAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
		

public:
//	ULVAbilitySystemComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:

	ULVAbilitySystemComponent(const FObjectInitializer& ObjectInitializer);

	void CancelInputActivatedAbilities(bool bReplicateCancelAbility);

	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

	void ProcessAbilityInput(float DeltaTime, bool bGamePaused);
	void ClearAbilityInput();


	UFUNCTION(BlueprintCallable)
	void OnAbilityEnded(class UGameplayAbility* Ability);


	/* TODO - Useampi input que, nyt vain seuraava katotaan kun ability loppuu*/
	/* TODO - Add timer joka clearaa inputn painallukse jälkee kun ekan kerran failaa*/
	TArray<FGameplayAbilitySpecHandle> InputPressedSpecHandlesQue;

	UFUNCTION(BlueprintCallable)
	void ClearInputPressedQue();

private:

	// Handles to abilities that had their input pressed this frame.
	TArray<FGameplayAbilitySpecHandle> InputPressedSpecHandles;

	// Handles to abilities that had their input released this frame.
	TArray<FGameplayAbilitySpecHandle> InputReleasedSpecHandles;

	// Handles to abilities that have their input held.
	TArray<FGameplayAbilitySpecHandle> InputHeldSpecHandles;



public:
	void TryActivateAbilitiesOnSpawn();

	virtual void AbilitySpecInputPressed(FGameplayAbilitySpec& Spec) override;
	virtual void AbilitySpecInputReleased(FGameplayAbilitySpec& Spec) override;
};

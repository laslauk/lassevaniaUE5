// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"

#include "AbilityTask_CheckActorsLinedAxis.generated.h"


//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActorsLinedforAxisSignature, const TArray<AActor*>&, HitActorsArray);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FActorsLinedforAxisSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FShouldAttemptAirStrikeSignature);


/**
 * 
 */
UCLASS()
class LASSEVANIA_API UAbilityTask_CheckActorsLinedAxis : public UAbilityTask
{
	GENERATED_BODY()


public:
	UAbilityTask_CheckActorsLinedAxis(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(
		BlueprintCallable, Category = "Ability|Tasks",
		meta =
		(DisplayName = "Trace for Aligned Actors",
			HidePin = "OwningAbility",
			DefaultToSelf = "OwningAbility",
			BlueprintInternalUseOnly = "true")
	)
	static UAbilityTask_CheckActorsLinedAxis* CreateAbilityTask_CheckActorsLinedAxis(UGameplayAbility* OwningAbility, float fDoAirStrikeTreshold,
			EAxis::Type AlignAxis, AActor* Actor, AActor* OtherActor, float Treshold);


	UPROPERTY(BlueprintAssignable)
		FActorsLinedforAxisSignature ActorsLined;
		

	UPROPERTY(BlueprintAssignable)
		FShouldAttemptAirStrikeSignature ShouldAttempAirStrike;

	virtual void TickTask(float DeltaTime) override;
	EAxis::Type AxisToCheck;
	AActor* Actor;
	AActor* OtherActor;

	float fDoAirStrikeTreshold = 0.0f;
	float Treshold = 0.0f;
private:
	virtual void Activate() override;



};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "MeleeAttackTraceForTargetData.generated.h"

/**
 * 
 */



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHitResultTargetDataSignature, const TArray<AActor*>& , HitActorsArray);

UCLASS()
class LASSEVANIA_API UMeleeAttackTraceForTargetData : public UAbilityTask
{
	GENERATED_BODY()

public:

	UMeleeAttackTraceForTargetData(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(
		BlueprintCallable, Category = "Ability|Tasks",
		meta =
		(DisplayName = "Trace For Targets",
			HidePin = "OwningAbility",
			DefaultToSelf = "OwningAbility",
			BlueprintInternalUseOnly = "true")
	)
		static UMeleeAttackTraceForTargetData* CreateMeleeAttackTraceForTargetData(UGameplayAbility* OwningAbility, FVector AttackDamageCollisionBoxExtend,  
			float InCollisionOffset, FGameplayTag StartTag, FGameplayTag EndTag, bool bDrawDebug);

	void GameplayEventCallback(const FGameplayEventData* Payload);

	bool bDrawDebug;
	/** Tick function for this task, if bTickingTask == true */
	virtual void TickTask(float DeltaTime) override;

	bool bDoTrace = false;
	bool bOldDoTrace = bDoTrace;

	FGameplayTag StartTag;
	FGameplayTag EndTag;

	float AttackCollisionOffset;
	FVector AttackCollisionBox;

	UPROPERTY(BlueprintAssignable)
	FHitResultTargetDataSignature AttackEnded;

	FDelegateHandle MyHandle;

	TArray<AActor*> NewHitActors;
	TArray<AActor*> AllHitActors;

private:
	virtual void Activate() override;



};

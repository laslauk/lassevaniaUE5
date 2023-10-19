// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BTService_FindNearbyPlayer.generated.h"

/**
 * 
 */
UCLASS()
class LASSEVANIA_API UBTService_FindNearbyPlayer : public UBTService_BlueprintBase
{
	GENERATED_BODY()
	
protected:

	/* Tick for services, overriden*/
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FBlackboardKeySelector TargetToFollowSelector;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FBlackboardKeySelector DistanceToTargetSelector;

public:



};

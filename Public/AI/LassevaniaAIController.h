// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "LassevaniaAIController.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;

/**
 *  has behaviour tree, brain comp
 */
UCLASS()
class LASSEVANIA_API ALassevaniaAIController : public AAIController
{
	GENERATED_BODY()
public:
	ALassevaniaAIController();


protected:


	UPROPERTY()
	TObjectPtr<UBlackboardComponent> BlackboardComponent;

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviourTreeComponent;

};

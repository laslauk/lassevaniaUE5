
// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/LassevaniaAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ALassevaniaAIController::ALassevaniaAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("Blackboard Component");
	BehaviourTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviourTree Component");

}
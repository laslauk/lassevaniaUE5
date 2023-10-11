// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueSystem/Tasks/DialogueTask_ModifyResource.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "DialogueSystem/DialogueWidget.h"
#include "DialogueSystem/DialogueSystemComponent.h"
#include "LassevaniaCommonTypes.h"
#include "DialogueSystem/DialogueAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interfaces/DialogSystemInterface.h"

EBTNodeResult::Type UDialogueTask_ModifyResource::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	GetWorld()->GetFirstPlayerController(); //isngle player only!

	return EBTNodeResult::Type();
}

FString UDialogueTask_ModifyResource::GetStaticDescription() const
{
	return FString();
}

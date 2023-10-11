// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueSystem/Tasks/DialogTask_SetDialogueFlags.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "DialogueSystem/DialogueWidget.h"
#include "DialogueSystem/DialogueSystemComponent.h"
#include "LassevaniaCommonTypes.h"
#include "Sound/SoundBase.h"
#include "DialogueSystem/DialogueAIController.h"
#include "Interfaces/DialogSystemInterface.h"

#include "BehaviorTree/BlackboardComponent.h"

UDialogTask_SetDialogueFlags::UDialogTask_SetDialogueFlags(FObjectInitializer const& object_initializer)
{
	
}

EBTNodeResult::Type UDialogTask_SetDialogueFlags::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{




	UBlackboardData* BBasset = GetBlackboardAsset();
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	AAIController* AIController = OwnerComp.GetAIOwner();

	IDialogSystemInterface* Interface = Cast<IDialogSystemInterface>(AIController);

	if (Interface)
	{
		UDialogueSystemComponent* DSC = Interface->GetDialogSystemComponent();

		DSC->AddTagFlags(TagsToSet);

	}


	return EBTNodeResult::Succeeded;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueSystem/Tasks/DialogTask_ExitDialogue.h"

#include "DialogueSystem/DialogueWidget.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UDialogTask_ExitDialogue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	UDialogueWidget* DialogWidget = Cast<UDialogueWidget>(BlackboardComp->GetValueAsObject(DialogueWidgetKey.SelectedKeyName));


	if (DialogWidget)
	{
		DialogWidget->ExitDialogue();
	}


	return EBTNodeResult::Succeeded;
}

FString UDialogTask_ExitDialogue::GetStaticDescription() const
{

	return FString::Printf(
		TEXT("Exit Dialogue")
		//*FString::SanitizeFloat(MyFloatValue)
	);
}

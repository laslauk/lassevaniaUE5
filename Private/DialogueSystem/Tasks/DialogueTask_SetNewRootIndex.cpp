// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueSystem/Tasks/DialogueTask_SetNewRootIndex.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UDialogueTask_SetNewRootIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	/*
		
		UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
		MyBlackboard->ClearValue(Key.SelectedKeyName);
		MyBlackboard->GetValueAsBool(Key.SelectedKeyName);
		MyBlackboard->SetValueAsBool(Key.SelectedKeyName, false);
*/

	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsInt(RootIndexOut.SelectedKeyName, NewIndex);
	} 

	return EBTNodeResult::Succeeded;
}



FString UDialogueTask_SetNewRootIndex::GetStaticDescription() const
{




	return FString::Printf(
		TEXT("RootIndexOut Key: %s%sNew Index: %s"),
		*RootIndexOut.SelectedKeyName.ToString(),
		LINE_TERMINATOR,
		*FString::FromInt(NewIndex)
		//*FString::SanitizeFloat(MyFloatValue)
	);


}
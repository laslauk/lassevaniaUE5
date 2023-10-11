// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueSystem/Tasks/DialogTask_Reply.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "DialogueSystem/DialogueWidget.h"
#include "DialogueSystem/DialogueSystemComponent.h"
#include "LassevaniaCommonTypes.h"
#include "DialogueSystem/DialogueAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interfaces/DialogSystemInterface.h"



UDialogTask_Reply::UDialogTask_Reply(FObjectInitializer const& object_initializer)
{
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UDialogTask_Reply::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComponent = &OwnerComp;
	NodeMemory = NodeMemory;

	FilteredReplyTexts.Empty();


	//UBlackboardData* BBasset = GetBlackboardAsset();


	 BlackboardComp = OwnerComp.GetBlackboardComponent();

	DialogWidget  = Cast<UDialogueWidget>(BlackboardComp->GetValueAsObject(DialogueWidgetKey.SelectedKeyName));
	AAIController* AIController = OwnerComp.GetAIOwner();

	IDialogSystemInterface* Interface = Cast<IDialogSystemInterface>(AIController);

	if (Interface)
	{
		UDialogueSystemComponent* DSC = Interface->GetDialogSystemComponent();
		FGameplayTagContainer DialogTags = DSC->GetDialogueTags();

		/* Filter replys that require a certain tag */
		for (auto DialogData : ReplyTexts)
		{
			if (DialogData.RequiredTagFlag == FGameplayTag::EmptyTag)
			{
				FilteredReplyTexts.Add(DialogData);
			}
			else
			{
				bool bHasTag = DialogTags.HasTagExact(DialogData.RequiredTagFlag);
				if (bHasTag)
				{
					FilteredReplyTexts.Add(DialogData);
				}

			}
		}

		/* Reply functionality */



		DialogWidget->Reply(FilteredReplyTexts);

		DialogWidget->OnReplyFinished.AddDynamic(this, &UDialogTask_Reply::OnReplyClicked);

		

	}

	return EBTNodeResult::InProgress;
}

FString UDialogTask_Reply::GetStaticDescription() const
{

	return FString::Printf(
		TEXT("ReplyIndexOut: %s%sDialogueWidget: %s"), 
		*ReplyIndexOutKey.SelectedKeyName.ToString(),
		LINE_TERMINATOR, 
		* DialogueWidgetKey.SelectedKeyName.ToString()
		//*FString::SanitizeFloat(MyFloatValue)
	);


}




void UDialogTask_Reply::OnReplyClicked(int32 ReplyIndex)
{
	UBlackboardData* BBasset = GetBlackboardAsset();

	if (BlackboardComp)
	{

		UE_LOG(LogTemp, Warning, TEXT("1/1 - BBtask On Reply clicked: Reply index value now: %d"), ReplyIndex);
		BlackboardComp->SetValueAsInt(ReplyIndexOutKey.SelectedKeyName, ReplyIndex);

		UE_LOG(LogTemp, Warning, TEXT("2/2 - BBtask On Reply clicked: Reply index value now: %d"), ReplyIndex);

		if (DialogWidget)
		{
			DialogWidget->UnBindFromOnReplyFinished();
		}
	}

	FinishLatentTask(*OwnerComponent, EBTNodeResult::Succeeded);

}
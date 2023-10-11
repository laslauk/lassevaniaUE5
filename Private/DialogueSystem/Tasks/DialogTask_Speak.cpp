// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueSystem/Tasks/DialogTask_Speak.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "DialogueSystem/DialogueWidget.h"
#include "DialogueSystem/DialogueSystemComponent.h"
#include "LassevaniaCommonTypes.h"
#include "Sound/SoundBase.h"
#include "DialogueSystem/DialogueAIController.h"
#include "Interfaces/DialogSystemInterface.h"

#include "BehaviorTree/BlackboardComponent.h"
//#include "UObject/Class.h" //ImplementsInterface
	// All about BTasks inc ++ https://www.thegames.dev/?p=70



FString UDialogTask_Speak::GetStaticDescription() const
{
	return FString::Printf(
		TEXT("SpeakerDTRowName: %s%s DialogText: %s"),
		*SpeakerDTRowName.ToString(),
		LINE_TERMINATOR,
		*DialogText.ToString()
		//*FString::SanitizeFloat(MyFloatValue)
	);
}

UDialogTask_Speak::UDialogTask_Speak(const FObjectInitializer& object_initializer)
 {
	
	UE_LOG(LogTemp, Warning, TEXT("Speak constructor"));
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UDialogTask_Speak::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//OwnerComp->Owner
	UE_LOG(LogTemp, Warning, TEXT("Speak ExecuteTask Started"));
	if (OwnerComponent)
	{

		UE_LOG(LogTemp, Warning, TEXT("OwnerComp IS Already set!"));
	}

	if (!OwnerComponent)
	{

		UE_LOG(LogTemp, Warning, TEXT("OwnerComp nullptr - ok set!"));
	}


	UBlackboardData* BBasset = GetBlackboardAsset();
	OwnerComponent = &OwnerComp;
	//DialogueWidgetKey.
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	UDialogueWidget* DialogWidget = Cast<UDialogueWidget>(BlackboardComp->GetValueAsObject(DialogueWidgetKey.SelectedKeyName));

	AAIController* AIController = OwnerComp.GetAIOwner();
	
	IDialogSystemInterface* Interface = Cast<IDialogSystemInterface>(AIController);

	if (Interface)
	{
		UE_LOG(LogTemp, Warning, TEXT("Interface ok"));
		 DSC = Interface->GetDialogSystemComponent();

		if (DSC)
		{
			UE_LOG(LogTemp, Warning, TEXT("DSC ok"));
			FDialogSpeakerData SpeakerDataStr;
			if (DSC->GetDialogRow(SpeakerDTRowName, SpeakerDataStr))
			{
				
				UE_LOG(LogTemp, Warning, TEXT("GetDialogRow ok"));
				if (DialogWidget)
				{
					UE_LOG(LogTemp, Warning, TEXT("Subbed to on speak fiished"));
					DialogWidget->Speak(DialogText, SpeakerDataStr, SpeakerSide);
					DialogWidget->OnSpeakFinished.AddDynamic(this, &UDialogTask_Speak::OnSpeakFinished);

				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("DialogWidget is null"));

				}

			
				if (VoiceLineToPlay)
				{
					DSC->PlayVoiceLine(VoiceLineToPlay);
				}
			}
		}

	}

	/*
	* 
	* NOTE: LABOROUS WAY TO CHECK INTERFACE: dont use!
	bool bIsImplemented = AIController->GetClass()->ImplementsInterface(UDialogSystemInterface::StaticClass());

	if (bIsImplemented)
	{
		IDialogSystemInterface* Interface = Cast<IDialogSystemInterface>(OutHit.GetActor());
		AIController->GetDialogSy

	}
	*/

	return EBTNodeResult::InProgress;
}

void UDialogTask_Speak::OnSpeakFinished()
{

	UE_LOG(LogTemp, Warning, TEXT("ON SPEAK FINISHED"));

	if (DSC)
	{
		DSC->StopVoiceLine();
	}


	FinishLatentTask(*OwnerComponent, EBTNodeResult::Succeeded);

}

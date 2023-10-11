// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueSystem/DialogueSystemComponent.h"
#include "DialogueSystem/DialogueAIController.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Engine/DataTable.h"
#include "Sound/SoundBase.h"
#include "GameFramework/PlayerController.h"
#include "Templates/SharedPointer.h"
#include "DialogueSystem/DialogueWidget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/AudioComponent.h"
#include "BehaviorTree/BlackboardData.h"


#define WBP_DialogueWidgetPath "/Game/_Main/DialogueSystem/UI/WBP_DialogWidget.WBP_DialogWidget"


// Sets default values for this component's properties
UDialogueSystemComponent::UDialogueSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	/// Script / UMGEditor.WidgetBlueprint'/Game/_Main/DialogueSystem/UI/WBP_DialogWidget.WBP_DialogWidget'

	/*
	ConstructorHelpers::FClassFinder<UUserWidget> WidgetDialogueClassBP(TEXT(WBP_DialogueWidgetPath));
	if (WidgetDialogueClassBP.Class)
	{
		DialogWidgetClass = WidgetDialogueClassBP.Class;
	}

	*/

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	
}


// Called when the game starts
void UDialogueSystemComponent::BeginPlay()
{
	Super::BeginPlay();
	

	/* Spawn AIC and set it's owner the owner of this component */
	UWorld* World = GetWorld();
	
	if (DialogAIControllerClass)
	{
		DialogAIController = World->SpawnActor<ADialogueAIController>(DialogAIControllerClass);
		DialogAIController->SetOwner(GetOwner());
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("DIALOGUE Component Controller not set for: %s "), *GetName());



	}

	
	// ...
	
}



bool UDialogueSystemComponent::GetDialogRow(FName RowName, FDialogSpeakerData& Data)
{

	/* Make sure that Data table is set */
	if (!DialogSpeakersDataTable) { return false; }

	FDialogSpeakerData* RowData = nullptr;


	RowData = DialogSpeakersDataTable->FindRow<FDialogSpeakerData>(RowName, "");
	
	if (RowData == nullptr)
	{
		return false;
	}
	Data = *RowData;

	return RowData != nullptr ? true : false;

}

void UDialogueSystemComponent::StopVoiceLine()
{
	AudioComponent->Stop();
}

void UDialogueSystemComponent::PlayVoiceLine(USoundBase* SoundToPlay)
{
	AudioComponent->SetSound(SoundToPlay);
	AudioComponent->Play();

	
}

void UDialogueSystemComponent::AddTagFlags(const FGameplayTagContainer& InTagContainer)
{

	DialogueFlagTagContainer.AppendTags(InTagContainer);

}

const FGameplayTagContainer& UDialogueSystemComponent::GetDialogueTags()
{
	return DialogueFlagTagContainer;
}

void UDialogueSystemComponent::SetDialogueInputMode(bool bEnableDialogueInputMode)
{
	if (!DialogPlayerController) { return; }


	/* UI Mouse cursor mode, dont allow movement */
	if (bEnableDialogueInputMode)
	{
		if (DialogWidget)
		{
			DialogWidget->AddToViewport();
		}

		FInputModeUIOnly InputModeData;




	
		DialogPlayerController->bShowMouseCursor = true;
		DialogPlayerController->SetInputMode(InputModeData);


	}

	
	/* Input mode back to player character game only */
	else
	{
		if (DialogWidget)
		{
			DialogWidget->RemoveFromParent();

			FInputModeGameOnly InputModeData;
			DialogPlayerController->bShowMouseCursor = false;
			DialogPlayerController->SetInputMode(InputModeData);
			DialogAIController->GetBrainComponent()->StopLogic("StopDialogue");


		}

	}



}



void UDialogueSystemComponent::OnExitDialogueWidget()
{

	if (DialogPlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("EXITING DIALOGUE"));
		SetDialogueInputMode(false);
	}

}

void UDialogueSystemComponent::RunFlagTagChecks()
{
	/* @TODO ; CHECK BP BPC_DialogueComponent for more*/

}


void UDialogueSystemComponent::RemoveDialogFlags(bool bClearAll, const FGameplayTagContainer* TagsToRemove)
{
	if (bClearAll)
	{
		DialogueFlagTagContainer.Reset();
	}
	else
	{
		TArray<FGameplayTag> TagArray;
		TagsToRemove->GetGameplayTagArray(TagArray);

		for (auto Tag : TagArray)
		{
			DialogueFlagTagContainer.RemoveTag(Tag);
		}
	}
}


bool UDialogueSystemComponent::StartDialogue(APlayerController* DialogStartingController)
{
	if (!DialogStartingController) { return false; }
	DialogPlayerController = DialogStartingController;

	if (!DialogAIController || !DialogueBehaviourTree || !BlackBoardData || !DialogWidgetClass)
	{ 
		UE_LOG(LogTemp, Warning, TEXT("HRRRRRRRRRRRR"));
		return false; 
	}

	DialogWidget = CreateWidget<UDialogueWidget>
	(
		DialogPlayerController, //player controller to be owner
		DialogWidgetClass //class of the widget
	);

	if (DialogWidget)
	{
		SetDialogueInputMode(true);

		DialogWidget->OnExit.AddDynamic(this, &UDialogueSystemComponent::OnExitDialogueWidget);

		/* return false if required members are null */
		

		/* Try run behaviour tree, return false if fail*/
		if (DialogAIController->RunBehaviorTree(DialogueBehaviourTree))
		{

		}

		DialogAIController->UseBlackboard(BlackBoardData, BlackboardComponent);

		if (BlackboardComponent)
		{
			BlackboardComponent->SetValueAsObject(DialogueWidgetKeyName, DialogWidget);
		}

		DialogAIController->SetDialogueSystemComponent(this);

		RunFlagTagChecks();

		return true;
	}





	return false;
}


void UDialogueSystemComponent::OnSpeakDialogFinished()
{
	UE_LOG(LogTemp, Warning, TEXT("OnSpeakDialogFinished"));
}

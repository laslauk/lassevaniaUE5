// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h" //cannot be forward declared
#include "Blueprint/UserWidget.h"
#include "LassevaniaCommonTypes.h"
#include "DialogueSystemComponent.generated.h"



class ADialogueAIController;
class UBehaviorTree;
class UBlackboardData;
class UBlackboardComponent;
class UDialogueWidget;
class UDataTable;
class USoundCue;
class UAudioComponent;

/*
*	DIALOGUE COMPONENT SINGLE PLAYER / OFFLINE ONLY 
* 
	Unreal's AI Behaviour tree based dialogue system.
	BT Pros:
	+ Ready made tree structure
	+ Tree traversal and state management with blueprint editor


	BT Cons:
	- Not designed for dialogues
	- Complex and difficult to manage flags

	USAGE:

	Add this component to Actor. 
	Component spawns AI Controller for each dialogue system component. AIC is required for the Behaviour Tree to play
	Dialogue's implementation is done in Behaviour Tree. BT Manages flags, checks and a global state of the dialogue via tags and choice indexes.
*/


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LASSEVANIA_API UDialogueSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties

	UDialogueSystemComponent();


	void PlayVoiceLine(USoundBase* SoundToPlay);
	void StopVoiceLine();


	// Called when the game starts
	virtual void BeginPlay() override;

	



	UFUNCTION()
	void AddTagFlags(const FGameplayTagContainer& InTagContainer);

	UFUNCTION()
	void OnExitDialogueWidget();

	void RunFlagTagChecks();

	void RemoveDialogFlags(bool bClearAll, const FGameplayTagContainer* TagsToRemove);

	/* Requires that StartDialogue has been called and Dialog Player Controller valid*/
	void SetDialogueInputMode(bool bEnableDialogueInputMode);

public:	
	// Called every frame
//	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UPROPERTY(EditAnywhere, Category = "DialogueSystemComponent | Init")
	TSubclassOf<ADialogueAIController> DialogAIControllerClass;

	UPROPERTY(EditAnywhere, Category = "DialogueSystemComponent | Init")
	TSubclassOf<UUserWidget> DialogWidgetClass;

	UPROPERTY(EditAnywhere, Category = "DialogueSystemComponent | Init ")
	UBehaviorTree* DialogueBehaviourTree;

	UPROPERTY(EditAnywhere, Category = "DialogueSystemComponent | Init ")
	UBlackboardData* BlackBoardData;

	UPROPERTY(EditAnywhere, Category = "DialogueSystemComponent | Init ")
	FName DialogueWidgetKeyName = "DialogueWidget";

	UPROPERTY(EditAnywhere, Category = "DialogueSystemComponent | Init ")
	FGameplayTagContainer DialogueFlagTagContainer;
	
	UPROPERTY(EditAnywhere, Category = "DialogueSystemComponent | Init ")	
	UDataTable* DialogSpeakersDataTable;


private:

	UAudioComponent* AudioComponent;

	/* Reference to AIC holding the dialogue behaviour tree */
	ADialogueAIController* DialogAIController;

	/* Ref to dialog widget for choice selection and dialog text*/
	UDialogueWidget* DialogWidget;

	UBlackboardComponent* BlackboardComponent;

	APlayerController* DialogPlayerController = nullptr;

public:
	/* Starts dialogue, returns false if failed to start, sets internal PlayerController*/
	UFUNCTION(BlueprintCallable)
	bool StartDialogue(APlayerController* DialogStartingController);

	UFUNCTION()
	void OnSpeakDialogFinished();


	UFUNCTION(BlueprintCallable)
		bool GetDialogRow(FName RowName, FDialogSpeakerData& Data);


	UFUNCTION(BlueprintCallable)
	const FGameplayTagContainer& GetDialogueTags();
};

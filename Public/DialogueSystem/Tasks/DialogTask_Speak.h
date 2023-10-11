// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "../DialogueWidget.h"
#include "../../LassevaniaCommonTypes.h"
#include "DialogTask_Speak.generated.h"

/**
 * 
 */
UCLASS()
class LASSEVANIA_API UDialogTask_Speak : public UBTTaskNode
{
	GENERATED_BODY()
public:
	virtual FString GetStaticDescription() const override;

	UDialogTask_Speak(const FObjectInitializer & object_initializer);


	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditANywhere, BlueprintReadWrite, Category = "Dialogue", meta = (AllowPrivateAccess = true))
	struct FBlackboardKeySelector DialogueWidgetKey;


	UPROPERTY(EditANywhere, BlueprintReadWrite, Category = "Dialogue", meta = (AllowPrivateAccess = true))
		FText DialogText;


		UDialogueWidget* DialogueWidget;

	UPROPERTY(EditANywhere, BlueprintReadWrite, Category = "Dialogue", meta = (AllowPrivateAccess = true))
		class USoundBase* VoiceLineToPlay;


		FDialogSpeakerData SpeakerData;

	UPROPERTY(EditANywhere, BlueprintReadWrite, Category = "Dialogue", meta = (AllowPrivateAccess = true))
		FName SpeakerDTRowName;


	UPROPERTY(EditANywhere, BlueprintReadWrite, Category = "Dialogue", meta = (AllowPrivateAccess = true))
		EDialogSpeakerSide SpeakerSide;

	UBehaviorTreeComponent* OwnerComponent;

	UDialogueSystemComponent* DSC;

	UFUNCTION()
	void OnSpeakFinished();
			
	//UPROPERTY(EditANywhere, BlueprintReadWrite, Category = "Dialogue", meta = (AllowPrivateAccess = true))
	//FGameplayTagContainer TagsToSet;
};

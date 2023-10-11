// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "../DialogueWidget.h"
#include "LassevaniaCommonTypes.h"
#include "DialogTask_Reply.generated.h"

/**
 * 
 */
UCLASS()
class LASSEVANIA_API UDialogTask_Reply : public UBTTaskNode
{
	GENERATED_BODY()
	
		// All about BTasks inc ++ https://www.thegames.dev/?p=70
public:


	UDialogTask_Reply(FObjectInitializer const& object_initializer);


	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual FString GetStaticDescription() const override;

	UFUNCTION(BlueprintCallable)
	void OnReplyClicked(int32 ReplyIndex);

	/* ++ Public Blackboard Keys ++*/
	UPROPERTY(EditANywhere, BlueprintReadWrite, Category = "Dialogue", meta = (AllowPrivateAccess = true))
	struct FBlackboardKeySelector DialogueWidgetKey;

	UPROPERTY(EditANywhere, BlueprintReadWrite, Category = "Dialogue", meta = (AllowPrivateAccess = true))
	struct FBlackboardKeySelector ReplyIndexOutKey;

	UPROPERTY(EditANywhere, BlueprintReadWrite, Category = "Dialogue", meta = (AllowPrivateAccess = true))
	TArray<FDialogContentData> ReplyTexts;
	/* -- Public Blackboard Keys --*/

	UBlackboardComponent* BlackboardComp;
	UDialogueWidget* DialogWidget;

private:
	TArray<FDialogContentData> FilteredReplyTexts;
	UBehaviorTreeComponent* OwnerComponent;
	UDialogueWidget* DialogueWidget;

};

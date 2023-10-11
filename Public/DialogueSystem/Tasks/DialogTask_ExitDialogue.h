// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DialogTask_ExitDialogue.generated.h"

/**
 * 
 */
UCLASS()
class LASSEVANIA_API UDialogTask_ExitDialogue : public UBTTaskNode
{
	GENERATED_BODY()
public:


	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual FString GetStaticDescription() const override;


	UPROPERTY(EditANywhere, BlueprintReadWrite, Category = "Dialogue", meta = (AllowPrivateAccess = true))
	struct FBlackboardKeySelector DialogueWidgetKey;
	
};

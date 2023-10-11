// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DialogueTask_SetNewRootIndex.generated.h"

/**
 * 
 */
UCLASS()
class LASSEVANIA_API UDialogueTask_SetNewRootIndex : public UBTTaskNode
{
	GENERATED_BODY()


public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


	virtual FString GetStaticDescription() const override;

	/* ++ Public Blackboard Keys ++*/
	UPROPERTY(EditANywhere, BlueprintReadWrite, Category = "Dialogue", meta = (AllowPrivateAccess = true))
		struct FBlackboardKeySelector RootIndexOut;

	UPROPERTY(EditANywhere, BlueprintReadWrite, Category = "Dialogue", meta = (AllowPrivateAccess = true))
		int32 NewIndex;
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GameplayTagContainer.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "DialogTask_SetDialogueFlags.generated.h"

/**
 * 
 */
UCLASS()
class LASSEVANIA_API UDialogTask_SetDialogueFlags : public UBTTaskNode
{
	GENERATED_BODY()

public:
		
	UDialogTask_SetDialogueFlags(FObjectInitializer const& object_initializer);

		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	//	UPROPERTY(EditANywhere, BlueprintReadWrite, Category = "Dialogue", meta = (AllowPrivateAccess = true))
	//	struct FBlackboardKeySelector OwningDialogSystemComponent;

		UPROPERTY(EditANywhere, BlueprintReadWrite, Category = "Dialogue", meta = (AllowPrivateAccess = true))
		FGameplayTagContainer TagsToSet;

	
};

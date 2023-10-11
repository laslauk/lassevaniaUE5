// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "../Interfaces/DialogSystemInterface.h"
#include "DialogueAIController.generated.h"

class UDialogueSystemComponent;

/**
 * 
 */
UCLASS()
class LASSEVANIA_API ADialogueAIController : public AAIController, public IDialogSystemInterface
{
	GENERATED_BODY()
	
public:

	ADialogueAIController();

	FORCEINLINE void SetDialogueSystemComponent(UDialogueSystemComponent* InDialogueSystemComponent)
	{
		DialogueSystemComponent = InDialogueSystemComponent;
	}


	/* Inherited via IDialogSystemInterface */
	UFUNCTION(BlueprintCallable)
	virtual UDialogueSystemComponent* GetDialogSystemComponent() override;

	



protected:
	/* Dialogue System component that this AI controller belongs to, set from the system component*/
	UDialogueSystemComponent* DialogueSystemComponent;


};

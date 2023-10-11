// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DialogReplyListObject.generated.h"

/**
 *  Object for Dialog Widget's ListView for replies. 
 * Holds index and text data. 
 * 
 *  ListView requires Uobject to be added as element. 
 *  Also to have functionality on clicked binding
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClickedDelegate, UDialogReplyListObject*, ClickedDialogReplyObj);


UCLASS(BlueprintType)
class LASSEVANIA_API UDialogReplyListObject : public UObject
{
	GENERATED_BODY()

public:

	FORCEINLINE UDialogReplyListObject(FText Text, int32 Index) : Text(Text), Index(Index)
	{

	}

	UPROPERTY(EditAnywhere)
	FText Text;

	UPROPERTY(EditAnywhere)
	int32 Index;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnClickedDelegate OnClicked;
	
};

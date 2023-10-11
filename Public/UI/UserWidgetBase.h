// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidgetBase.generated.h"



/**
 *  views data got from WidgetController
 */
UCLASS()
class LASSEVANIA_API UUserWidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:


	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;


	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();


};

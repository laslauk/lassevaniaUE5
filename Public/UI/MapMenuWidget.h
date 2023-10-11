// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MapMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class LASSEVANIA_API UMapMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:


	FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent);

	void NativeConstruct();
	

};

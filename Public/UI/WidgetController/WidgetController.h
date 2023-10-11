// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WidgetController.generated.h"




class UAbilitySystemComponent;
class APlayerController;
class APlayerState;
class UAttributeSet;


USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()


		FWidgetControllerParams(){}


		FWidgetControllerParams(
			
			APlayerController* PC,
			APlayerState* PS,
			UAbilitySystemComponent* ASC,
			UAttributeSet* AS) : 
			PlayerController(PC),
			PlayerState(PS),
			AbilitySystemComponent(ASC),
			AttributeSet(AS)
	{
	}


		UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
			TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

		UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
			TObjectPtr<APlayerState> PlayerState = nullptr;

		UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
			TObjectPtr<APlayerController> PlayerController = nullptr;

		UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
			TObjectPtr<UAttributeSet> AttributeSet = nullptr;


};

/**
 *  Responsible for getting data from system/model, character, ASC, etc. This is broadcasted to all set widgets.
 */
UCLASS(BlueprintType, Blueprintable)
class LASSEVANIA_API UWidgetController : public UObject
{
	GENERATED_BODY()

public:

	/* ASC, Attributset, playerState, PlayerController */
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& WCParams);

	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValues();

	virtual void BindCallbacksToDependencies();


protected:

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
		TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
		TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
		TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
		TObjectPtr<UAttributeSet> AttributeSet;

};

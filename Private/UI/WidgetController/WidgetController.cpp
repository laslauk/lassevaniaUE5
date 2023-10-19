// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/WidgetController.h"
#include "AbilitySystemComponent.h"


void UWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerState = WCParams.PlayerState;
	AttributeSet = WCParams.AttributeSet;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	PlayerController= WCParams.PlayerController;


}

void UWidgetController::BroadcastInitialValues()
{
}

void UWidgetController::BindCallbacksToDependencies()
{
}

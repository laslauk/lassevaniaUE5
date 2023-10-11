// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/LassevaniaHUD.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "PlayerControllerBase.h"
#include "PlayerStateBase.h"
#include "AbilitySystemComponent.h"
#include "AttributeSetBase.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "UI/UserWidgetBase.h"


UOverlayWidgetController* ALassevaniaHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject< UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);


		OverlayWidgetController->BindCallbacksToDependencies();


	} 

	return OverlayWidgetController;
}

UAttributeMenuWidgetController* ALassevaniaHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if (AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject< UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(WCParams);


		AttributeMenuWidgetController->BindCallbacksToDependencies();

	
	}

	return AttributeMenuWidgetController;
}

void ALassevaniaHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{

	checkf(OverlayWidgetClass, TEXT("Overlay widget class uninited, please fill out HUd class"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass uninited, please fill out HUd class"));



	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);

	OverlayWidget = Cast<UUserWidgetBase>(Widget);

	const FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);


	/* after this values okay to present*/
	OverlayWidget->SetWidgetController(WidgetController);

	WidgetController->BroadcastInitialValues();


	Widget->AddToViewport();


}


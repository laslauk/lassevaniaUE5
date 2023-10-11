// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LassevaniaHUD.generated.h"


class UUserWidgetBase;
class UOverlayWidgetController;
class UAttributeSet;
struct FWidgetControllerParams;
class UAbilitySystemComponent;
class UAttributeMenuWidgetController;

/**
 *  Sets up Widget Controllers
 */
UCLASS()
class LASSEVANIA_API ALassevaniaHUD : public AHUD
{
	GENERATED_BODY()

public:


	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;


		
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidgetBase> OverlayWidgetClass;



	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

protected:


private:
	

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;

	UPROPERTY()
	TObjectPtr<UUserWidgetBase> OverlayWidget;
	
};

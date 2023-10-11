// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/LassevaniaAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include  "UI/HUD/LassevaniaHUD.h"
#include "UI/WidgetController/WidgetController.h"
#include "PlayerStateBase.h"


UOverlayWidgetController* ULassevaniaAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (ALassevaniaHUD* LassevaniaHUD = Cast<ALassevaniaHUD>(PC->GetHUD()))
		{

			APlayerStateBase* PS = PC->GetPlayerState<APlayerStateBase>();


			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AttributeSet = Cast< UAttributeSet>(PS->GetAttributeSetComponent());

			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AttributeSet);

			return LassevaniaHUD->GetOverlayWidgetController(WidgetControllerParams);

		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* ULassevaniaAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (ALassevaniaHUD* LassevaniaHUD = Cast<ALassevaniaHUD>(PC->GetHUD()))
		{

			APlayerStateBase* PS = PC->GetPlayerState<APlayerStateBase>();


			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AttributeSet = Cast< UAttributeSet>(PS->GetAttributeSetComponent());

			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AttributeSet);

			return LassevaniaHUD->GetAttributeMenuWidgetController(WidgetControllerParams);

		}
	}
	return nullptr;
}

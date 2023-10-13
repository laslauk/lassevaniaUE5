// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/LassevaniaAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include  "UI/HUD/LassevaniaHUD.h"
#include "UI/WidgetController/WidgetController.h"
#include "GameModeLassevania.h"
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

void ULassevaniaAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	

	UCharacterClassInfo* ClassInfo = GetCharacterClassInfo(WorldContextObject);


	AActor* AvatarActor = ASC->GetAvatarActor();

	FCharacterClassDefaultInfo ClassDefaultInfo = ClassInfo->GetClassDefaultInfo(CharacterClass);

	FGameplayEffectContextHandle PrimaryGEHandle = ASC->MakeEffectContext();
	PrimaryGEHandle.AddSourceObject(AvatarActor);

	/* Primary */
	FGameplayEffectSpecHandle PrimaryAttritubteSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, PrimaryGEHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttritubteSpecHandle.Data.Get());

	/*Seconadry*/
	FGameplayEffectContextHandle SeconadryGEHandle = ASC->MakeEffectContext();
	SeconadryGEHandle.AddSourceObject(AvatarActor);

	FGameplayEffectSpecHandle SecondaryAttritubteSpecHandle = ASC->MakeOutgoingSpec(ClassInfo->SecondaryAttributes, Level, SeconadryGEHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttritubteSpecHandle.Data.Get());

	/*vital*/
	FGameplayEffectContextHandle VitalGEHandle = ASC->MakeEffectContext();
	VitalGEHandle.AddSourceObject(AvatarActor);
	FGameplayEffectSpecHandle VitalAttritubteSpecHandle = ASC->MakeOutgoingSpec(ClassInfo->VitalAttributes, Level, VitalGEHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttritubteSpecHandle.Data.Get());


}

UCharacterClassInfo* ULassevaniaAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	AGameModeLassevania* LassevaniaGM = Cast< AGameModeLassevania>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (LassevaniaGM == nullptr) return nullptr;

	return LassevaniaGM->CharacterClassInfo;

}

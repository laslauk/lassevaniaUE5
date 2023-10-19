// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/LassevaniaAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Character/EnemyCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "CharacterZDBase.h"
#include  "UI/HUD/LassevaniaHUD.h"
#include "LassevaniaAbilityTypes.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "UI/WidgetController/WidgetController.h"
#include "GameModeLassevania.h"
#include "LassevaniaCommonTypes.h"
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

void ULassevaniaAbilitySystemLibrary::GetTargetsWithinBoxCollision(const UObject* WorldContextObject, TArray<AActor*>& OutOverllappingActors, AActor* OwnerActor,  FVector InBoxExtend, const FVector& StartOrigin, ECollisionChannel TraceChannel)
{


	FCollisionQueryParams TraceParams(
		SCENE_QUERY_STAT(WeaponTrace),
		/*bTraceComplex=*/ true,
		/*IgnoreActor=*/ OwnerActor);
	TraceParams.bReturnPhysicalMaterial = true;

	FVector BoxExtend = InBoxExtend;

	TArray<FHitResult> HitResults;
	FVector Start = StartOrigin;
	FVector End = Start;
	//ECollisionChannel TraceChannel = Lassevania_TraceChannel_HitBoxTrace;
	FCollisionShape Box = FCollisionShape::MakeBox(BoxExtend);
	FCollisionQueryParams QueryParams;

	const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (World)
	{
		WorldContextObject->GetWorld()->SweepMultiByChannel(
			HitResults,
			Start,
			End,
			FQuat::Identity,
			TraceChannel,
			Box,
			TraceParams
		);
	}

	for (auto hitResult : HitResults)
	{
		AActor* Actor = hitResult.GetActor();
		if (Actor)
		{
			OutOverllappingActors.AddUnique(Actor);
		}
	
	}



}

FGameplayEffectSpecHandle ULassevaniaAbilitySystemLibrary::CreateDamageEffectSpec(const FGameplayEffectContextHandle& EffectContextHandle,
	AActor* OwnerActor, TSubclassOf<UGameplayEffect> DamageEffectClass, TMap<FGameplayTag, FScalableFloat> DamageTypes)
{
	if (!IsValid(DamageEffectClass))  return FGameplayEffectSpecHandle();

	if (ACharacterZDBase* ASCOwner = Cast<ACharacterZDBase>(OwnerActor))
	{
		if (UAbilitySystemComponent* ASC = ASCOwner->GetAbilitySystemComponent())
		{

			
			FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
			FGameplayEffectSpecHandle DamageSpecHandle = ASC->MakeOutgoingSpec(DamageEffectClass, 1.0f, EffectContext);
			

			ULassevaniaAbilitySystemLibrary::SetIsParryableAbility(
				EffectContext, true);


			ULassevaniaAbilitySystemLibrary::SetDamageCasuesHitStun(
				EffectContext, true);

			for (TTuple<FGameplayTag, FScalableFloat> Pair : DamageTypes)
			{
				float ScaledDamage = Pair.Value.GetValueAtLevel(1);
				UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageSpecHandle, Pair.Key, ScaledDamage);


			}

			return DamageSpecHandle;
		}

	}
	FGameplayEffectSpecHandle DamageSpecHandle;
	return DamageSpecHandle;

	/*
	if (!IsValid(DamageEffectClass))  return;



	for (TTuple<FGameplayTag, FScalableFloat> Pair : DamageTypes)
	{
		float ScaledDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageSpecHandle, Pair.Key, ScaledDamage);

		/* Set Properties of Gameplay Effect - Damage , handled in ExecCalc Damage cpp*/
	//	FGameplayEffectContextHandle EffectContext = DamageSpecHandle.Data->GetContext();

	//	ULassevaniaAbilitySystemLibrary::SetIsParryableAbility(
	//		EffectContext, bIsParryable
	//	);

	//	ULassevaniaAbilitySystemLibrary::SetDamageCasuesHitStun(
	//		EffectContext, bDamageCausesHitStun
	//	);


		/* Apply to target */
	//	GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*DamageSpecHandle.Data.Get(),
	//		UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor)
	//	);
	//}



}

bool ULassevaniaAbilitySystemLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	const FLassevaniaGameplayEffectContext* LassevaniaEffectContext = static_cast<const FLassevaniaGameplayEffectContext*>(EffectContextHandle.Get());

	if (LassevaniaEffectContext)
	{
		return LassevaniaEffectContext->IsBlockedHit();

	}
	return false;



}

bool ULassevaniaAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	const FLassevaniaGameplayEffectContext* LassevaniaEffectContext = static_cast<const FLassevaniaGameplayEffectContext*>(EffectContextHandle.Get());

	if (LassevaniaEffectContext)
	{
		return LassevaniaEffectContext->IsCriticalHit();

	}
	return false;

}

void ULassevaniaAbilitySystemLibrary::SetDamageCasuesHitStun(FGameplayEffectContextHandle& EffectContextHandle, bool bCausesHitStun)
{
	FLassevaniaGameplayEffectContext* LassevaniaEffectContext = static_cast<FLassevaniaGameplayEffectContext*>(EffectContextHandle.Get());

	if (LassevaniaEffectContext)
	{
		LassevaniaEffectContext->SetDamageCausesHitStun(bCausesHitStun);
	}
}

bool ULassevaniaAbilitySystemLibrary::IsDamageCausesHitStun(const FGameplayEffectContextHandle& EffectContextHandle)
{
	 const FLassevaniaGameplayEffectContext* LassevaniaEffectContext = static_cast< const FLassevaniaGameplayEffectContext*>(EffectContextHandle.Get());

	if (LassevaniaEffectContext)
	{
		return LassevaniaEffectContext->IsDamageCausesHitStun();

	}
	return false;
}

void ULassevaniaAbilitySystemLibrary::SetIsBlockedHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit)
{

	FLassevaniaGameplayEffectContext* LassevaniaEffectContext = static_cast<FLassevaniaGameplayEffectContext*>(EffectContextHandle.Get());

	if (LassevaniaEffectContext)
	{
		LassevaniaEffectContext->SetIsBlockingHit(bInIsBlockedHit);
	}


}

void ULassevaniaAbilitySystemLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit)
{
	
	FLassevaniaGameplayEffectContext* LassevaniaEffectContext = static_cast<FLassevaniaGameplayEffectContext*>(EffectContextHandle.Get());

	if (LassevaniaEffectContext)
	{
		UE_LOG(LogTemp, Warning, TEXT("SetIsCriticalHit"));
		LassevaniaEffectContext->SetIsCriticalHit(bInIsCriticalHit);
	}
}


void ULassevaniaAbilitySystemLibrary::SetIsParryableAbility(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit)
{

	FLassevaniaGameplayEffectContext* LassevaniaEffectContext = static_cast<FLassevaniaGameplayEffectContext*>(EffectContextHandle.Get());

	if (LassevaniaEffectContext)
	{
		UE_LOG(LogTemp, Warning, TEXT("SetIsCriticalHit"));
		LassevaniaEffectContext->SetIsParryableAbility(bInIsCriticalHit);
	}
}



bool ULassevaniaAbilitySystemLibrary::IsParryable(const FGameplayEffectContextHandle& EffectContextHandle)
{
	const FLassevaniaGameplayEffectContext* LassevaniaEffectContext = static_cast<const FLassevaniaGameplayEffectContext*>(EffectContextHandle.Get());

	if (LassevaniaEffectContext)
	{
		return LassevaniaEffectContext->IsParryableAbility();

	}
	return false;
}

bool ULassevaniaAbilitySystemLibrary::IsTargetHostile(AActor* Actor, AActor* OtherActor)
{

	const bool bBothPlayers = Actor->ActorHasTag(FName("Player")) && OtherActor->ActorHasTag(FName("Player"));;
	const bool bBothEnemies = Actor->ActorHasTag(FName("Enemy"))  && OtherActor->ActorHasTag(FName("Enemy"));;
	const bool bBothSameTeam = bBothPlayers || bBothEnemies;

	return !bBothSameTeam;
}

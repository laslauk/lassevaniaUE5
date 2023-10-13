// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Tasks/MeleeAttackTraceForTargetData.h"
#include "LassevaniaCommonTypes.h"
#include "AbilitySystemComponent.h"


UMeleeAttackTraceForTargetData::UMeleeAttackTraceForTargetData(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{

	bTickingTask = true;
}

UMeleeAttackTraceForTargetData* UMeleeAttackTraceForTargetData::CreateMeleeAttackTraceForTargetData(UGameplayAbility* OwningAbility, FGameplayTag StartEventTag, FGameplayTag EndEventTag, bool bDrawDebug)
{
	

	UMeleeAttackTraceForTargetData* MyObj = NewAbilityTask< UMeleeAttackTraceForTargetData >(OwningAbility);
	MyObj->StartTag = StartEventTag;
	MyObj->EndTag = EndEventTag;
	MyObj->bDrawDebug = bDrawDebug;
	return MyObj;


}

void UMeleeAttackTraceForTargetData::GameplayEventCallback(const FGameplayEventData* Payload)
{
	UE_LOG(LogTemp, Warning, TEXT("A --- Ending task"));


	EndTask();
}

void UMeleeAttackTraceForTargetData::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	if (bOldDoTrace && bDoTrace == false)
	{
		EndTask();
	}

	if (bDoTrace)
	{

		UAbilitySystemComponent* ASC = AbilitySystemComponent.Get();

		if (ASC)
		{
			AActor* AvatarActor = GetAvatarActor();

			//	MyHandle = ASC->GenericGameplayEventCallbacks.FindOrAdd(Tag).
				//	AddUObject(this, &UAbilityTask_WaitGameplayEvent::GameplayEventCallback);

	

			FCollisionQueryParams TraceParams(
				SCENE_QUERY_STAT(WeaponTrace),
				/*bTraceComplex=*/ true,
				/*IgnoreActor=*/ AvatarActor);
			TraceParams.bReturnPhysicalMaterial = true;

			FVector BoxExtend({ 90.f,80.f,70.f });

			TArray<FHitResult> HitResults;
			FVector Start = AvatarActor->GetActorLocation() + 
				(AvatarActor->GetActorForwardVector() * FVector(100.f,0.f,0.f));
			FVector End = Start;
			ECollisionChannel TraceChannel = Lassevania_TraceChannel_HitBoxTrace;
			FCollisionShape Box = FCollisionShape::MakeBox(BoxExtend);
			FCollisionQueryParams QueryParams;


			GetWorld()->SweepMultiByChannel(
				HitResults,
				Start,
				End,
				FQuat::Identity,
				TraceChannel,
				Box,
				TraceParams
			);

			if (bDrawDebug)
			{
				DrawDebugBox(GetWorld(), Start, BoxExtend, FColor::Cyan, false, 5);
			}

		
			NewHitActors.Empty();

			for (auto hit : HitResults)
			{
				if (!AllHitActors.Contains(hit.GetActor()))
				{
					NewHitActors.AddUnique(hit.GetActor());
				}

				AllHitActors.AddUnique(hit.GetActor());

			}

			AttackEnded.Broadcast(NewHitActors);
		}
		
	}

	bOldDoTrace = bDoTrace;
	
}



void UMeleeAttackTraceForTargetData::Activate()
{

	UAbilitySystemComponent* ASC = AbilitySystemComponent.Get();

	if (ASC)
	{
		AActor* Actor = GetAvatarActor();

		MyHandle = ASC->GenericGameplayEventCallbacks.FindOrAdd(StartTag).AddLambda(
			[this](const FGameplayEventData* Payload)
			{
				bDoTrace = true;
			}
		);

		ASC->GenericGameplayEventCallbacks.FindOrAdd(EndTag).AddLambda(
			[this](const FGameplayEventData* Payload)
			{
				bDoTrace = false;
			}
		);
	}
}

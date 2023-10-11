// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Tasks/MeleeAttackTraceForTargetData.h"
#include "LassevaniaCommonTypes.h"
#include "AbilitySystemComponent.h"


UMeleeAttackTraceForTargetData::UMeleeAttackTraceForTargetData(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{

	bTickingTask = true;
}

UMeleeAttackTraceForTargetData* UMeleeAttackTraceForTargetData::CreateMeleeAttackTraceForTargetData(UGameplayAbility* OwningAbility, FGameplayTag StartEventTag, FGameplayTag EndEventTag)
{
	

	UMeleeAttackTraceForTargetData* MyObj = NewAbilityTask< UMeleeAttackTraceForTargetData >(OwningAbility);
	MyObj->StartTag = StartEventTag;
	MyObj->EndTag = EndEventTag;
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

			UE_LOG(LogTemp, Warning, TEXT("Actor %s"), *AvatarActor->GetName());

			FCollisionQueryParams TraceParams(
				SCENE_QUERY_STAT(WeaponTrace),
				/*bTraceComplex=*/ true,
				/*IgnoreActor=*/ AvatarActor);
			TraceParams.bReturnPhysicalMaterial = true;


			TArray<FHitResult> HitResults;
			FVector Start = AvatarActor->GetActorLocation();
			FVector End = Start;
			ECollisionChannel TraceChannel = Lassevania_TraceChannel_HitBoxTrace;
			FCollisionShape Box = FCollisionShape::MakeBox(FVector({ 175.f,75.f,75.f }));
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

			DrawDebugBox(GetWorld(), Start, { 175.f,75.f,75.f }, FColor::Cyan, false, 5);

		
			NewHitActors.Empty();


			for (auto hit : HitResults)
			{
			

				if (!AllHitActors.Contains(hit.GetActor()))
				{

					NewHitActors.AddUnique(hit.GetActor());
					UE_LOG(LogTemp, Warning, TEXT("AllHitActors does not contains %s"), *hit.GetActor()->GetName());
				}

				AllHitActors.AddUnique(hit.GetActor());

			}
			UE_LOG(LogTemp, Warning, TEXT("New HIT ACTOR COUNT %d"), NewHitActors.Num());
			UE_LOG(LogTemp, Warning, TEXT("New HIT ACTOR COUNT %d"), AllHitActors.Num());

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

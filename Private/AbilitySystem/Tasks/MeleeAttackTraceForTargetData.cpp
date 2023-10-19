// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Tasks/MeleeAttackTraceForTargetData.h"
#include "LassevaniaCommonTypes.h"
#include "AbilitySystem/LassevaniaAbilitySystemLibrary.h"
#include "AbilitySystemComponent.h"


UMeleeAttackTraceForTargetData::UMeleeAttackTraceForTargetData(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{

	bTickingTask = true;
}

UMeleeAttackTraceForTargetData* UMeleeAttackTraceForTargetData::CreateMeleeAttackTraceForTargetData(UGameplayAbility* OwningAbility,
	FVector AttackDamageCollisionBoxExtend,
	float InCollisionOffSet,
	FGameplayTag StartEventTag, FGameplayTag EndEventTag, bool bDrawDebug

)
{
	

	UMeleeAttackTraceForTargetData* MyObj = NewAbilityTask< UMeleeAttackTraceForTargetData >(OwningAbility);
	MyObj->StartTag = StartEventTag;
	MyObj->EndTag = EndEventTag;
	MyObj->bDrawDebug = bDrawDebug;
	MyObj->AttackCollisionBox = AttackDamageCollisionBoxExtend;
	MyObj->AttackCollisionOffset = InCollisionOffSet;
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

		TArray<AActor*> HitActors;

		UAbilitySystemComponent* ASC = AbilitySystemComponent.Get();

		if (ASC)
		{
			AActor* AvatarActor = GetAvatarActor();

			FVector Start = AvatarActor->GetActorLocation() +
				(AvatarActor->GetActorForwardVector() * FVector(AttackCollisionOffset, 0.f, 0.f));

			ULassevaniaAbilitySystemLibrary::GetTargetsWithinBoxCollision(
			this, HitActors, AvatarActor, AttackCollisionBox, Start, Lassevania_TraceChannel_HitBoxTrace);

			if (bDrawDebug)
			{
				DrawDebugBox(GetWorld(), Start, AttackCollisionBox, FColor::Cyan, false, 1);
			}

			NewHitActors.Empty();


			for (auto HitActor : HitActors)
			{
				if (!AllHitActors.Contains(HitActor))
				{
					NewHitActors.AddUnique(HitActor);
				}
				AllHitActors.AddUnique(HitActor);
			}
			AttackEnded.Broadcast(NewHitActors);
			/*
			FCollisionQueryParams TraceParams(
				SCENE_QUERY_STAT(WeaponTrace),
				 true,
			 AvatarActor);
			TraceParams.bReturnPhysicalMaterial = true;

			FVector BoxExtend = AttackCollisionBox;
			const float CollisionFrontOffset = AttackCollisionOffset;

			TArray<FHitResult> HitResults;
			
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

			*/
		
			
			/*
		
		
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
			*/
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

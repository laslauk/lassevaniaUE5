// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTSservice/BTService_FindNearbyPlayer.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "Kismet/GameplayStatics.h" //GetAllActorsWith()
#include "AIController.h"







 void UBTService_FindNearbyPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	 /* services on behavior tree and it has owner, actor + component*/
	 Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	 //access to AiController and Actor, owner of the behavior tree actor
	
	 APawn* OwningPawn = AIOwner->GetPawn();


	 /* jos pelaaja niin etsitään enemyä, esim peteille tai summoneille */
	const FName TargetTag = OwningPawn->ActorHasTag(FName("Player")) ? FName("Enemy") : FName("Player");

	TArray<AActor*> ActorsWithTag;
	UGameplayStatics::GetAllActorsWithTag(OwningPawn, TargetTag, ActorsWithTag);

	/* Get Closest */

	float ClosestDistance = TNumericLimits<float>::Max();
	AActor* ClosestActor = nullptr;
	for (AActor* Actor : ActorsWithTag)
	{
		if (IsValid(Actor) && IsValid(OwningPawn))
		{
			const float Distance = OwningPawn->GetDistanceTo(Actor);

			if (Distance < ClosestDistance)
			{
				ClosestActor = Actor;
				ClosestDistance = Distance;
			}
		}
	}


	UBTFunctionLibrary::SetBlackboardValueAsObject
	(
		this, 	//this service is descent of node owner
		TargetToFollowSelector, // The blackboard key selector to set the value
		ClosestActor //value for  the key selector
	);


	UBTFunctionLibrary::SetBlackboardValueAsFloat
	(
		this, 	//this service is descent of node owner
		DistanceToTargetSelector, // The blackboard key selector to set the value
		ClosestDistance //value for  the key selector
	);

}
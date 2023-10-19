// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Tasks/AbilityTask_CheckActorsLinedAxis.h"
#include "GameFramework/CharacterMovementComponent.h"

UAbilityTask_CheckActorsLinedAxis::UAbilityTask_CheckActorsLinedAxis(const FObjectInitializer& ObjectInitializer)
{
	bTickingTask = true;
}

UAbilityTask_CheckActorsLinedAxis* UAbilityTask_CheckActorsLinedAxis::CreateAbilityTask_CheckActorsLinedAxis(UGameplayAbility* OwningAbility, float DoAirStrikeTreshold, EAxis::Type AlignAxis, AActor* Actor, AActor* OtherActor, float Treshold)
{
	UAbilityTask_CheckActorsLinedAxis* MyObj = NewAbilityTask< UAbilityTask_CheckActorsLinedAxis >(OwningAbility);
	MyObj->AxisToCheck = AlignAxis;
	MyObj->Actor = Actor;
	MyObj->Treshold = Treshold;
	MyObj->OtherActor = OtherActor;
	MyObj->fDoAirStrikeTreshold = DoAirStrikeTreshold;
	return MyObj;

}

void UAbilityTask_CheckActorsLinedAxis::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
	bool IsInRange = false;

	if (EAxis::X)
	{
		IsInRange = FMath::IsWithinInclusive(Actor->GetActorLocation().X,
			OtherActor->GetActorLocation().X - Treshold,
			OtherActor->GetActorLocation().X + Treshold);
		
		

	} else if (EAxis::Y)
	{
		IsInRange = FMath::IsWithinInclusive(Actor->GetActorLocation().Y,
			OtherActor->GetActorLocation().Y - Treshold,
			OtherActor->GetActorLocation().Y + Treshold);
		
	}
	else if (EAxis::Z)
	{

		IsInRange = FMath::IsWithinInclusive(Actor->GetActorLocation().Z,
			OtherActor->GetActorLocation().Z - Treshold,
			OtherActor->GetActorLocation().Z + Treshold);

	}

	if (IsInRange)
	{

		ActorsLined.Broadcast();

		float Dist = FVector::Dist(OtherActor->GetActorLocation(), Actor->GetActorLocation());
		/*
		
		float Dist = FMath::Sqrt(FMath::Pow((OtherActor->GetActorLocation().X - Actor->GetActorLocation().X), 2) +
			FMath::Pow((Actor->GetActorLocation().Z - OtherActor->GetActorLocation().Z), 2));
		UE_LOG(LogTemp, Warning, TEXT("Distacne: %f - %f"), Dist, dist2);*/

		if (Dist > fDoAirStrikeTreshold)
		{
			ShouldAttempAirStrike.Broadcast();
			EndTask();


		}

	}



}

void UAbilityTask_CheckActorsLinedAxis::Activate()
{
}

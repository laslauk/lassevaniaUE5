// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyDummyPawn.h"
#include "AbilitySystemComponent.h"


// Sets default values
AEnemyDummyPawn::AEnemyDummyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System Component"));
//	AttributeSetBaseComp = CreateDefaultSubobject<UAttributeSetBase>(TEXT("AttributeSetBaseComponent"));
}

// Called when the game starts or when spawned
void AEnemyDummyPawn::BeginPlay()
{
	Super::BeginPlay();

	/*
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();

	FGameplayEffectContextHandle PrimaryGEHandle = ASC->MakeEffectContext();
	PrimaryGEHandle.AddSourceObject(this);

	FGameplayEffectSpecHandle PrimaryAttritubteSpecHandle = ASC->MakeOutgoingSpec(DefaultPrimaryAttributes, 1.0, PrimaryGEHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttritubteSpecHandle.Data.Get());

	FGameplayEffectContextHandle Second = ASC->MakeEffectContext();
	Second.AddSourceObject(this);

	FGameplayEffectSpecHandle secge = ASC->MakeOutgoingSpec(DefaultSecondaryAttributes, 1.0, Second);
	ASC->ApplyGameplayEffectSpecToSelf(*secge.Data.Get());


	FGameplayEffectContextHandle Vital = ASC->MakeEffectContext();
	PrimaryGEHandle.AddSourceObject(this);

	FGameplayEffectSpecHandle vt = ASC->MakeOutgoingSpec(DefaultVitalAttributes, 1.0, Vital);
	ASC->ApplyGameplayEffectSpecToSelf(*vt.Data.Get());


	*/

}

// Called every frame
void AEnemyDummyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyDummyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}




UAbilitySystemComponent* AEnemyDummyPawn::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
 }
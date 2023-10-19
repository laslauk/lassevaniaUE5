// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AbilitySystemInterface.h"
#include "EnemyDummyPawn.generated.h"

class UAbilitySystemComponent;
class UAttributeSetBase;

UCLASS()
class LASSEVANIA_API AEnemyDummyPawn : public APawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyDummyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	/*
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes") //metas not replicated
		TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes") //metas not replicated
		TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes") //metas not replicated
		TSubclassOf<UGameplayEffect> DefaultVitalAttributes;
	*/

	UPROPERTY(VisibleAnywhere, Category = "Lassevania|Ability System")
	TObjectPtr<class UAbilitySystemComponent> AbilitySystemComponent;

	//UPROPERTY(VisibleAnywhere, Category = "CharacterBase")
	//UAttributeSetBase* AttributeSetBaseComp;
};

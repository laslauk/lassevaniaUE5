// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"

#include "Abilities/GameplayAbility.h"
#include "AbilitySystemInterface.h"
#include "LassevaniaCommonTypes.h"
#include "Interfaces/CombatInterface.h"
#include "CharacterZDBase.generated.h"


class UAttributeSetBase;
class APlayerStateBase; /* Abiltiy System Component, Sek‰ inventoryComponent on t‰‰ll‰*/
class APlayerControllerBase;
class UCharacterDataAsset;
class UAbilitySystemComponent;


/**
 * 
 */
UCLASS()
class LASSEVANIA_API ACharacterZDBase : public APaperZDCharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()
	

public:


	ACharacterZDBase();

	void GiveAbilities();

	UPROPERTY(EditDefaultsOnly/*ReplicatedUsing = OnRep_PawnData*/)
	TObjectPtr<const UCharacterDataAsset> CharacterDataAsset;

	virtual void PossessedBy(AController* NewController) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const ;

	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
	void AquireAbility(TSubclassOf<UGameplayAbilityBase> AbilityToAquire);

	class UInventoryComponent* GetInventoryComponent();

	/* SETTERS AND GETTERS*/

	UFUNCTION(BlueprintCallable)
	virtual UAttributeSetBase* GetAttributeSetComponent();

	void TryMovement(float ScaleValue);

	UFUNCTION(BlueprintCallable)
	const UCharacterDataAsset*  GetCharacterData() const;

	UFUNCTION(BlueprintCallable)
	void SetCharacterData(const UCharacterDataAsset* InCharacterData);

	virtual void ApplyStartupEffects();

	bool ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> gameplayEffect, FGameplayEffectContextHandle IneffectContext);
	
	UFUNCTION(BlueprintCallable)
		void SetCanMove(bool NewCanMove) { bCanMove = NewCanMove;  }

	/* Combat interface */

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> Effect, float level);



	virtual void Die() override;
	/* Combat interface end*/

	virtual void InitializeDefaultAttributes();


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes") //metas not replicated
		TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;


	/* These depend on Primary attributes - applied with infinite GE*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes") //metas not replicated
		TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	/* These depend on Primary attributes - applied with infinite GE*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes") //metas not replicated
		TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

private:



	bool bCanMove = true;




};



// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayEffectTypes.h"
#include "GameplayTagContainer.h" /*FGameplayTag*/
#include "GameplayAbilitySpec.h"
#include "LassevaniaAbilitySet.generated.h"

class UAttributeSet;
class UGameplayEffect;
class ULVAbilitySystemComponent;
class UGameplayAbilityBase;
class UObject;

USTRUCT(BlueprintType)
struct FLassevaniaAbilitySet_GameplayAbility
{
	GENERATED_BODY()

public:

	/* Gameplay ability to grant. */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayAbilityBase> Ability = nullptr;

	// Level of ability to grant.
	UPROPERTY(EditDefaultsOnly)
	int32 AbilityLevel = 1;

	// Tag used to process input for the ability.
	UPROPERTY(EditDefaultsOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
};

/**
 * FLassevaniaAbilitySet_GameplayEffect
 *
 *	Data used by the ability set to grant gameplay effects.
 */
USTRUCT(BlueprintType)
struct FLassevaniaAbilitySet_GameplayEffect
{
	GENERATED_BODY()

public:

	// Gameplay effect to grant.
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UGameplayEffect> GameplayEffect = nullptr;

	// Level of gameplay effect to grant.
	UPROPERTY(EditDefaultsOnly)
		float EffectLevel = 1.0f;
};


/**
 * FLassevaniaAbilitySet_AttributeSet
 *
 *	Data used by the ability set to grant attribute sets.
 */
USTRUCT(BlueprintType)
struct FLassevaniaAbilitySet_AttributeSet
{
	GENERATED_BODY()

public:
	// Gameplay effect to grant.
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UAttributeSet> AttributeSet;

};



/**
 * FLyraAbilitySet_GrantedHandles
 *
 *	Data used to store handles to what has been granted by the ability set.
 */

USTRUCT(BlueprintType)
struct FLassevaniaAbilitySet_GrantedHandles
{
	GENERATED_BODY()

public:

	void AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle);
	void AddGameplayEffectHandle(const FActiveGameplayEffectHandle& Handle);
	void AddAttributeSet(UAttributeSet* Set);


	void TakeFromAbilitySystem(ULVAbilitySystemComponent* LVASC);

protected:



	// Handles to the granted abilities.
	UPROPERTY()
		TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

	// Handles to the granted gameplay effects.
	UPROPERTY()
		TArray<FActiveGameplayEffectHandle> GameplayEffectHandles;

	// Pointers to the granted attribute sets
	UPROPERTY()
		TArray<TObjectPtr<UAttributeSet>> GrantedAttributeSets;

};


/**
 * 
 */
UCLASS()
class LASSEVANIA_API ULassevaniaAbilitySet : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	ULassevaniaAbilitySet(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// Grants the ability set to the specified ability system component.
// The returned handles can be used later to take away anything that was granted.
	void GiveToAbilitySystem(ULVAbilitySystemComponent* LVASC, FLassevaniaAbilitySet_GrantedHandles* OutGrantedHandles, UObject* SourceObject = nullptr) const;


protected:

	// Gameplay abilities to grant when this ability set is granted.
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities", meta = (TitleProperty = Ability))
	TArray<FLassevaniaAbilitySet_GameplayAbility> GrantedGameplayAbilities;

	// Gameplay effects to grant when this ability set is granted.
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects", meta = (TitleProperty = GameplayEffect))
	TArray<FLassevaniaAbilitySet_GameplayEffect> GrantedGameplayEffects;

	UPROPERTY(EditDefaultsOnly, Category = "Attribute Sets", meta = (TitleProperty = AttributeSet))
	TArray<FLassevaniaAbilitySet_AttributeSet> GrantedAttributes;

};

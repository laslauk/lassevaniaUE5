// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "Containers/Array.h"
#include "Containers/Map.h"
#include "GameplayAbilitySpec.h"
#include "GameplayEffectTypes.h"
#include "GameplayTagContainer.h"
#include "Templates/SubclassOf.h"
#include "UObject/ObjectPtr.h"
#include "UObject/UObjectGlobals.h"
#include "GameplayAbilityBase.generated.h"

/* https://www.reddit.com/r/unrealengine/comments/12awr7p/i_swear_its_worth_learning_if_your_mental_health/
*/

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityEnded);

UENUM(BlueprintType)
enum class EAbilityActivationPolicy : uint8
{
	// Try to activate the ability when the input is triggered.
	OnInputTriggered,

	// Continually try to activate the ability while the input is active.
	WhileInputActive,

	// Try to activate the ability when an avatar is assigned.
	OnSpawn
};



/**
 * 
 */
UCLASS(Abstract, HideCategories = Input, Meta = (ShortTooltip = "The base gameplay ability class used by this project."))
class LASSEVANIA_API UGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()
public:


	UGameplayAbilityBase(const FObjectInitializer& ObjectInitializer);

	// Tag used to process input for the ability.
	UPROPERTY(EditDefaultsOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	/** Actually activate ability, do not call this directly */
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);

	/** Native function, called if an ability ends normally or abnormally. If bReplicate is set to true, try to replicate the ending to the client/server */
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);


	UFUNCTION(BlueprintCallable, Category = "Crawl|Ability")
	AController* GetControllerFromActorInfo() const;


	class ACharacterZDBase* GetLVCharacterFromActorInfo();

	void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec);


	//Applying effects on start, ability wont manage their lifeitme
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
		TArray<TSubclassOf<UGameplayEffect>> OngoingEffectsToRemoveOnEnd;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TArray<TSubclassOf<UGameplayEffect>> OngoingEffectsToJustApplyOnStart;

	TArray<FActiveGameplayEffectHandle> RemoveOnEndEffectHandles;


	UPROPERTY(EditDefaultsOnly, Category = "Effects")
		bool bActivateAbilityOnGranted = false;

	EAbilityActivationPolicy GetActivationPolicy() const { return ActivationPolicy; }


	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnAbilityEnded OnAbilityEndedDeligate;

	/** Called when this ability is granted to the ability system component. */
	UFUNCTION(BlueprintImplementableEvent, Category = Ability, DisplayName = "OnAbilityAdded")
		void K2_OnAbilityAdded();

	/** Called when this ability is removed from the ability system component. */
	UFUNCTION(BlueprintImplementableEvent, Category = Ability, DisplayName = "OnAbilityRemoved")
		void K2_OnAbilityRemoved();



	/** Called when the ability is removed from an AbilitySystemComponent */
	virtual void OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;



protected:
	// Defines how this ability is meant to activate.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lyra|Ability Activation")
	EAbilityActivationPolicy ActivationPolicy;


};

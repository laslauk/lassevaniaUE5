// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CharacterZDBase.h"
#include "../UI/WidgetController/OverlayWidgetController.h"


#include "EnemyCharacterBase.generated.h"




class UWidgetComponent;
class UAttributeSetBase;
class UGameplayAbility;
class UBehaviorTree;
class ALassevaniaAIController;


/**
 * 
 */
UCLASS()
class LASSEVANIA_API AEnemyCharacterBase : public ACharacterZDBase
{
	GENERATED_BODY()


public:

	AEnemyCharacterBase();

	/* ABILITIES GIVEN WITH LASSEVANI_ABILITYSET data asset set to the character*/
	virtual void GiveAbilities() override;

	virtual void PossessedBy(AController* NewController) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	//virtual void ApplyStartupEffects() override;

	FORCEINLINE class ULVAbilitySystemComponent* GetLVAbilitySystemComponent() const { return AbilitySystemComponent; }


	virtual void AddMovementInput
	(
		FVector WorldDirection,
		float ScaleValue,
		bool bForce
	) override;


	UFUNCTION(BlueprintCallable)
	 void GotAttacked(const FGameplayTag CallbackTag, int32 NewTagCount) ;


	UFUNCTION(BlueprintCallable)
	virtual void TryMovement(float Scalevalue) override;

	UPROPERTY(VisibleAnywhere, Category = "Lassevania|Ability System")
	TObjectPtr<class ULVAbilitySystemComponent> AbilitySystemComponent;


	 virtual UAttributeSetBase* GetAttributeSetComponent() override;


	 UFUNCTION(BlueprintImplementableEvent, meta =
		 (DisplayName = "OnDeath"))
		void K2_OnDeath();



	 UFUNCTION(BlueprintImplementableEvent, meta =
		 (DisplayName = "OnAttacked"))
		 void K2_OnAttacked();


	 virtual void Die() override;


	 virtual void InitializeDefaultAttributes() override;
	 

	 UFUNCTION(BlueprintCallable)
		  void SetAvatarLevel(int32 NewLevel) { Level = NewLevel; }

	 void BindToGameplayTags();

	 /*Combat interface */
	 virtual int32 GetAvatarLevel() override;
	 /*Combat interface */

	 UPROPERTY(BlueprintAssignable)
	 FOnAttributeChangedSignature OnHealthChanged;

	 UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	 UPROPERTY(BlueprintReadonly, Category = "Combat")
		  bool bHitStunned;
	
	 void HitStunTagChanged(const FGameplayTag CallbackTag, int32 NewTagCount);

	 UFUNCTION(BlueprintImplementableEvent, meta =
		 (DisplayName = "OnHitReact" ))
	 void K2_OnHitStunned();

	 /* nyt t‰m‰ applyttana kun tulee Damage tag, voisi pist‰‰ suoraan damage effektist‰ mutta more control nyt*/
	 UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	 TSubclassOf<UGameplayEffect> HitReactEffectClass;


	 UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		 TObjectPtr<ULassevaniaAbilitySet> EnemyCharacterAbilitySet;

	 UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;


	 UPROPERTY(VisibleAnywhere, Category = "CharacterBase")
	 UAttributeSetBase* AttributeSetBaseComp;

private:



	void SetupAI(AController* NewController);
	void SetupMovementFor2DCharacter();

protected:

	virtual void BeginPlay() override;
	void InitAbilityActorInfo();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "character class defaults")
		int32 Level = 1;




	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	/* all attris*/
	


	UPROPERTY()
	TObjectPtr<ALassevaniaAIController> LassevaniaAIController;

	
};

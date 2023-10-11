// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CharacterZDBase.h"
#include "../UI/WidgetController/OverlayWidgetController.h"
#include "EnemyCharacterBase.generated.h"




class UWidgetComponent;
class UAttributeSetBase;
/**
 * 
 */
UCLASS()
class LASSEVANIA_API AEnemyCharacterBase : public ACharacterZDBase
{
	GENERATED_BODY()


public:

	AEnemyCharacterBase();

	virtual void PossessedBy(AController* NewController) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	//virtual void ApplyStartupEffects() override;

	FORCEINLINE class ULVAbilitySystemComponent* GetLVAbilitySystemComponent() const { return AbilitySystemComponent; }


	UPROPERTY(VisibleAnywhere, Category = "Lassevania|Ability System")
	TObjectPtr<class ULVAbilitySystemComponent> AbilitySystemComponent;


	 virtual UAttributeSetBase* GetAttributeSetComponent() override;

	 

	 UFUNCTION(BlueprintCallable)
		  void SetAvatarLevel(int32 NewLevel) { Level = NewLevel; }

	 virtual int32 GetAvatarLevel() override;

	 UPROPERTY(BlueprintAssignable)
	 FOnAttributeChangedSignature OnHealthChanged;

	 UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;


private:


	UPROPERTY(VisibleAnywhere, Category = "CharacterBase")
		UAttributeSetBase* AttributeSetBaseComp;

protected:

	virtual void BeginPlay() override;
	void InitAbilityActorInfo();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "character class defaults")
		int32 Level = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	/* all attris*/
	

	
};

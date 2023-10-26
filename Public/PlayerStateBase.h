// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"

#include "AbilitySystem/LVAbilitySystemComponent.h"


#include "PlayerStateBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSetBase;
class UInventoryComponent;
class APlayerControllerBase;
class ULevelUpInfo;




DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChanged, int32 /*StatValue*/);

/**
 * 
 */
UCLASS()
class LASSEVANIA_API APlayerStateBase : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	
	
	APlayerStateBase();


	FORCEINLINE  ULVAbilitySystemComponent* GetLVAbilitySystemComponent() const {
			return AbilitySystemComponent; 
	}

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	

	UFUNCTION(BlueprintCallable)
	FORCEINLINE  UInventoryComponent* GetInventoryComponent() { return InventoryComponent; }


	/* TODO DEFAULT ABVILITIES AND ACQUIRING AND GIVING ABILTIIES, DO LIKE IN LYRA FOR STARTERS */
	/* separate different activation methods */

	// The ability system component sub-object used by player characters.
	UPROPERTY(VisibleAnywhere, Category = "Lassevania|PlayerState")
	ULVAbilitySystemComponent* AbilitySystemComponent;

	UFUNCTION(BlueprintCallable)
	 UAttributeSetBase* GetAttributeSetComponent()
	{
		return AttributeSetBaseComp;
	}



	UFUNCTION(BlueprintCallable)
	 void SetPlayerLevel(int32 NewLevel) { Level = NewLevel; }

	UFUNCTION(BlueprintCallable)
	 int32 GetPlayerLevel() { return Level; }

	UFUNCTION(BlueprintCallable)
	int32 GetXP() { return XP; }


	UFUNCTION(BlueprintCallable)
	int32 GetStoredXP() { return StoredXP; }

	FOnPlayerStatChanged OnXPChangedDelegate;
	FOnPlayerStatChanged OnLevelChangedDelegate;


	UFUNCTION(BlueprintCallable)
	void AddToXP(int32 InXP);

	UFUNCTION(BlueprintCallable)
	void AddToLevel(int32 InLevel);

	UFUNCTION(BlueprintCallable)
	void SetLevel(int32 NewLevel);

	UFUNCTION(BlueprintCallable)
	void SetXP(int32 NewXP);


	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ULevelUpInfo> LevelUpInfo;


private:
	UPROPERTY(VisibleAnywhere, Category = "CharacterBase")
	 UAttributeSetBase* AttributeSetBaseComp;

	UInventoryComponent* InventoryComponent;
	APlayerControllerBase* PlayerController;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "character class defaults")
	int32 Level = 1;


	//UAbilitySystemComponent* AbilitySystemComponent;


private:

	UPROPERTY(VisibleAnywhere)
	int32 PlayerLevel;

	UPROPERTY(VisibleAnywhere)
	int32 XP;

	UPROPERTY(VisibleAnywhere)
	int32 StoredXP;

};

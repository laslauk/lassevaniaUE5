 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterZDBase.h"
#include "PlayerCharacterBase.generated.h"

class UEquipmentManagerComponent;
class UInventoryManagerComponent;

/**
 * 
 */
UCLASS()
class LASSEVANIA_API APlayerCharacterBase : public ACharacterZDBase
{
	GENERATED_BODY()
	

public:
	APlayerCharacterBase();

	UFUNCTION(BlueprintCallable)
	APlayerControllerBase* GetPlayerController();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;


	UFUNCTION(BlueprintCallable, BlueprintPure)
	APlayerStateBase* GetPlayerState();
	UFUNCTION(BlueprintCallable)
	void SetPlayerState(APlayerStateBase* PlayerStateIn);


	//virtual void ApplyStartupEffects() override;

	UFUNCTION(BlueprintCallable)
		void SetPlayerController(APlayerControllerBase* PlayerControllerIn);

	UFUNCTION(BlueprintCallable)
		void TryInteract();


	UPROPERTY(EditAnywhere)
		UEquipmentManagerComponent* EquipmentManagerComponent;

	UPROPERTY(EditAnywhere)
		UInventoryManagerComponent* InventoryManagerComponent;

	/* Combat interface */
	virtual int32 GetAvatarLevel() override;
		/* Combat interface */

private:


	APlayerStateBase* PlayerState;
	APlayerControllerBase* PlayerController;



public:





private:



};

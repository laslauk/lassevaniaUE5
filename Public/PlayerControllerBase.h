// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "PlayerControllerBase.generated.h"


class UMainHUDWidget;
class UAbilitySystemComponent;
class UInventoryComponent;
class UInventoryMainMenuWidget;
class APlayerCharacterBase;
class ULVAbilitySystemComponent;
class MapMenuWidgetClass;
class UMapMenuWidget;
class ALassevaniaHUD;
/* INPUT CUE https://www.youtube.com/watch?v=8yLq7jlVCAY&t=6090s*/
/* https://gascompanion.github.io/ability-queue-system/ */


/*
ABILITY ACTIVATION:
Abiltity jotka lisätään AbilitySetin kautta, on FLassevaniaAbilitySet_GameplayAbility STRUCT
jossa InputTag data määritetty DataAssetille.

PostProcessInput controllerilla kutsuu joka input handle framen jälkeen jälkeen
Oman abilitySysteemin LVASC->ProcessAbilityInput(DeltaTime, bGamePaused);
joka checkaa InputHeld, InputPRssed, input released arrayt joihin laitetaan
AbilitySpecit ja se yrittää joka kutsu aktivoida abilityn.

Esim clickauksessa katsotaan InputPressedSpecHandles mitä siellä on ja yritetään aktivoidaan ne joka
frame.

Controlleri bindataan inputit AbilityInputTagPressed(InputTag) joka 
ilmoittaa AbilitySysteemille kutsumalla ASC->AbilityInputTagPressed mikä inputTag laitetaan
InputPressed/HeldSpec handle arrayhyn.


*/

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttributeWidgetSetSignature);


UCLASS()
class LASSEVANIA_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<ALassevaniaHUD> HUDClass;

	virtual void OnPossess(APawn* aPawn) override;

	void InitializePlayerInput();


	UFUNCTION(BlueprintCallable, BlueprintPure)
	UAbilitySystemComponent* GetAbilitySystemComponentFromActor() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	ULVAbilitySystemComponent* GetLVAbilitySystemComponentFromActor() const;

	virtual void SetupInputComponent() override;

	void Input_AbilityInputTagPressed(FGameplayTag InputTag);

	void Input_AbilityInputTagReleased(FGameplayTag InputTag);

	/* Todo: input mallia void ULyraAbilitySystemComponent::ProcessAbilityInput(float DeltaTime, bool bGamePaused) LyraAbilitySystemComponent*/
	
	/* called after processing ipnut */
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;

	UInventoryComponent* GetInventoryComponent();


	UFUNCTION(BlueprintCallable, BlueprintPure)
	APlayerCharacterBase* GetPlayerCharacterBase();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryMainMenuWidget> InventoryWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidgetBase> AttributeMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMainHUDWidget> MainHUDWIdgetClass;


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMapMenuWidget> MapMenuWidgetClass;



	
	/* CONTROLS */

	UPROPERTY(EditDefaultsOnly)
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly)
	class UInputAction* MoveRightInputAction;


	UPROPERTY(EditDefaultsOnly)
	class UInputAction* SprintInputAction;

	UPROPERTY(EditDefaultsOnly)
	class UInputAction* PrimaryInputAction;


	UPROPERTY(EditDefaultsOnly)
	class UInputAction* OpenMapMenuInputAction;


	UPROPERTY(EditDefaultsOnly)
	class UInputAction* InteractInputAction;

	UPROPERTY(EditDefaultsOnly)
		class UInputAction* OpenInventoryAction;

	UPROPERTY(EditDefaultsOnly)
		FGameplayTag InputTag_Move;

	UPROPERTY(EditDefaultsOnly)
		class UInputAction* SlotOneInputAction; 	/* TODO JÄRKEVÄMPI SLOT SYSTEM*/

	UPROPERTY(EditDefaultsOnly)
		class UInputAction* SlotTwoInputAction; 	/* TODO JÄRKEVÄMPI SLOT SYSTEM*/

	UPROPERTY(EditDefaultsOnly)
		class UInputAction* SlotThreeInputAction; 	/* TODO JÄRKEVÄMPI SLOT SYSTEM*/

	/* Input Action Callbacks */
	void OnMoveRightInputAction(const struct FInputActionValue& val);

	void OnInteractInputAction(const struct FInputActionValue& val);

	
//	void OnSecondaryInputAction(const struct FInputActionValue& val);
	 
	void OnSlotOneInputAction(const struct FInputActionValue& val);  /* TODO JÄRKEVÄMPI SLOT SYSTEM*/
//	void OnSlotTwoInputAction(const struct FInputActionValue& val); /* TODO JÄRKEVÄMPI SLOT SYSTEM*/
//	void OnSlotThreeInputAction(const struct FInputActionValue& val); /* TODO JÄRKEVÄMPI SLOT SYSTEM*/
//	void OnSprintInputActionStarted(const struct FInputActionValue& val);



	void OnMapMenuOpenInputAction(const struct FInputActionValue& val);

	void OnOpenInventoryAction(const struct FInputActionValue& val);

	void OnAttributeWidgetSet();

	UPROPERTY(BlueprintAssignable)
	FOnAttributeWidgetSetSignature AttributeWidgetSet;


	void Input_Move(const FInputActionValue& InputActionValue);


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidgetBase* AttributeMenuWidget;

private:

	/* PlayerCharacter Reference set OnPossess*/
	APlayerCharacterBase* PlayerCharacterBase;

	class UMainHUDWidget* MainHUDWidget;

	class UMapMenuWidget* MapMenuWidget;


	/* LEGACY */
	/*
	void OnJumpInputActionStarted(const struct FInputActionValue& val);

		UPROPERTY(EditDefaultsOnly)
	class UInputAction* JumpInputAction;



	*/
};

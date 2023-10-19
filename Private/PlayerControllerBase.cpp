// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"
#include "PlayerStateBase.h"
#include "AbilitySystemComponent.h"
#include "EnhancedPlayerInput.h"
#include "InputActionValue.h"
#include "AbilitySystem/LVAbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Inventory/InventoryItemInstance.h"
#include "Inventory/InventoryMainMenuWidget.h"
#include "Input/LassevaniaInputConfig.h"
#include "UI/MainHUDWidget.h"
#include "Inventory/InventoryFragment_EquippableItem.h"
#include "LassevaniaCommonTypes.h"
#include "Input/LVInputComponent.h"
#include "Equipment/EquipmentDefinition.h"
#include "Inventory/InventoryItemDefinition.h"
#include "GameplayTagsManager.h"
#include "Equipment/EquipmentInstance.h"
#include "Inventory/InventoryManagerComponent.h"
#include "UI/MapMenuWidget.h"
#include "Character/PlayerCharacterBase.h"
#include "Inventory/InventoryComponent.h"
#include "UI/HUD/LassevaniaHUD.h"
#include "AbilitySystem/LVAbilitySystemComponent.h"
#include "DataAssets/CharacterDataAsset.h"
#include "Equipment/EquipmentManagerComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "LassevaniaGameplayTags.h"
#include "UI/Widget/DamageTextComponent.h"
#include "CharacterZDBase.h"


void APlayerControllerBase::ShowDamageNumber(float DamageAmount, ACharacter* TargetCharacter, bool bBlockingHit, bool bCriticalHit)
{

	/* is valid checks PendingKill() aswell*/
	if (IsValid(TargetCharacter) && DamageTextComponentClass)
	{
		UDamageTextComponent* DamageText = NewObject<UDamageTextComponent>(TargetCharacter, DamageTextComponentClass);
		DamageText->RegisterComponent();

		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

		DamageText->AddRelativeLocation(FVector(0.f, 0.f, 170.f));
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		DamageText->SetDamageText(DamageAmount, bBlockingHit, bCriticalHit);
	}

}

void APlayerControllerBase::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	ClientSetHUD(HUDClass);

	/*Set Character's Variable references to PlayerState and COntroller*/
	 PlayerCharacterBase = Cast<APlayerCharacterBase>(aPawn);
	 UAbilitySystemComponent* ASC = nullptr;
	if (PlayerCharacterBase)
	{
		APlayerStateBase* PlayerStateRef = GetPlayerState<APlayerStateBase>();

		PlayerCharacterBase->SetPlayerController(this);
		PlayerCharacterBase->SetPlayerState(PlayerStateRef);
		PlayerStateRef->GetInventoryComponent()->InitInventoryWidget(InventoryWidgetClass);

		ASC = PlayerCharacterBase->GetAbilitySystemComponent();

		if ( ASC )
		{
		//	ASC->SetAvatarActor(PlayerCharacterBase);
			ASC->InitAbilityActorInfo(PlayerStateRef, PlayerCharacterBase);

			UE_LOG(LogTemp, Warning, TEXT("Owner ACtor ASC: %s"), *ASC->GetOwnerActor()->GetName());

			ALassevaniaHUD* LVHUD = Cast<ALassevaniaHUD>(GetHUD());
			if (LVHUD)
			{
				UE_LOG(LogTemp, Warning, TEXT("Saatiin HUD %s"), *LVHUD->GetName());
				

				UAttributeSet* AttributeSet = Cast< UAttributeSet>(PlayerStateRef->GetAttributeSetComponent());
				
				if (AttributeSet)
				{
					UE_LOG(LogTemp, Warning, TEXT("saatii nmyös attribute set"));
				}
				
				LVHUD->InitOverlay(this, PlayerStateRef, ASC, AttributeSet);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Ei saatu hudia 1"));

				if (APlayerControllerBase::GetHUD())
				{
					UE_LOG(LogTemp, Warning, TEXT("saatiin paskaa saatu hudia2"));
				}

			}


		}
	}

	/*
	if (MainHUDWIdgetClass)
	{
		MainHUDWidget = CreateWidget<UMainHUDWidget>(this, MainHUDWIdgetClass);
		MainHUDWidget->AddToViewport();
	} */

	/* Set audio listener to PlayerCharacter - Cinematic Camera currently so far away that sounds are weird, due to wanted Depth of Field blur ffect*/
	SetAudioListenerOverride
	(
		PlayerCharacterBase->GetCapsuleComponent(), /* Component to attach */
		PlayerCharacterBase->GetCapsuleComponent()->GetComponentLocation(), /* location */
		FRotator::ZeroRotator /* rotation */
	);


	if (MapMenuWidgetClass)
	{
		MapMenuWidget = CreateWidget<UMapMenuWidget>(this, MapMenuWidgetClass);
		MapMenuWidget->AddToViewport();
		MapMenuWidget->SetVisibility((ESlateVisibility::Collapsed));
	}

	if ((AttributeMenuWidget == nullptr) && IsValid(AttributeMenuWidgetClass))
	{

		AttributeMenuWidget = CreateWidget<UUserWidgetBase>(this, AttributeMenuWidgetClass);
		AttributeMenuWidget->AddToViewport();
		AttributeMenuWidget->SetVisibility((ESlateVisibility::Collapsed));
	}


	/* DONE IN INVENTORY COMPONENT  - Inventory component is concerned on opening it
	if (InventoryWidgetClass)
	{
		InventoryMenuWidget = CreateWidget<UInventoryMainMenuWidget>(this, InventoryWidgetClass);

		InventoryMenuWidget->AddToViewport();
		InventoryMenuWidget->SetVisibility((ESlateVisibility::Collapsed));
	}

	*/


	/* DEFAULT STARTING STAST + ABILITIES - Importan*/
	/* Note: do this here, if character is placed in world before haviing possessed, AbiliySystem from player staten ot found*/
	InitializePlayerInput();


	if (ASC)
	{
		PlayerCharacterBase->InitializeDefaultAttributes();
		PlayerCharacterBase->ApplyStartupEffects();
		PlayerCharacterBase->GiveAbilities();
		PlayerCharacterBase->SetDamageListenerTagCallback();
	}



}


UAbilitySystemComponent* APlayerControllerBase::GetAbilitySystemComponentFromActor() const
{
	return GetPlayerState<APlayerStateBase>()->GetAbilitySystemComponent();
}


ULVAbilitySystemComponent* APlayerControllerBase::GetLVAbilitySystemComponentFromActor() const
{
	return GetPlayerState<APlayerStateBase>()->GetLVAbilitySystemComponent();
}

UInventoryComponent* APlayerControllerBase::GetInventoryComponent()
{
	return GetPlayerState<APlayerStateBase>()->GetInventoryComponent();
}

APlayerCharacterBase* APlayerControllerBase::GetPlayerCharacterBase()
{
	return PlayerCharacterBase;
}






void APlayerControllerBase::InitializePlayerInput()
{
	/* NOTE:::::::::: CHARACTEREILLA ON CHJARACTER DATA MIKÄ PITÄÄ PISTÄÄÄ!!!!!!!!*/
	/* NOTE:::::::::: CHARACTEREILLA ON CHJARACTER DATA MIKÄ PITÄÄ PISTÄÄÄ!!!!!!!!*/
	/* NOTE:::::::::: CHARACTEREILLA ON CHJARACTER DATA MIKÄ PITÄÄ PISTÄÄÄ!!!!!!!!*/

	/* NOTE - mihi muuallekkaa ny*/


	/* Oletus että kustutaan onpossess äjlkeen?*/

	/* ACharacterZDBAsella CharacterDataAsset jossa pitäisi olla kaikki */
	/* Input Config ptr*/
	UE_LOG(LogTemp, Warning, TEXT("PlayerControllerbase  -> InitializePlayerInput 1 "));
	UEnhancedInputLocalPlayerSubsystem* Subsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (PlayerCharacterBase)
	{
		const UCharacterDataAsset* CharacterData = PlayerCharacterBase->GetCharacterData();

		UE_LOG(LogTemp, Warning, TEXT("PlayerControllerbase  -> InitializePlayerInput2 "));
		if (CharacterData)
		{
			UE_LOG(LogTemp, Warning, TEXT("PlayerControllerbase  -> InitializePlayerInput 3 "));
			const ULassevaniaInputConfig* InputConfig = CharacterData->InputConfig;

			if (InputConfig)
			{


				UE_LOG(LogTemp, Warning, TEXT("PlayerControllerbase  -> InitializePlayerInput 4 "));
				ULVInputComponent* LVInputComp = Cast<ULVInputComponent>(InputComponent);

				if (LVInputComp)
				{
					UE_LOG(LogTemp, Warning, TEXT("PlayerControllerbase  -> InitializePlayerInput 5 "));
					UE_LOG(LogTemp, Warning, TEXT("InitializePlayerInput -> LVInputComp -->"));
					LVInputComp->AddInputMappings(InputConfig, Subsystem);

				TArray<uint32> BindHandles;
				LVInputComp->BindAbilityActions(InputConfig, this, &ThisClass::Input_AbilityInputTagPressed, &ThisClass::Input_AbilityInputTagReleased, /*out*/ BindHandles);

				if (InputTag_Move.IsValid())
				{
					LVInputComp->BindNativeAction(InputConfig, InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move, false);

				}
			
			//	LyraIC->BindNativeAction(InputConfig, GameplayTags.InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move, /*bLogIfNotFound=*/ false);
			//	LyraIC->BindNativeAction(InputConfig, GameplayTags.InputTag_Look_Mouse, ETriggerEvent::Triggered, this, &ThisClass::Input_LookMouse, /*bLogIfNotFound=*/ false);
			//	LyraIC->BindNativeAction(InputConfig, GameplayTags.InputTag_Look_Stick, ETriggerEvent::Triggered, this, &ThisClass::Input_LookStick, /*bLogIfNotFound=*/ false);
			//	LyraIC->BindNativeAction(InputConfig, GameplayTags.InputTag_Crouch, ETriggerEvent::Triggered, this, &ThisClass::Input_Crouch, /*bLogIfNotFound=*/ false);
			//	LyraIC->BindNativeAction(InputConfig, GameplayTags.InputTag_AutoRun, ETriggerEvent::Triggered, this, &ThisClass::Input_AutoRun, /*bLogIfNotFound=*/ false);
					
				

				}
			}


		}
	}
}




void APlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (Subsystem)
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	UEnhancedInputComponent* EI = Cast<UEnhancedInputComponent>(InputComponent);

	InitializePlayerInput();



	if (EI)
	{
		

		/* 
		
		legacy 
		if (JumpInputAction)
		{
			EI->BindAction(JumpInputAction, ETriggerEvent::Started, this, &APlayerControllerBase::OnJumpInputActionStarted);
			EI->BindAction(JumpInputAction, ETriggerEvent::Completed, this, &APlayerControllerBase::OnJumpInputActionEnded);
		}

		*/

		if (MoveRightInputAction)
		{
			EI->BindAction(MoveRightInputAction, ETriggerEvent::Triggered, this, &APlayerControllerBase::OnMoveRightInputAction);
		}

		if (InteractInputAction)
		{
			EI->BindAction(InteractInputAction, ETriggerEvent::Started, this, &APlayerControllerBase::OnInteractInputAction);
		}

		if (OpenInventoryAction)
		{
			EI->BindAction(OpenInventoryAction, ETriggerEvent::Started, this, &APlayerControllerBase::OnOpenInventoryAction);
		}

		if (OpenMapMenuInputAction)
		{
			EI->BindAction(OpenMapMenuInputAction, ETriggerEvent::Started, this, &APlayerControllerBase::OnMapMenuOpenInputAction);
		}


		if (SlotOneInputAction)
		{
			EI->BindAction(SlotOneInputAction, ETriggerEvent::Started, this, &APlayerControllerBase::OnSlotOneInputAction);
		}

	
	}

}

void APlayerControllerBase::Input_AbilityInputTagPressed(FGameplayTag InputTag)
{
	//UE_LOG(LogTemp, Warning, TEXT("Input_AbilityInputTagPressed -->"));
	if (PlayerCharacterBase)
	{

		ULVAbilitySystemComponent* AbilitySystemComp = GetLVAbilitySystemComponentFromActor();
		if (AbilitySystemComp)
		{

			//UE_LOG(LogTemp, Warning, TEXT("Input_AbilityInputTagPressed -->"));
			AbilitySystemComp->AbilityInputTagPressed(InputTag);
		}
	}
}

void APlayerControllerBase::Input_AbilityInputTagReleased(FGameplayTag InputTag)
{
	const APawn* PawnA = GetPawn<APawn>();
	if (!PawnA)
	{
		return;
	}

	if (ULVAbilitySystemComponent* AbilitySystemComp = GetLVAbilitySystemComponentFromActor())
	{
		AbilitySystemComp->AbilityInputTagReleased(InputTag);
	}

}



void APlayerControllerBase::OnSlotOneInputAction(const FInputActionValue& val)
{

	
	APlayerCharacterBase* CharRef = GetPlayerCharacterBase();
	TArray<UInventoryItemInstance*> Items = CharRef->InventoryManagerComponent->GetAllItems();




	if (Items.Num() <= 0) { return; }

	UInventoryItemInstance* Item = Items[0];

	UE_LOG(LogTemp, Warning, TEXT("item: %s"), *Item->GetItemDef()->GetDefaultObject<UInventoryItemDefinition>()->DisplayName.ToString());
	const UInventoryFragment_EquippableItem* EquipInfo = Item->FindFragmentByClass<UInventoryFragment_EquippableItem>();


	if (EquipInfo)
	{	

		UEquipmentDefinition* EquipDef = EquipInfo->EquipmentDefinition->GetDefaultObject<UEquipmentDefinition>();

		if (EquipDef)
		{

			/* TODO - JOS INVENTORYSSÄ ON ITEMS JOILLAW ON ENCHANTING YMS ITEM INSTANSSI KOHTASIA asioita ni ny 
			tällä järjestelmällä ottaa vaa item def templateja ::_
			*/
			UE_LOG(LogTemp, Warning, TEXT("EquipDef: "));
			CharRef->EquipmentManagerComponent->EquipItem(EquipInfo->EquipmentDefinition);
		}


	}

	/*




	if (EquipInfo)
	{
		UE_LOG(LogTemp, Warning, TEXT("EquipDef: "));
		
	/
	}

	*/

//	CharRef->EquipmentManagerComponent->EquipItem();



}




void APlayerControllerBase::OnMapMenuOpenInputAction(const FInputActionValue& val)
{
	
		//OnAttributeWidgetSet();
		/* Nyt widgetissä palautetaan - TODO joku more robost system 
		sitten kun keksii miten UI ja input (common Ui plugin perhaps)
		*/

	if(AttributeMenuWidget)
	{
	
		FInputModeUIOnly InputMode;
	//	SetInputMode(InputMode);
		AttributeMenuWidget->SetVisibility(ESlateVisibility::Visible);
	//	AttributeMenuWidget->SetFocus();
		//InputMode.SetWidgetToFocus(MapMenuWidget->TakeWidget());
		SetShowMouseCursor(true);
	}

}

/* NOTE, NYT WIDGET OTTAA INPUT CONSUMEN NIIN EI KOSKAAN KUTSUTA CLOSE */
void APlayerControllerBase::OnOpenInventoryAction(const FInputActionValue& val)
{


	UInventoryComponent* InventoryComp = GetInventoryComponent();

	APlayerCharacterBase* CharRef = GetPlayerCharacterBase();
	UE_LOG(LogTemp, Warning, TEXT("---- ITEMS IN INVENTORY ----- "));
	if (CharRef)
	{
		TArray<UInventoryItemInstance*> Items = CharRef->InventoryManagerComponent->GetAllItems();

		for (UInventoryItemInstance* Item : Items)
		{
			UE_LOG(LogTemp, Warning, TEXT("Item: %s: x%d/%d"),
				*Item->GetItemDef()->GetDefaultObject<UInventoryItemDefinition>()->DisplayName.ToString(),
				Item->GetStackItemCount(),
				Item->GetItemDef()->GetDefaultObject<UInventoryItemDefinition>()->StackSize
				);
		}


		for (UEquipmentInstance* item : CharRef->EquipmentManagerComponent->GetAllEquipmentInstances())
		{
				UE_LOG(LogTemp, Warning, TEXT("EQUIPMENT: %s"), *item->GetName());
		}

	}


	if (InventoryComp->bIsMenuWidgetOpen)
	{
		UE_LOG(LogTemp, Warning, TEXT("closing Inventory"));
		InventoryComp->SetShowInventoryMenu(EInventoryMenuVisibility::Hide);
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Opening Inventory"));
		InventoryComp->SetShowInventoryMenu(EInventoryMenuVisibility::Show);
	}

}

void APlayerControllerBase::Input_Move(const FInputActionValue& InputActionValue)
{
	if (PlayerCharacterBase)
		PlayerCharacterBase->TryMovement(InputActionValue.GetMagnitude());
}

void APlayerControllerBase::OnAttributeWidgetSet()
{
	AttributeWidgetSet.Broadcast();
}


void APlayerControllerBase::OnMoveRightInputAction(const  FInputActionValue& val)
{

	PlayerCharacterBase->TryMovement(val.GetMagnitude());

}

void APlayerControllerBase::OnInteractInputAction(const  FInputActionValue& val)
{
	if (PlayerCharacterBase)
	{
		UE_LOG(LogTemp, Warning, TEXT("INTERACTING"));
		PlayerCharacterBase->TryInteract();
		//PlayerCharacter->TryI
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerCharacterBase - null - INTERACTING"));
	}
}

void APlayerControllerBase::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	if (ULVAbilitySystemComponent* LVASC = GetLVAbilitySystemComponentFromActor())
	{
		LVASC->ProcessAbilityInput(DeltaTime, bGamePaused);
	}

	Super::PostProcessInput(DeltaTime, bGamePaused);
}
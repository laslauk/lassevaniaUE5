// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryComponent.h"
#include "Inventory/InventoryMainMenuWidget.h"
#include "PlayerControllerBase.h"
#include "PlayerStateBase.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

}

APlayerController* UInventoryComponent::GetPlayerController()
{
	return Cast<APlayerStateBase>(GetOwner())->GetPlayerController();
}

void UInventoryComponent::InitInventoryWidget(TSubclassOf<UInventoryMainMenuWidget> InventoryMenuWidgetClass)
{
	APlayerController* PlayerController = GetPlayerController();

	if (PlayerController )
	{

	if(InventoryMenuWidgetClass) 
	{
		InventoryMenuWidget = CreateWidget<UInventoryMainMenuWidget>(PlayerController, InventoryMenuWidgetClass);
			if (InventoryMenuWidget)
			{
				InventoryMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
				InventoryMenuWidget->AddToViewport();
				bIsMenuWidgetOpen = false;
			}
		}
	}
}

void UInventoryComponent::SetShowInventoryMenu(EInventoryMenuVisibility Visibility)
{
	if (!InventoryMenuWidget) return;

	APlayerControllerBase* PlayerController = Cast<APlayerControllerBase>(GetPlayerController());

	if (PlayerController)
	{

		if (Visibility == EInventoryMenuVisibility::Show)
		{
			PlayerController->SetShowMouseCursor(true);
			InventoryMenuWidget->SetVisibility(ESlateVisibility::Visible);
			FInputModeUIOnly UIMode;
			UIMode.SetWidgetToFocus(InventoryMenuWidget->TakeWidget());
			PlayerController->SetInputMode(UIMode);
			bIsMenuWidgetOpen = true;
		}
		else if (Visibility == EInventoryMenuVisibility::Hide)
		{
			FInputModeGameOnly GameUImode;
			InventoryMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
			PlayerController->SetInputMode(GameUImode);
			PlayerController->SetShowMouseCursor(false);
			bIsMenuWidgetOpen = false;
		}

	}
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


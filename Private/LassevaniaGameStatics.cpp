// Fill out your copyright notice in the Description page of Project Settings.


#include "LassevaniaGameStatics.h"

#include "PlayerControllerBase.h"
#include "Inventory/InventoryComponent.h"
#include "PlayerStateBase.h"

UInventoryComponent* ULassevaniaGameStatics::GetPlayerInventoryComponent(UObject* WorldContextObject)
{

	return WorldContextObject->GetWorld()
			->GetFirstPlayerController()
			->GetPlayerState<APlayerStateBase>()
			->GetInventoryComponent();
}
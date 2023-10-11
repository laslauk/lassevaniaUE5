// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../LassevaniaCommonTypes.h"
#include "InventoryComponent.generated.h"

class UInventoryMainMenuWidget;

UENUM(BlueprintType)
 enum class EInventoryMenuVisibility: uint8
{
	Show UMETA(DisplayName = "ShowMenu"),
	Hide UMETA(DisplayName = "HideMenu"),
};

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LASSEVANIA_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();





	UFUNCTION()
	void InitInventoryWidget(TSubclassOf<UInventoryMainMenuWidget> InventoryMenuWidgetClass);

	void SetShowInventoryMenu(EInventoryMenuVisibility Visibility);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	APlayerController* GetPlayerController();


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool bIsMenuWidgetOpen = false;

	/* INVENTORY NIIKU PAREMMAKS - item instance ja actor eriksee*/
	UPROPERTY(EditAnywhere)
	TArray<FInventoryWidgetSlotData> Inventory;

private:
	UInventoryMainMenuWidget* InventoryMenuWidget;

};

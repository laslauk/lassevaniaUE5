// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interfaces/InteractInterface.h"
#include "ItemActorBase.generated.h"

class UInventoryItemInstance;
class UItemStaticData;
class UPickupDefinition;
class UStaticMeshComponent;
class UPaperSpriteComponent;

/* This class represents the Object IN WORLD, that can be picked up, has a pointer to owning item instance.
When picked up., it is destroyed*/

/* 

InventoryItemInstance
-has ptr to this actor class 
-ptr data to staticdata


IF ACTOR PLACED IN WORLD:
-> Begin play creates inventoryItemInstance

ItemStaticData 
	->


*/

UCLASS()
class LASSEVANIA_API AItemActorBase : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemActorBase(const FObjectInitializer& ObjectInitializer);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* interact interface */
	UFUNCTION(BlueprintCallable)
	virtual void Interact(APlayerController* PlayerController) override;

	void Init(class UInventoryItemInstance* InInstance, int32 Quantity = 1);

	virtual void OnConstruction(const FTransform& Transform) override;

	
	UFUNCTION(BlueprintCallable, Category = "Lassevania|WeaponPickup")
	bool GiveItem(TSubclassOf<UInventoryItemDefinition> WeaponItemClass, APawn* ReceivingPawn);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lassevania|Pickup")
	TSubclassOf<UPickupDefinition> ItemDefinitionClass;

	void ShowPickupWidget(bool bShowWidget);


	UPROPERTY(EditAnywhere)
	class USphereComponent* SphereComponent;


	UPROPERTY(VisibleAnywhere)
	class UPaperSpriteComponent* SpriteComponent;

	UPROPERTY(VisibleAnywhere, Category = " Item properties")
		class UWidgetComponent* PickupTextWidget;

	TObjectPtr<UStaticMesh> DisplayMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lassevania|Pickup")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;



	/* Defines how many items of this type this item will give*/
	/* Forced to 1 on construction if item  StackSize in definition is capped to 1*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lassevania | Pickup")
	int32 ItemStackCount = 1;

private:


	//Data asset used to configure a Weapon Spawner
	UPROPERTY()
	TObjectPtr<UPickupDefinition> ItemDefinition;
};

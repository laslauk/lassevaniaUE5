// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/ItemActorBase.h"
#include "Equipment/PickupDefinition.h"
#include "Inventory/InventoryItemInstance.h"
#include "PaperSpriteComponent.h"
#include "Character/PlayerCharacterBase.h"
#include "Inventory/InventoryManagerComponent.h"
#include "Components/SphereComponent.h"
#include "LassevaniaCommonTypes.h"
#include "Inventory/InventoryItemDefinition.h"



#include "Components/StaticMeshComponent.h"


AItemActorBase::AItemActorBase(const FObjectInitializer& ObjectInitializer)
{

	PrimaryActorTick.bCanEverTick = false;
	SpriteComponent = ObjectInitializer.CreateDefaultSubobject<UPaperSpriteComponent>(this, TEXT("Paper Sprite Component"));
	SpriteComponent->RegisterComponent();

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->RegisterComponent();
	SetRootComponent(SphereComponent);



	StaticMeshComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Static Mesh Comp"));
	StaticMeshComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	StaticMeshComponent->RegisterComponent();









}



// Called when the game starts or when spawned
void AItemActorBase::BeginPlay()
{
	Super::BeginPlay();
	
	/* 1. show pickup text widget */


	/* This item has been placed to world in editor: This actor drives the creation of item instance */
	/* Uses ItemStaticData to create the instance */
	 


}

// Called every frame
void AItemActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemActorBase::Interact(APlayerController* PlayerController)
{
	UE_LOG(LogTemp, Warning, TEXT("INTeracting with item from: %s"), *PlayerController->GetName());

	APawn* InteractorPawn = PlayerController->GetPawn();

	if (InteractorPawn)
	{

		TObjectPtr<APlayerCharacterBase> PlayerCharacterRef = Cast<APlayerCharacterBase>(InteractorPawn);


		if (PlayerCharacterRef && ItemDefinition)
		{

				UE_LOG(LogTemp, Warning, TEXT("GIVING ITEM: %s TO %s"), *ItemDefinition->InventoryItemDefinition->GetName(), *PlayerCharacterRef->GetName());
			 GiveItem(ItemDefinition->InventoryItemDefinition, PlayerCharacterRef);

			
		}

	}
}

void AItemActorBase::Init(UInventoryItemInstance* InInstance, int32 Quantity)
{

}

void AItemActorBase::OnConstruction(const FTransform& Transform)
{


	if (ItemDefinitionClass)
	{
		ItemDefinition = ItemDefinitionClass->GetDefaultObject<UPickupDefinition>();

		if (ItemDefinition)
		{
			UE_LOG(LogTemp, Warning, TEXT("asdasdasd"));
			StaticMeshComponent->SetStaticMesh(ItemDefinition->DisplayMesh);


			if (ItemDefinition->StackSize == 1)
			{
				ItemStackCount = 1;
			}

		}

	}

	Super::OnConstruction(Transform);
}


bool AItemActorBase::GiveItem(TSubclassOf<UInventoryItemDefinition> WeaponItemClass, APawn* ReceivingPawn)
{
	TObjectPtr<APlayerCharacterBase> PlayerCharacterRef = Cast<APlayerCharacterBase>(ReceivingPawn);

	if (PlayerCharacterRef)
	{
		if (PlayerCharacterRef->InventoryManagerComponent)
		{
			/* add the actual item to players inventory*/
			UInventoryItemInstance* ItemInstance = PlayerCharacterRef->InventoryManagerComponent->AddItemDefinition(WeaponItemClass, ItemStackCount);

			if (ItemInstance)
			{
				auto item = ItemInstance->GetItemDef();
				if (item)
				{
				
				UE_LOG(
					LogTemp, Warning, TEXT("ADDED Item to PlayerCharacterRef Inventory, instance name: %s"), 
					*item->GetDefaultObject<UInventoryItemDefinition>()->DisplayName.ToString()
					);
				}

				Destroy();
			}
			else
			{
				UE_LOG(
					LogTemp, Warning, TEXT("Give Item instance nullptr"));
			}
		}
	}
	return false;
}




void AItemActorBase::ShowPickupWidget(bool bShowWidget)
{
}


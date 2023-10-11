// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateBase.h"
#include "Inventory/InventoryComponent.h"
#include "AttributeSetBase.h"
#include "AbilitySystemComponent.h"
//#include "AbilitySystemComponent.h"

APlayerStateBase::APlayerStateBase()
{


	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
	AbilitySystemComponent = CreateDefaultSubobject<ULVAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSetBaseComp =  CreateDefaultSubobject<UAttributeSetBase>(TEXT("AttributeSetBaseComponent"));
	InventoryComponent->RegisterComponent();
	AbilitySystemComponent->RegisterComponent();
	/* SINGLE PLAYER GAME FOR NOW NOTE!*/

	//AbilitySystemComponent->SetIsReplicated(false);
	

}


UAbilitySystemComponent* APlayerStateBase::GetAbilitySystemComponent() const
{

	return GetLVAbilitySystemComponent();
}


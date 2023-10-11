// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/EquipmentDefinition.h"
#include "Equipment/EquipmentInstance.h"


UEquipmentDefinition::UEquipmentDefinition(const FObjectInitializer& ObjectInitializer)
{
	InstanceType =  UEquipmentInstance::StaticClass();
}

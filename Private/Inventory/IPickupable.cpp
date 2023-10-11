// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/IPickupable.h"
#include "GameFramework/Actor.h"
#include "Inventory/InventoryManagerComponent.h"
#include "UObject/ScriptInterface.h"


// Add default functionality here for any IIPickupable functions that are not pure virtual.

UPickupableStatics::UPickupableStatics()
	: Super(FObjectInitializer::Get())
{
}


TScriptInterface<IIPickupable> UPickupableStatics::GetFirstPickupableFromActor(AActor* Actor)
{
	// If the actor is directly pickupable, return that.

	TScriptInterface<IIPickupable> PickupableActor(Actor);
	if (PickupableActor)
	{
		return PickupableActor;
	}

	//	 If the actor isn't pickupable, it might have a component that has a pickupable interface.
	TArray<UActorComponent*> PickupableComponents = Actor ? Actor->GetComponentsByInterface(UIPickupable::StaticClass()) : TArray<UActorComponent*>();
	if (PickupableComponents.Num() > 0)
	{
		// Get first pickupable, if the user needs more sophisticated pickup distinction, will need to be solved elsewhere.
		return TScriptInterface<IIPickupable>(PickupableComponents[0]);
	}

	return TScriptInterface<IIPickupable>();

}

void UPickupableStatics::AddPickupToInventory(UInventoryManagerComponent* InventoryComponent, TScriptInterface<IIPickupable> Pickup)
{
	if (InventoryComponent && Pickup)
	{
		const FInventoryPickup& PickupInventory = Pickup->GetPickupInventory();

		for (const FPickupTemplate& Template : PickupInventory.Templates)
		{
			InventoryComponent->AddItemDefinition(Template.ItemDef, Template.StackCount);
		}

		for (const FPickupInstance& Instance : PickupInventory.Instances)
		{
			InventoryComponent->AddItemInstance(Instance.Item);
		}
	}

}

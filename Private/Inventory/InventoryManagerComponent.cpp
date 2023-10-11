// Fill out your copyright notice in the Description page of Project Settings.



#include "Inventory/InventoryManagerComponent.h"
#include "Engine/ActorChannel.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "LassevaniaCommonTypes.h"
#include "Inventory/InventoryItemInstance.h"
#include "Inventory/InventoryItemDefinition.h"
#include "Misc/AssertionMacros.h"
#include "NativeGameplayTags.h"
#include "Net/UnrealNetwork.h"
#include "UObject/NameTypes.h"
#include "UObject/Object.h"
#include "UObject/ObjectPtr.h"
#include "UObject/UObjectBaseUtility.h"




UE_DEFINE_GAMEPLAY_TAG_STATIC(Inventory_Message_StackChanged, "Inventory.Message.StackChanged");

//////////////////////////////////////////////////////////////////////
// FInventory Entry


FString FInventoryEntry::GetDebugString() const
{

	TSubclassOf<UInventoryItemDefinition> ItemDef;
	if (Instance != nullptr)
	{
		ItemDef = Instance->GetItemDef();
	}

	return FString::Printf(TEXT("%s (%d x %s)"), *GetNameSafe(Instance), StackCount, *GetNameSafe(ItemDef));



}



//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// FLyraInventoryList



TArray<UInventoryItemInstance*> FInventoryList::GetAllItems() const
{
	TArray<UInventoryItemInstance*> Results;
	Results.Reserve(Entries.Num());

	for (const FInventoryEntry& Entry : Entries)
	{
		if (Entry.Instance != nullptr)
		{
			Results.Add(Entry.Instance);
		}
	}
	return Results;
}

void FInventoryList::PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize)
{
	for (int32 Index : RemovedIndices)
	{
		FInventoryEntry& Stack = Entries[Index];
		BroadcastChangeMessage(Stack, /*OldCount=*/ Stack.StackCount, /*NewCount=*/ 0);
				Stack.LastObservedCount = 0;
			}
	}

void FInventoryList::PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize)
{
	for (int32 Index : AddedIndices)
	{
		FInventoryEntry& Stack = Entries[Index];
		BroadcastChangeMessage(Stack, /*OldCount=*/ 0, /*NewCount=*/ Stack.StackCount);
		Stack.LastObservedCount = Stack.StackCount;
	}
}

void FInventoryList::PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize)
{
	for (int32 Index : ChangedIndices)
	{
		FInventoryEntry& Stack = Entries[Index];
		check(Stack.LastObservedCount != INDEX_NONE);
		BroadcastChangeMessage(Stack, /*OldCount=*/ Stack.LastObservedCount, /*NewCount=*/ Stack.StackCount);
		Stack.LastObservedCount = Stack.StackCount;
	}
}

void FInventoryList::BroadcastChangeMessage(FInventoryEntry& Entry, int32 OldCount, int32 NewCount)
{
	FInventoryChangeMessage Message;
	Message.InventoryOwner = OwnerComponent;
	Message.Instance = Entry.Instance;
	Message.NewCount = NewCount;
	Message.Delta = NewCount - OldCount;




	/* USE Gameplay  Message Router  */
	/* MESSAGE SUBSYSTEM!!*/
	/* https://github.com/imnazake/gameplay-message-router */
	/* USES TAGS!!!!!!*/

	UGameplayMessageSubsystem& MessageSystem = UGameplayMessageSubsystem::Get(OwnerComponent->GetWorld());
	MessageSystem.BroadcastMessage(Inventory_Message_StackChanged, Message);
}


/* TÄMÄ TEKEE MYÖS UUDEN INSTANSSIN! HYUOM*/
UInventoryItemInstance* FInventoryList::AddEntry(TSubclassOf<UInventoryItemDefinition> ItemDef, int32 StackCount)
{
	UInventoryItemInstance* Result = nullptr;

	if (ItemDef == nullptr) { return Result; }
	if (OwnerComponent == nullptr) { return Result; }



	AActor* OwningActor = OwnerComponent->GetOwner();
//	if(OwningActor->HasAuthority()); NOT FO LASSEVANIA, SINGLEP LAYEUR



	/* Tehdään tyhjä entry johon muutetaan membut*/
	FInventoryEntry& NewEntry = Entries.AddDefaulted_GetRef();
	NewEntry.Instance = NewObject<UInventoryItemInstance>(OwnerComponent->GetOwner()); //@TODO: Using the actor instead of component as the outer due to UE-127172
	NewEntry.Instance->SetItemDef(ItemDef);

	UE_LOG(LogTemp, Warning, TEXT("ADDED ITEM ENTRY With owner: %s"), *OwnerComponent->GetOwner()->GetName());

	for (UInventoryItemFragment* Fragment : GetDefault<UInventoryItemDefinition>(ItemDef)->Fragments)
	{
		if (Fragment != nullptr)
		{
			Fragment->OnInstanceCreated(NewEntry.Instance);
		}
	}



	/* NOTE: NewEntry StackCount ei tee mitään nyt?? mitäs sillä thedään?*/
	int32 Nothing = 0;
	NewEntry.Instance->AddStackItem(StackCount, Nothing);
	NewEntry.StackCount = StackCount;
	Result = NewEntry.Instance;

	MarkItemDirty(NewEntry);

	return Result;
}

void FInventoryList::AddEntry(UInventoryItemInstance* Instance)
{
	unimplemented();
}

void FInventoryList::RemoveEntry(UInventoryItemInstance* Instance)
{
	for (auto EntryIt = Entries.CreateIterator(); EntryIt; ++EntryIt)
	{
		FInventoryEntry& Entry = *EntryIt;
		if (Entry.Instance == Instance)
		{
			EntryIt.RemoveCurrent();
			MarkArrayDirty();
		}
	}
}
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

/* INVENTORY MANAGER COMPONENT */

UInventoryManagerComponent::UInventoryManagerComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
, InventoryList(this)
{

}

bool UInventoryManagerComponent::CanAddItemDefinition(TSubclassOf<UInventoryItemDefinition> ItemDef, int32 StackCount)
{
	//@TODO: Add support for stack limit / uniqueness checks / etc...
	return true;
}

UInventoryItemInstance* UInventoryManagerComponent::AddItemDefinition(TSubclassOf<UInventoryItemDefinition> ItemDef, int32 StackCount)
{
	UInventoryItemInstance* Result = nullptr;

	/* TODO - STACKAUS - Onko muita parempia ideoita? nyt FInventoryEntryllä stack size ja jos max niin uus instance, muute siihen vaa
		Tagisysteemillä mutta pitää TagStackContainerii systeemi mikä trackaa count stackia ja sekavaa?
	*/
/* 1. Katotaan onko jo tämmöstä instanssia */


	if (!ItemDef) { return nullptr; }

	bool found = false;
	UInventoryItemInstance* Instance = nullptr;
	for ( FInventoryEntry& Entry : InventoryList.Entries)
	{

		Instance = Entry.Instance;

		if (IsValid(Instance))
		{
			if (Instance->GetItemDef() == ItemDef && (Instance->HasFreeStackSlots()))
			{
				found = true;
				break;
			}
		}
	}


	/* Found first non-full instance of this item*/
	if (found)
	{
		/* Täysi instance*/
	
		if (IsValid(Instance)) 
		{
			int Over = 0;
			bool bOverStack = Instance->AddStackItem(StackCount, Over);
			UE_LOG(LogTemp, Warning, TEXT("Overstack count: %d"), Over);
			if (bOverStack && Over > 0)
			{

				int StackSize = (ItemDef->GetDefaultObject<UInventoryItemDefinition>()->StackSize);
				int32 FullStacksCount = FMath::Floor(Over/ StackSize);
				UE_LOG(LogTemp, Warning, TEXT("Full new stacks of item count: %d"), FullStacksCount);
				int32 LeftOver = Over - (StackSize * FullStacksCount);
		

				for (int32 i = 0; i < FullStacksCount; ++i)
				{
					Result = InventoryList.AddEntry(ItemDef, StackSize);

				}

				if (LeftOver > 0)
				{
					Result = InventoryList.AddEntry(ItemDef, LeftOver);
				}

			}
		Result = Instance;
	
		}
	
	}

	/* No existing type of this item instance exists - create new*/
	else
	{
		int StackSize = (ItemDef->GetDefaultObject<UInventoryItemDefinition>()->StackSize);
		
		if (StackSize < StackCount)
		{
			int32 FullStacksCount = FMath::Floor(StackCount / StackSize);
			int32 LeftOver = StackCount - (StackSize * FullStacksCount);


			for (int32 i = 0; i < FullStacksCount; ++i)
			{
				Result = InventoryList.AddEntry(ItemDef, StackSize);

			}

			if (LeftOver > 0)
			{
				Result = InventoryList.AddEntry(ItemDef, LeftOver);
			}
		}
		else
		{
			Result = InventoryList.AddEntry(ItemDef, StackCount);
		}


	}



	return Result;
}



void UInventoryManagerComponent::AddItemInstance(UInventoryItemInstance* ItemInstance)
{

	InventoryList.AddEntry(ItemInstance);
}

void UInventoryManagerComponent::RemoveItemInstance(UInventoryItemInstance* ItemInstance)
{
	InventoryList.RemoveEntry(ItemInstance);

}

TArray<UInventoryItemInstance*> UInventoryManagerComponent::GetAllItems() const
{
	return InventoryList.GetAllItems();
}


UInventoryItemInstance* UInventoryManagerComponent::FindFirstItemStackByDefinition(TSubclassOf<UInventoryItemDefinition> ItemDef) const
{
	for (const FInventoryEntry& Entry : InventoryList.Entries)
	{
		UInventoryItemInstance* Instance = Entry.Instance;

		if (IsValid(Instance))
		{
			if (Instance->GetItemDef() == ItemDef)
			{
				return Instance;
			}
		}
	}

	return nullptr;
}

int32 UInventoryManagerComponent::GetTotalItemCountByDefinition(TSubclassOf<UInventoryItemDefinition> ItemDef) const
{
	int32 TotalCount = 0;
	for (const FInventoryEntry& Entry : InventoryList.Entries)
	{
		UInventoryItemInstance* Instance = Entry.Instance;

		if (IsValid(Instance))
		{
			if (Instance->GetItemDef() == ItemDef)
			{
				++TotalCount;
			}
		}
	}

	return TotalCount;
}

bool UInventoryManagerComponent::ConsumeItemsByDefinition(TSubclassOf<UInventoryItemDefinition> ItemDef, int32 NumToConsume)
{
	AActor* OwningActor = GetOwner();
	if (!OwningActor)
	{
		return false;
	}

	//@TODO: N squared right now as there's no acceleration structure
	int32 TotalConsumed = 0;

	while (TotalConsumed < NumToConsume)
	{

		if (UInventoryItemInstance* Instance = UInventoryManagerComponent::FindFirstItemStackByDefinition(ItemDef))
		{
			InventoryList.RemoveEntry(Instance);
			++TotalConsumed;
		}
		else
		{
			return false;
		}
	}

	return TotalConsumed == NumToConsume;
}

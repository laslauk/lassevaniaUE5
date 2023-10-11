// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Net/Serialization/FastArraySerializer.h"
#include "../LassevaniaCommonTypes.h"



#include "InventoryManagerComponent.generated.h"


struct FNetDeltaSerializeInfo;
class UInventoryItemInstance;


/* message when item is added to inventory*/
/* message format for the subsystem messaging*/




USTRUCT(BlueprintType)
struct FInventoryChangeMessage
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadOnly, Category = Inventory)
		TObjectPtr<UActorComponent> InventoryOwner = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = Inventory)
		TObjectPtr<UInventoryItemInstance> Instance = nullptr;


	UPROPERTY(BlueprintReadOnly, Category = Inventory)
		int32 NewCount = 0;

	UPROPERTY(BlueprintReadOnly, Category = Inventory)
		int32 Delta = 0;

};


USTRUCT(BlueprintType)
struct FInventoryEntry : public FFastArraySerializerItem
{

public:


	GENERATED_BODY()

	FInventoryEntry() {}

	FString GetDebugString() const;

	UPROPERTY()
	TObjectPtr<UInventoryItemInstance> Instance = nullptr;

	UPROPERTY()
		int32 StackCount = 0;

	UPROPERTY()
	int32 LastObservedCount = INDEX_NONE;



};



/** List of inventory items */ 



USTRUCT(BlueprintType)
struct FInventoryList : public FFastArraySerializer
{
	GENERATED_BODY()

	FInventoryList(): OwnerComponent(nullptr) {}

	FInventoryList(UActorComponent* InOwnerComponent): OwnerComponent(InOwnerComponent) {}


	TArray<UInventoryItemInstance*> GetAllItems() const;

public:
	//~FFastArraySerializer contract
	void PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize);
	void PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize);
	void PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize);
	//~End of FFastArraySerializer contract

	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FInventoryEntry, FInventoryList>
			(Entries, DeltaParms, *this);
	}



	UInventoryItemInstance* AddEntry(TSubclassOf<UInventoryItemDefinition> ItemDef, int32 StackCount);


	/* Add entry ja remov entry tekevät / postavat instancen. Asettavat entry tietoon instanssin objektitsat*/
	void AddEntry(UInventoryItemInstance* Instance);

	void RemoveEntry(UInventoryItemInstance* Instance);

	void BroadcastChangeMessage(FInventoryEntry& Entry, int32 OldCount, int32 NewCount);


	UPROPERTY()
	TArray<FInventoryEntry> Entries;

	UPROPERTY(NotReplicated)
	TObjectPtr<UActorComponent> OwnerComponent;

};


template<>
struct TStructOpsTypeTraits<FInventoryList> : public TStructOpsTypeTraitsBase2<FInventoryList>
{
	enum { WithNetDeltaSerializer = true };
};








UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LASSEVANIA_API UInventoryManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryManagerComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = Inventory)
		bool CanAddItemDefinition(TSubclassOf<UInventoryItemDefinition> ItemDef, int32 StackCount = 1);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = Inventory)
	UInventoryItemInstance* AddItemDefinition(TSubclassOf<UInventoryItemDefinition> ItemDef, int32 StackCount = 1);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = Inventory)
	void AddItemInstance(UInventoryItemInstance* ItemInstance);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = Inventory)
	void RemoveItemInstance(UInventoryItemInstance* ItemInstance);


	UFUNCTION(BlueprintCallable, Category = Inventory, BlueprintPure = false)
	TArray<UInventoryItemInstance*> GetAllItems() const;

	UFUNCTION(BlueprintCallable, Category = Inventory, BlueprintPure)
	UInventoryItemInstance* FindFirstItemStackByDefinition(TSubclassOf<UInventoryItemDefinition> ItemDef) const;

	int32 GetTotalItemCountByDefinition(TSubclassOf<UInventoryItemDefinition> ItemDef) const;

	bool ConsumeItemsByDefinition(TSubclassOf<UInventoryItemDefinition> ItemDef, int32 NumToConsume);

	/* NOTE::::::::: NETWORKING - FOR WHEN MULTIPLAYER
	//~UObject interface
	virtual bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags) override;
	virtual void ReadyForReplication() override;
	//~End of UObject interface

	*/


	UPROPERTY(/*Replicated*/)
	FInventoryList InventoryList;
};

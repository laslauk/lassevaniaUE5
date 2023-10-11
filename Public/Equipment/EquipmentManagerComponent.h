// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../LassevaniaCommonTypes.h"
#include "../AbilitySystem/LassevaniaAbilitySet.h"
#include "Net/Serialization/FastArraySerializer.h"
#include "Components/PawnComponent.h"
#include "EquipmentManagerComponent.generated.h"

class UInventoryItemInstance;
class UEquipmentInstance;

class UEquipmentDefinition;

/* HUOMAUTUS IMPORTANT */
/* HUOMAUTUS IMPORTANT */
/* HUOMAUTUS IMPORTANT */
/* HUOMAUTUS IMPORTANT */

/* EQuipmentiksi lasketaan YLLÄPIDETTYJÄ itemeitä, ne luodaan InventoryItemien perusteella. EquipmentList ON YLLÄPIDETYISTÄ itemeistä
	jolloin ne voivat antaa AppliedEquipmentEntryn kautta AbilitySettejä ja efektjä koska ne OVAT equipped itsessään 
	

	Abilityt lisätään AddEntry() vaiheessa


*/

/* Single piece of applied equipment, such as helmet, chest armor, weapon*/
USTRUCT(BlueprintType)
struct FAppliedEquipmentEntry : public FFastArraySerializerItem
{

	GENERATED_BODY()

	FAppliedEquipmentEntry(){ }
	FString GetDebugString() const;

	// The equipment class that got equipped
	UPROPERTY()
	TSubclassOf<UEquipmentDefinition> EquipmentDefinition;


	UPROPERTY()
	TObjectPtr<UEquipmentInstance> Instance = nullptr;


	// Authority-only list of granted handles
	UPROPERTY(/*NotReplicated*/)
	FLassevaniaAbilitySet_GrantedHandles GrantedHandles;
};


/** List of applied equipment */
USTRUCT(BlueprintType)
struct FEquipmentList : public FFastArraySerializer
{
	GENERATED_BODY()


public:
	FEquipmentList()
	{

	}

	FEquipmentList(UActorComponent* InOwnerComponent):OwnerComponent(InOwnerComponent)
	{

	}

	//~FFastArraySerializer contract
	void PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize);
	void PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize);
	void PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize);
	//~End of FFastArraySerializer contract


	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FAppliedEquipmentEntry, FEquipmentList>(Entries, DeltaParms, *this);
	}

	UEquipmentInstance* AddEntry(TSubclassOf<UEquipmentDefinition> EquipmentDefinition);
	void RemoveEntry(UEquipmentInstance* Instance);

	ULVAbilitySystemComponent* GetAbilitySystemComponent() const;

	TArray< UEquipmentInstance*> GetAllAppliedEquipmentInstances();

	UPROPERTY()
	TArray<FAppliedEquipmentEntry> Entries;

	UPROPERTY(/*NotReplicated*/)
	UActorComponent* OwnerComponent;
};


template<>
struct TStructOpsTypeTraits<FEquipmentList> : public TStructOpsTypeTraitsBase2<FEquipmentList>
{
	enum { WithNetDeltaSerializer = true };
};



/**
 * 
 */
UCLASS(BlueprintType, Const)
class LASSEVANIA_API UEquipmentManagerComponent : public UPawnComponent
{
	GENERATED_BODY()

public:

	UEquipmentManagerComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/* Creates an instance, adds it to equipment list and calls instance's OnEquipped*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	UEquipmentInstance* EquipItem(TSubclassOf<UEquipmentDefinition> EquipmentDefinition);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
		void UnequipItem(UEquipmentInstance* ItemInstance);


	//~UObject interface
	//virtual bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags) override;
	//~End of UObject interface

		//~UActorComponent interface
	//virtual void EndPlay() override;
	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;
	virtual void ReadyForReplication() override;
	//~End of UActorComponent interface

		/** Returns the first equipped instance of a given type, or nullptr if none are found */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UEquipmentInstance* GetFirstInstanceOfType(TSubclassOf<UEquipmentInstance> InstanceType);

	/** Returns all equipped instances of a given type, or an empty array if none are found */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<UEquipmentInstance*> GetEquipmentInstancesOfType(TSubclassOf<UEquipmentInstance> InstanceType) const;

	template <typename T>
	T* GetFirstInstanceOfType()
	{
		return (T*)GetFirstInstanceOfType(T::StaticClass());
	}


	UFUNCTION(BlueprintCallable, BlueprintPure)
		TArray<UEquipmentInstance*> GetAllEquipmentInstances();




private:
	UPROPERTY(/*Replicated*/)
	FEquipmentList EquipmentList;

};


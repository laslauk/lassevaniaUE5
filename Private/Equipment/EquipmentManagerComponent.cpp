// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/EquipmentManagerComponent.h"
#include "Net/UnrealNetwork.h"
#include "Equipment/EquipmentInstance.h"
#include "Equipment/EquipmentDefinition.h"
#include "Net/UnrealNetwork.h"
#include "Misc/AssertionMacros.h"
#include "Character/PlayerCharacterBase.h"
#include "AbilitySystemGlobals.h"


FString FAppliedEquipmentEntry::GetDebugString() const
{
	return FString::Printf(TEXT("%s of %s"), *GetNameSafe(Instance), *GetNameSafe(EquipmentDefinition.Get()));
}


void FEquipmentList::PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize)
{
}

void FEquipmentList::PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize)
{
}

void FEquipmentList::PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize)
{
}


/* tekee myös uuden instancssin equipmentista */
UEquipmentInstance* FEquipmentList::AddEntry(TSubclassOf<UEquipmentDefinition> EquipmentDefinition)
{
	UEquipmentInstance* Result = nullptr;
	check(EquipmentDefinition != nullptr);
	check(OwnerComponent);
	check(OwnerComponent->GetOwner()->HasAuthority());

	const UEquipmentDefinition* EquipmentCDO = GetDefault<UEquipmentDefinition>(EquipmentDefinition);
	TSubclassOf<UEquipmentInstance> InstanceType = EquipmentCDO->InstanceType;

	if (InstanceType == nullptr)
	{
		InstanceType = UEquipmentInstance::StaticClass();

	}
	
	/* Ei vaan addata vaan tehdää default uus ja vaihetaan sen memberit (/( TODO SELFITÄ MIKS ?? )*/
	FAppliedEquipmentEntry& NewEntry = Entries.AddDefaulted_GetRef();
	NewEntry.EquipmentDefinition = EquipmentDefinition;

	/* Spawn / create actual instance object*/
	NewEntry.Instance = NewObject<UEquipmentInstance>(OwnerComponent->GetOwner(), InstanceType); //pitäisi olla actor eikä component, todo check
	Result = NewEntry.Instance;

	UE_LOG(LogTemp, Warning, TEXT("1  - Start grant "));
	/* Lisätään EquipmentDefinitionissa olevat Abiltiies to add, equipment instanssilla on lista abiltiy seteistä mitkä anentaan kun lisätään entry*/
	if (ULVAbilitySystemComponent* ASC = GetAbilitySystemComponent())
	{
		UE_LOG(LogTemp, Warning, TEXT(" 2   GETTING ABILITIES SYST COMP"));
		for (TObjectPtr<const ULassevaniaAbilitySet> AbilitySet : EquipmentCDO->AbilitySetsToGrant)
		{
		// GiveAbilitySystem pistää ability spec handlet Listaan	OutGrantedHandles->AddAbilitySpecHandle(AbilitySpecHandle);
			UE_LOG(LogTemp, Warning, TEXT("  3  GRANTING ABILITIES"));
			AbilitySet->GiveToAbilitySystem(ASC, /*inout */ &NewEntry.GrantedHandles, Result);
		}
	}


	Result->SpawnEquipmentActors(EquipmentCDO->ActorsToSpawn);

	MarkItemDirty(NewEntry);
	return Result;

}



void FEquipmentList::RemoveEntry(UEquipmentInstance* Instance)
{

	for (auto EntryIt = Entries.CreateIterator(); EntryIt; ++EntryIt)
	{

		FAppliedEquipmentEntry& Entry = *EntryIt;

		if (Entry.Instance == Instance)
		{
			if (ULVAbilitySystemComponent* ASC = GetAbilitySystemComponent())
			{
				Entry.GrantedHandles.TakeFromAbilitySystem(ASC);
			}

			Instance->DestroyEquipmentActors();

			EntryIt.RemoveCurrent();
			MarkArrayDirty();
		}
	}

}

ULVAbilitySystemComponent* FEquipmentList::GetAbilitySystemComponent() const
{
	check(OwnerComponent)
		APlayerCharacterBase* OwningActor = Cast<APlayerCharacterBase>(OwnerComponent->GetOwner());


//	UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OwningActor);
	if (OwningActor->GetAbilitySystemComponent())
	{
		UE_LOG(LogTemp, Warning, TEXT("---- GOT D:! ASC from: EquipmentList OwnerComponent's Owner: %s"), *OwningActor->GetName());

		return Cast<ULVAbilitySystemComponent>(OwningActor->GetAbilitySystemComponent());
	}

	return nullptr;
}

TArray<UEquipmentInstance*> FEquipmentList::GetAllAppliedEquipmentInstances()
{
	TArray<UEquipmentInstance*> Result;

	for (auto &Item : Entries)
	{
		if (Item.Instance)
		{
			Result.Add(Item.Instance);
		}
	
	}
	return Result;
}


////////////////////////////////////////////////////////////////////////////////////////////


UEquipmentManagerComponent::UEquipmentManagerComponent(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer), EquipmentList(this)

{
	bWantsInitializeComponent = true;
}

UEquipmentInstance* UEquipmentManagerComponent::EquipItem(TSubclassOf<UEquipmentDefinition> EquipmentClass)
{

	/* EquipmentDefinition vastaa static dataa */
	UEquipmentInstance* Result = nullptr;

	if (EquipmentClass != nullptr)
	{
		Result = EquipmentList.AddEntry(EquipmentClass);
		if (Result != nullptr)
		{

			Result->OnEquipped();

			/* TODO HERE: ONLINE REPLICATION */
		}
	}


	return Result;
}

void UEquipmentManagerComponent::UnequipItem(UEquipmentInstance* ItemInstance)
{
	if (ItemInstance != nullptr)
	{

		ItemInstance->OnUnequipped();
		EquipmentList.RemoveEntry(ItemInstance);
	}
}

/*
bool UEquipmentManagerComponent::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	return false;
}
*/
/*
void UEquipmentManagerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

*/

void UEquipmentManagerComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UEquipmentManagerComponent::UninitializeComponent()
{
	TArray<UEquipmentInstance*> AllEquipmentInstances;

	for (const FAppliedEquipmentEntry& Entry : EquipmentList.Entries)
	{
		AllEquipmentInstances.Add(Entry.Instance);
	}

	for (UEquipmentInstance* EquipInstance : AllEquipmentInstances)
	{
		UnequipItem(EquipInstance);
	}
	Super::UninitializeComponent();
}

void UEquipmentManagerComponent::ReadyForReplication()
{

	Super::ReadyForReplication();
}

UEquipmentInstance* UEquipmentManagerComponent::GetFirstInstanceOfType(TSubclassOf<UEquipmentInstance> InstanceType)
{

	for ( FAppliedEquipmentEntry& Entry : EquipmentList.Entries)
	{
		if (UEquipmentInstance* Instance = Entry.Instance)
		{
			/*checks pointers type to TSubclass of varaible*/
			if (Instance->IsA(InstanceType))
			{
				return Instance;
			}
		}
	}

	return nullptr;
}

TArray<UEquipmentInstance*> UEquipmentManagerComponent::GetEquipmentInstancesOfType(TSubclassOf<UEquipmentInstance> InstanceType) const
{
	TArray<UEquipmentInstance*> Results;

	for (const FAppliedEquipmentEntry& Entry : EquipmentList.Entries)
	{
		if (UEquipmentInstance* Instance = Entry.Instance)
		{
			if (Instance->IsA(InstanceType))
			{
				Results.Add(Instance);
			}
		}
	}

	return Results;
}

TArray<UEquipmentInstance*> UEquipmentManagerComponent::GetAllEquipmentInstances()
{
	return EquipmentList.GetAllAppliedEquipmentInstances();
}

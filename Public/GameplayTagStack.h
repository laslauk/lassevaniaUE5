// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Containers/Array.h"
#include "Containers/ArrayView.h"
#include "Containers/Map.h"
#include "Containers/Set.h"
#include "Containers/SparseArray.h"
#include "Containers/UnrealString.h"
#include "GameplayTagContainer.h"
#include "HAL/Platform.h"
#include "Net/Serialization/FastArraySerializer.h"
#include "Templates/UnrealTemplate.h"
#include "UObject/Class.h"

#include "GameplayTagStack.generated.h"


struct FGameplayTagStackContainer;
struct FNetDeltaSerializeInfo;


/**
 * 
 */
USTRUCT(BlueprintType)
struct  FGameplayTagStack : public FFastArraySerializerItem
{
	GENERATED_BODY()

public:
	FGameplayTagStack()
	{
	}

	FGameplayTagStack(FGameplayTag InTag, int32 InStackCount): Tag(InTag), StackCount(InStackCount)
	{
	}

	FString GetDebugString() const;


	UPROPERTY()
		FGameplayTag Tag;

	UPROPERTY()
		int32 StackCount = 0;


};


USTRUCT(BlueprintType)
struct FGameplayTagStackContainer : public FFastArraySerializer
{
	GENERATED_BODY()
		
		
		FGameplayTagStackContainer()
	{

	}
public:
	// Adds a specified number of stacks to the tag (does nothing if StackCount is below 1)
	void AddStack(FGameplayTag Tag, int32 StackCount);

	// Removes a specified number of stacks from the tag (does nothing if StackCount is below 1)
	void RemoveStack(FGameplayTag Tag, int32 StackCount);

	// Returns the stack count of the specified tag (or 0 if the tag is not present)
	int32 GetStackCount(FGameplayTag Tag) const
	{
		return TagToCountMap.FindRef(Tag);
	}

	// Returns the stack count of the specified tag (or 0 if the tag is not present)
	int32 GetMaxStackCount(FGameplayTag Tag);


	// Returns true if there is at least one stack of the specified tag
	bool ContainsTag(FGameplayTag Tag) const
	{
		return TagToCountMap.Contains(Tag);
	}

	//~FFastArraySerializer contract
	void PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize);
	void PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize);
	void PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize);
	//~End of FFastArraySerializer contract

	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FGameplayTagStack, FGameplayTagStackContainer>(Stacks, DeltaParms, *this);
	}

	// Replicated list of gameplay tag stacks
	UPROPERTY()
		TArray<FGameplayTagStack> Stacks;

	/* TODO - Note, this used as a tag for base tags when first putting in stacks 
	- NOW using Item AMmo as itself as a item, so item instance will have 
	stack count set when creating it
	
	*/




	// Accelerated list of tag stacks for queries
	/* USED FOR COUNT QUERIES*/
	TMap<FGameplayTag, int32> TagToCountMap;

};


template<>
struct TStructOpsTypeTraits<FGameplayTagStackContainer> : public TStructOpsTypeTraitsBase2<FGameplayTagStackContainer>
{
	enum
	{
		WithNetDeltaSerializer = true,
	};
};

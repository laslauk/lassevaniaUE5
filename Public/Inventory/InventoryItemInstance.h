// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HAL/Platform.h"
#include "../GameplayTagStack.h"
#include "Templates/SubclassOf.h"
#include "UObject/Object.h"
#include "UObject/UObjectGlobals.h"
#include "InventoryItemInstance.generated.h"



struct FFrame;
struct FGameplayTag;
class UInventoryItemFragment;
class UInventoryItemDefinition;
class AItemActorBase;
class UItemStaticData;

class UWorld;

/**
 *  Stacking of items is done with Tag Counts
 */
UCLASS()
class LASSEVANIA_API UInventoryItemInstance : public UObject
{
	GENERATED_BODY()

public:
	UInventoryItemInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~UObject interface
	virtual bool IsSupportedForNetworking() const override { return true; }
	//~End of UObject interface


	// Adds a specified number of stacks to the tag (does nothing if StackCount is below 1)
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = Inventory)
		void AddStatTagStack(FGameplayTag Tag, int32 StackCount);

	// Removes a specified number of stacks from the tag (does nothing if StackCount is below 1)
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = Inventory)
		void RemoveStatTagStack(FGameplayTag Tag, int32 StackCount);

	// Returns the stack count of the specified tag (or 0 if the tag is not present)
	UFUNCTION(BlueprintCallable, Category = Inventory)
		int32 GetStatTagStackCount(FGameplayTag Tag) const;


	// Returns true if there is at least one stack of the specified tag
	UFUNCTION(BlueprintCallable, Category = Inventory)
		bool HasStatTag(FGameplayTag tTag) const;

	TSubclassOf<UInventoryItemDefinition> GetItemDef() const
	{
		return ItemDef;
	}

	void SetItemDef(TSubclassOf<UInventoryItemDefinition> InDef);


	UPROPERTY(/*Replicated*/)
	TSubclassOf<UInventoryItemDefinition> ItemDef;

	 UPROPERTY(/*Replicated*/)
	 FGameplayTagStackContainer StatTags;

	 UFUNCTION(BlueprintCallable, BlueprintPure = false, meta = (DeterminesOutputType = FragmentClass))
	 const UInventoryItemFragment* FindFragmentByClass(TSubclassOf<UInventoryItemFragment> FragmentClass) const;


	 template <typename ResultClass>
	 const ResultClass* FindFragmentByClass() const
	 {
		 return (ResultClass*)FindFragmentByClass(ResultClass::StaticClass());
	 }

	 /* TODO Parempi stackaus systeemi, nyt simple enouffi*/

	 int32 GetStackSize() { return StackSize; }

	
	 /* returns if flowed*/

	 bool AddStackItem(int32 Count, int32& CountOverSize) { 

		 CountOverSize = (StackItemCount + Count) - StackSize;
		 StackItemCount = FMath::Clamp(StackItemCount + Count, 0, StackSize);

		 if (CountOverSize < 0)
		 {
			 CountOverSize = 0;
		}

		 return CountOverSize > 0;
	 }

	 int32 GetStackItemCount() { return StackItemCount; }

	 bool HasFreeStackSlots() { return StackItemCount < StackSize && bIsStackable; }


	 bool GetIsStackable() { return bIsStackable; }

private:

	void SetStackSize(int32 NewStackSize) { StackSize = NewStackSize; }

	 int32 StackSize = 1;
	 int32 StackItemCount = 0; /* initially 0*/

	 bool bIsStackable = false;

	/*

	// Adds a specified number of stacks to the tag (does nothing if StackCount is below 1)
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = Inventory)
	void AddStatTagStack(FGameplayTag Tag, int32 StackCount);

	// Removes a specified number of stacks from the tag (does nothing if StackCount is below 1)
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = Inventory)
	void RemoveStatTagStack(FGameplayTag Tag, int32 StackCount);

	// Returns the stack count of the specified tag (or 0 if the tag is not present)
	UFUNCTION(BlueprintCallable, Category = Inventory)
	int32 GetStatTagStackCount(FGameplayTag Tag) const;

	// Returns true if there is at least one stack of the specified tag
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool HasStatTag(FGameplayTag tTag) const;

	*/



	// The item definition


};

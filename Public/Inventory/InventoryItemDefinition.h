// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"
#include "Internationalization/Text.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Templates/SubclassOf.h"
#include "UObject/Object.h"
#include "UObject/ObjectPtr.h"
#include "UObject/UObjectGlobals.h"
#include "InventoryItemDefinition.generated.h"



class UInventoryItemInstance;
struct FFrame;

/**
 * 
 */



 // Represents a fragment of an item definition
UCLASS(DefaultToInstanced, EditInlineNew, Abstract)
class LASSEVANIA_API UInventoryItemFragment : public UObject
{
	GENERATED_BODY()


public:
	virtual void OnInstanceCreated(UInventoryItemInstance* Instance) const {}
};


//////////////////////////////////////////////////////////////////////





UCLASS(Blueprintable, Const, Abstract)
class UInventoryItemDefinition : public UObject
{
	GENERATED_BODY()

public:

	UInventoryItemDefinition(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Display)
		FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Display)
		int32 StackSize = 1;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Display, Instanced)
		TArray<TObjectPtr<UInventoryItemFragment>> Fragments;


	const UInventoryItemFragment* FindFragmentByClass(TSubclassOf<UInventoryItemFragment> FragmentClass) const;
};


UCLASS()
class UInventoryFunctionLibrary : public UBlueprintFunctionLibrary
{
	
	GENERATED_BODY()

public:
		UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = FragmentClass))
		static const UInventoryItemFragment* FindItemDefinitionFragment(TSubclassOf<UInventoryItemDefinition> ItemDef, TSubclassOf<UInventoryItemFragment> FragmentClass);
};

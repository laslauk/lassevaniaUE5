// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AttributeInfo.generated.h"

USTRUCT(BlueprintType)
struct FLassevaniAttributeInfo
{
	GENERATED_BODY()

public:
		/*which attribute this info is for */

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDescription = FText();


	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.0f;

};


UCLASS()
class LASSEVANIA_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()


public:

	FLassevaniAttributeInfo FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound = false) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray< FLassevaniAttributeInfo> AttributeInformation;
	
};

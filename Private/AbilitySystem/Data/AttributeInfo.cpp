// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/AttributeInfo.h"

FLassevaniAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{

	for (const FLassevaniAttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag.MatchesTag(AttributeTag))
		{
			return Info;
		}


	}


	/* didnt find */
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Tag wasnt found for Attribute tag [%s]"), *AttributeTag.ToString());
	}


	return FLassevaniAttributeInfo();
}

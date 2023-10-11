// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/LassevaniaInputConfig.h"

ULassevaniaInputConfig::ULassevaniaInputConfig()
{




}

const UInputAction* ULassevaniaInputConfig::FindNativeInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{

	for (const FLVInputAction& Action : NativeInputActions)
	{
		/* Check että on valid ja input tag on sama */
		if (Action.InputAction && (Action.InputTag == InputTag))
		{
			return Action.InputAction;
		}

	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find NativeInputAction for InputTag [%s] on InputConfig [%s]."), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;




}

const UInputAction* ULassevaniaInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FLVInputAction& Action : AbilityInputActions)
	{
		if (Action.InputAction && (Action.InputTag == InputTag))
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s] on InputConfig [%s]."), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}

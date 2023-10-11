// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "LassevaniaInputConfig.h"
#include "LVInputComponent.generated.h"

class UEnhancedInputLocalPlayerSubsystem;
/**
 *  IMPORTANT NOTE::::!!!!!!!!!!!!!!!!!!!!!!IMPORTANT!!!!!!!!!!!!IMPORTANT!!!!!!!!!!!!!!!!!!!!!!!
 * 
 * -------- Tämä asetetaan: project settings > Input > Default Input Component class 
 * 
 * !!!!!!!!!IMPORTANT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!IMPORTANT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * 
 */
UCLASS()
class LASSEVANIA_API ULVInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	ULVInputComponent(const FObjectInitializer& ObjectInitializer);

	void AddInputMappings(const ULassevaniaInputConfig* InputConfig, UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const;


	/* native varmaan  jump, liiku, yms*/
	template<class UserClass, typename FuncType>
	void BindNativeAction(const ULassevaniaInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func, bool bLogIfNotFound);


	/* abiity kuten shoot, prone, yell*/
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
	void BindAbilityActions(const ULassevaniaInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, TArray<uint32>& BindHandles);


	void RemoveBinds(TArray<uint32>& BindHandles);

private:
	
};


template<class UserClass, typename FuncType>
void ULVInputComponent::BindNativeAction(const ULassevaniaInputConfig* InputConfig, const FGameplayTag& InputTag,
	ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func, bool bLogIfNotFound)
{

	if (!InputConfig) { return; }
	
	const UInputAction* IA = InputConfig->FindNativeInputActionForTag(InputTag, bLogIfNotFound);
	{
		/* Tämä actually bindaa annetun funktion, eventin tyypin, objektin ja Callback function enahnced inptu systeemii*/
		BindAction(IA, TriggerEvent, Object, Func);
	}

}

template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
void ULVInputComponent::BindAbilityActions(const ULassevaniaInputConfig* InputConfig, UserClass* Object,
	PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, TArray<uint32>& BindHandles)
{

	if (InputConfig == nullptr) { return; }

	/*  InputConfig on datasetti jossa input abilityt ja actionit */
	for (const FLVInputAction& InputAction : InputConfig->AbilityInputActions)
	{

		if (InputAction.InputAction && InputAction.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindHandles.Add(
					BindAction(InputAction.InputAction, ETriggerEvent::Triggered, Object, PressedFunc, InputAction.InputTag).GetHandle()
				);
			}

			if (ReleasedFunc)
			{
				if (ReleasedFunc)
				{
					BindHandles.Add(BindAction(InputAction.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, InputAction.InputTag).GetHandle());
				}
			}
		}


	}




}


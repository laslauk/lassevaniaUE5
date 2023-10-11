// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/LVInputComponent.h"

#include "Containers/Map.h"
#include "EnhancedInputSubsystems.h"
#include "InputCoreTypes.h"
#include "UObject/NameTypes.h"
#include "GameFramework/GameUserSettings.h"
#include "Input/LassevaniaInputConfig.h"

#include "UObject/UnrealNames.h"

ULVInputComponent::ULVInputComponent(const FObjectInitializer& ObjectInitializer)
{
}

void ULVInputComponent::AddInputMappings(const ULassevaniaInputConfig* InputConfig, UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const
{
	if (!InputConfig) { return; }
	if (!InputSubsystem) { return; }

	ULocalPlayer* LocalPlayer = InputSubsystem->GetLocalPlayer<ULocalPlayer>();

	if (!LocalPlayer) { return; }


}





void ULVInputComponent::RemoveBinds(TArray<uint32>& BindHandles)
{
	for (uint32 Handle : BindHandles)
	{
		RemoveBindingByHandle(Handle);
	}
	BindHandles.Reset();

}

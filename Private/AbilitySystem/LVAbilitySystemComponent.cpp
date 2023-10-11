// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/LVAbilitySystemComponent.h"
#include "AbilitySystem/GameplayAbilityBase.h"

ULVAbilitySystemComponent::ULVAbilitySystemComponent(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{

	InputPressedSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();
	InputHeldSpecHandles.Reset();
}

void ULVAbilitySystemComponent::ProcessAbilityInput(float DeltaTime, bool bGamePaused)
{
	static TArray<FGameplayAbilitySpecHandle> AbilitiesToActivate;
	AbilitiesToActivate.Reset();
	
//
// Process all abilities that activate when the input is held.
//
	for (const FGameplayAbilitySpecHandle& SpecHandle : InputHeldSpecHandles)
	{

	}

	/* Input PRESSED*/

	for (const FGameplayAbilitySpecHandle& SpecHandle : InputPressedSpecHandles)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULVAbilitySystemComponent::ProcessAbilityInput PROCESS INPUTY PRESSED HANDLES !"));
	
		if (FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle))
		{
		
			if (AbilitySpec->Ability)
			{
				AbilitySpec->InputPressed = true;


				if (AbilitySpec->IsActive())
				{
					// Ability is active so pass along the input event.
					AbilitySpecInputPressed(*AbilitySpec);
				}
				else
				{
					 UGameplayAbilityBase* AbilityCD0 = CastChecked<UGameplayAbilityBase>(AbilitySpec->Ability);
				
					if (AbilityCD0->GetActivationPolicy() == EAbilityActivationPolicy::OnInputTriggered)
					{
						AbilitiesToActivate.AddUnique(AbilitySpec->Handle);
					
					}
				}
			}
		}
	}

	// Try to activate all the abilities that are from presses and holds.
	// We do it all at once so that held inputs don't activate the ability
	// and then also send a input event to the ability because of the press.
	//
	for (const FGameplayAbilitySpecHandle& AbilitySpecHandle : AbilitiesToActivate)
	{
		
		bool Success = TryActivateAbility(AbilitySpecHandle);
		UE_LOG(LogTemp, Warning, TEXT("---> TryActivateAbility Input %s 2"), *FindAbilitySpecFromHandle(AbilitySpecHandle)->GetDebugString());

		if (!Success)
		{
		//TODO INPURT ABILIT QUE	InputPressedSpecHandlesQue.AddUnique(AbilitySpecHandle);
		}

	}


	//
// Process all abilities that had their input released this frame.
//
	for (const FGameplayAbilitySpecHandle& SpecHandle : InputReleasedSpecHandles)
	{
		if (FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle))
		{
			if (AbilitySpec->Ability)
			{
				AbilitySpec->InputPressed = false;
				UE_LOG(LogTemp, Warning, TEXT("---> AbilitySpecInputReleased Input %s 1"), *AbilitySpec->Ability->GetName());
				if (AbilitySpec->IsActive())
				{
					UE_LOG(LogTemp, Warning, TEXT("---> AbilitySpecInputReleased Input %s 2"), *AbilitySpec->Ability->GetName());
					// Ability is active so pass along the input event.
					AbilitySpecInputReleased(*AbilitySpec);
				}
			}
		}
	}



	InputPressedSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();
}

void ULVAbilitySystemComponent::ClearInputPressedQue()
{
	InputPressedSpecHandlesQue.Empty();
}

void ULVAbilitySystemComponent::OnAbilityEnded(UGameplayAbility* Ability)
{
	UE_LOG(LogTemp, Warning, TEXT("---> OnAbilityEnded 1"));
	if (InputPressedSpecHandlesQue.Num() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("---> OnAbilityEnded 2"));

		for (auto abilitHandle : InputPressedSpecHandlesQue)
		{

			UE_LOG(LogTemp, Warning, TEXT("---> OnAbilityEnded 3"));
			if (abilitHandle.IsValid())
			{
			
				FGameplayAbilitySpec* spec = FindAbilitySpecFromHandle(abilitHandle);


				if (spec)
				{
					if(spec->IsActive())
					UE_LOG(LogTemp, Warning, TEXT("---> FOUND SEPC and its active  4.1"));

				}

				UE_LOG(LogTemp, Warning, TEXT("---> OnAbilityEnded 4"));
				InputPressedSpecHandles.AddUnique(abilitHandle);
				
			
			}

		}
	}
	InputPressedSpecHandlesQue.Empty();
}

void ULVAbilitySystemComponent::ClearAbilityInput()
{
}

void ULVAbilitySystemComponent::TryActivateAbilitiesOnSpawn()
{
}

void ULVAbilitySystemComponent::AbilitySpecInputPressed(FGameplayAbilitySpec& Spec)
{
	Super::AbilitySpecInputPressed(Spec);
}

void ULVAbilitySystemComponent::AbilitySpecInputReleased(FGameplayAbilitySpec& Spec)
{
	Super::AbilitySpecInputReleased(Spec);
}

void ULVAbilitySystemComponent::CancelInputActivatedAbilities(bool bReplicateCancelAbility)
{
}

void ULVAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
//	UE_LOG(LogTemp, Warning, TEXT("AbilityInputTagPressed 1"));
	if (InputTag.IsValid())
	{
		

	//	UE_LOG(LogTemp, Warning, TEXT("AbilityInputTagPressed 2"));
		for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
		{
			UE_LOG(LogTemp, Warning, TEXT("AbilityInputTagPressed 3"));

			if (AbilitySpec.Ability)
			{
		//		UE_LOG(LogTemp, Warning, TEXT("AbilityInputTagPressed 4"));
			}
		//	UE_LOG(LogTemp, Warning, TEXT("AbilitySpec: %s"), *AbilitySpec.Ability.GetFullName());
		//	UE_LOG(LogTemp, Warning, TEXT("Inputtag: %s"), *InputTag.ToString());
			 
			if ((AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag)))
			{
			//	UE_LOG(LogTemp, Warning, TEXT("AbilityInputTagPressed 5"));
			}


			if (AbilitySpec.Ability && (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag)))
			{

				//UE_LOG(LogTemp, Warning, TEXT("AbilityInputTagPressed adding uniguqes -->"));

				UE_LOG(LogTemp, Warning, TEXT("AbilityInputTagPressed 3 - before unique add"));
				/* Siell‰ on jo t‰m‰ ability, pistet‰‰n cueen?*/

				if (AbilitySpec.IsActive())
				{

					UE_LOG(LogTemp, Warning, TEXT("AbilityInputTagPressed 4 - added to cue"));
					InputPressedSpecHandlesQue.AddUnique(AbilitySpec.Handle);

				}


				 InputPressedSpecHandles.AddUnique(AbilitySpec.Handle);
				 InputHeldSpecHandles.AddUnique(AbilitySpec.Handle);
			}
		}
	}
}

void ULVAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{

	if (InputTag.IsValid())
	{
		for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
		{
			if (AbilitySpec.Ability && (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag)))
			{
				InputReleasedSpecHandles.AddUnique(AbilitySpec.Handle);
				InputHeldSpecHandles.Remove(AbilitySpec.Handle);
			}
		}
	}
}

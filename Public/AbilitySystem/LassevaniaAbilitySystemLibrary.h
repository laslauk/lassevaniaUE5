// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include  "Data/CharacterClassInfo.h"
#include "LassevaniaAbilitySystemLibrary.generated.h"

class  UAbilitySystemComponent;
class UOverlayWidgetController;
/**
 * 
 */
UCLASS()
class LASSEVANIA_API ULassevaniaAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/* static functyion doesnt exist in the game world, requires world context*/
	/* called from widget*/
	UFUNCTION(BlueprintPure,Category="LassevaniaAbilitySystemLibrary | WidgetController")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "LassevaniaAbilitySystemLibrary | WidgetController")
		static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);


	UFUNCTION(BlueprintCallable, Category = "LassevaniaAbilitySystemLibrary | CharacterClassDefaults")
	static void InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC);
	

	static UCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);

};

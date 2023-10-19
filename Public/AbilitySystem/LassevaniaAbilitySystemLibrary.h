// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include  "Data/CharacterClassInfo.h"
#include "LassevaniaAbilitySystemLibrary.generated.h"

class  UAbilitySystemComponent;
class UOverlayWidgetController;
struct FGameplayEffectContextHandle;
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


	/* Collisions checks */

	UFUNCTION(BlueprintPure, Category = "LassevaniaAbilitySystemLibrary | Collision Attack")
		static void GetTargetsWithinBoxCollision(const UObject* WorldContextObject, TArray<AActor*>& OutOverllappingActors, AActor* OwnerActor, FVector InBoxExtend, const FVector& StartOrigin, ECollisionChannel TraceChannel);




	UFUNCTION(BlueprintPure, Category = "LassevaniaAbilitySystemLibrary | GameplayEffects")
		static FGameplayEffectSpecHandle CreateDamageEffectSpec(const FGameplayEffectContextHandle& EffectContextHandle, AActor* OwnerActor, 
			TSubclassOf<UGameplayEffect> DamageEffectClass, TMap<FGameplayTag, FScalableFloat> DamageTypes);


	/* Gameplay effect context */

	UFUNCTION(BlueprintPure, Category = "LassevaniaAbilitySystemLibrary | GameplayEffects")
	static bool IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category = "LassevaniaAbilitySystemLibrary | GameplayEffects")
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintCallable, Category = "LassevaniaAbilitySystemLibrary | GameplayEffects")
	static void SetIsBlockedHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit);

	UFUNCTION(BlueprintCallable, Category = "LassevaniaAbilitySystemLibrary | GameplayEffects")
	static void SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit);


	UFUNCTION(BlueprintCallable, Category = "LassevaniaAbilitySystemLibrary | GameplayEffects")
	static void SetDamageCasuesHitStun(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bCausesHitStun);


	UFUNCTION(BlueprintPure, Category = "LassevaniaAbilitySystemLibrary | GameplayEffects")
	static bool IsDamageCausesHitStun(const FGameplayEffectContextHandle& EffectContextHandle);


	UFUNCTION(BlueprintCallable, Category = "LassevaniaAbilitySystemLibrary | GameplayEffects")
	static void SetIsParryableAbility(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsParryable);

	UFUNCTION(BlueprintPure, Category = "LassevaniaAbilitySystemLibrary | GameplayEffects")
	static bool IsParryable(const FGameplayEffectContextHandle& EffectContextHandle);


	UFUNCTION(BlueprintPure, Category = "LassevaniaAbilitySystemLibrary | Combat Gameplay Mechanics")
	static bool IsTargetHostile(AActor* Actor, AActor* OtherActor);

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "LassevaniaAbilityTypes.generated.h"

/*
	UObjects have StaticClass() , returns UClass,
	Engine generates Uclass for each Uobject for REFLECXTIOn system
	Struct version - GetScriptStruct() returns UScriptStruct, for reflection structs
	StaticStruct() equivalent fro structs

*/



USTRUCT()
struct FLassevaniaGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:

	/* TODO damage effect elemental type e.g*/

	bool IsCriticalHit() const {

		UE_LOG(LogTemp, Warning, TEXT(" IsCriticalHit EFFECT CONTEXT: %s"), bIsCriticalHit ? TEXT("[ TRUE ]") : TEXT("xx False xx"));
		return bIsCriticalHit;
	}


	bool IsBlockedHit() const { return bIsBlockedHit; }


	bool IsParryableAbility() const { return IsParryable; }

	void SetIsParryableAbility(bool bInIsParryalbe) { IsParryable = bInIsParryalbe; };

	void SetIsCriticalHit(bool bInIsCriticalHit);

	bool  IsDamageCausesHitStun() const  { return bDamageCausesHitStun; }

	void SetDamageCausesHitStun(bool bNewCausesHitStun) { bDamageCausesHitStun = bNewCausesHitStun; };

	void SetIsBlockingHit(bool bInBlock) { bIsBlockedHit = bInBlock; }


	/* ------from FGameplayEffectContext Interface--------- */

	/** Creates a copy of this context, used to duplicate for later modifications */
	virtual FLassevaniaGameplayEffectContext* Duplicate() const override
	{
		FLassevaniaGameplayEffectContext* NewContext = new FLassevaniaGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}


	virtual UScriptStruct* GetScriptStruct() const override;

	/* serialization definition, if sending across network or saving*/
//	virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;
	/* --------from FGameplayEffectContext Interface---------- */





protected:
	/* These properties used by system such as UI damage floating widget component */
private:
	UPROPERTY()
		bool bIsCriticalHit = false;
	UPROPERTY()
		bool bIsBlockedHit = false;
	UPROPERTY()
		bool bDamageCausesHitStun = true;
	UPROPERTY()
	bool IsParryable = true;
};


template<>
struct TStructOpsTypeTraits<FLassevaniaGameplayEffectContext> :
	public TStructOpsTypeTraitsBase2< FLassevaniaGameplayEffectContext>
{
	enum
	{
	//	WithNetSerializer = true,
		WithCopy = true
	};
};
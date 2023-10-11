// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "GameplayTagContainer.h"

#include "Engine/DataTable.h"
#include "LassevaniaCommonTypes.generated.h"
/**
 * 
 */
class AItemActorBase;
class UGameplayAbilityBase;
class UGameplayEffect;
class UPaperSprite;
class ULassevaniaAbilitySet;

#define LVPRINT(str, val) UE_LOG(LogTemp, Warning, TEXT(str "%s"), val)

/* Channelit omaan headeriin TODO*/
#define Lassevania_TraceChannel_Interaction ECC_GameTraceChannel4
#define Lassevania_TraceChannel_HitBoxTrace ECC_GameTraceChannel2


USTRUCT(BlueprintType)
struct FCharacterData
{
	GENERATED_USTRUCT_BODY();


/*
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GAS")
	TArray<TSubclassOf<class UGameplayEffect>> EffectsDefault;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GAS")
	TArray<TSubclassOf<class UGameplayAbilityBase>> AbilitiesDefault;
*/
};

USTRUCT(BlueprintType)
struct FDialogSpeakerData: public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DialogSystem")
	FName Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DialogSystem")
	UTexture2D* Image;
};


USTRUCT(BlueprintType)
struct FDialogContentData : public FTableRowBase
{

	GENERATED_USTRUCT_BODY();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DialogSystem")
	int32 Index;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DialogSystem")
	FText TextContent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DialogSystem")
	FGameplayTag RequiredTagFlag;

};


UCLASS(BlueprintType, Blueprintable)
class UItemStaticData : public UObject
{
	GENERATED_BODY()


public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName Name;

	/* Actor class to spawn in the world */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class AItemActorBase> ItemActorClass;

	// Gameplay ability sets to grant when this is equipped
	UPROPERTY(EditDefaultsOnly, Category = Equipment)
	TArray<TObjectPtr<const ULassevaniaAbilitySet>> AbilitySetsToGrant;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bCanBeEquipped = true;

	/* NOTE::::::::::: REPLACED WITH AbilitySetsToGrant --- INCLUDES EFFECTS + ATTRIBUTES + ABILITYY!!!
	* THIS WILL MAP THE INPUT to INPUTTAG -- USE THAT!!!!! 
	* 
	* 
	//how to use weapons == weapons grant an USE (such as melee, shoot) ability to use the weapon
	UPROPERTY(EditDefaultsOnly, BLueprintReadOnly)
	TArray<TSubclassOf<UGameplayAbility>> GrantedAbilities; //item grants abilities

	//effects we apply to character when we equip it
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<UGameplayEffect>> OngoingEffects;

	*/


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FGameplayTag> InventoryTags;

	//1 item instance can have multiple items
	UPROPERTY(EditDefaultsOnly, Blueprintable)
	int32 MaxStackCount = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UPaperSprite* ActorSprite;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAnimMontage* AttackMontage;

		/* TODO - ASEEN MUKAAN MENEE PELAAJAN ANIMAATIO T/ tai 2D spritet??*/

};


UCLASS(BlueprintType, Blueprintable)
class UGearItemStaticData : public UItemStaticData
{
public:
	GENERATED_BODY()


};





UCLASS(BlueprintType, Blueprintable)
class UWeaponStaticData : public UItemStaticData
{
	GENERATED_BODY()

public:

	//effect to apply damage
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TSubclassOf<UGameplayEffect> DamageEffect;


	UPROPERTY(EditDefaultsOnly, BLueprintReadOnly)
		float FireRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float BaseDamage;

	//Attack soundit on played by itemActor
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		USoundBase* AttackSound;

};



UENUM(BlueprintType)
enum class EItemState : uint8
{
	None UMETA(DisplayName = "None"),
	Equipped UMETA(DisplayName = "Equipped"),
	Dropped UMETA(DisplayName = "Dropped"),
};


UENUM(BlueprintType)
enum class EItemEquipmentSlot : uint8
{
	None UMETA(DisplayName = "None"),
	Head UMETA(DisplayName = "Head"),
	TwoHand UMETA(DisplayName = "TwoHanded"),
	Finger UMETA(DisplayName = "Finger"),
	Chest UMETA(DisplayName = "Chest")
};



USTRUCT(BlueprintType)
struct FItemStats
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "InventoryItem")
	int32 Damage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "InventoryItem")
	int32 BuyValue;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "InventoryItem")
	int32 SellValue;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "InventoryItem")
	FText Description;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "InventoryItem")
	FText Title;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "InventoryItem")
	EItemEquipmentSlot EquipmentSlot;
};


USTRUCT(BlueprintType)
struct FInventoryWidgetSlotData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "InventoryItem")
	TSubclassOf<AItemActorBase> ItemClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "InventoryItem")
	int32 Count;
};

UENUM(BlueprintType)
enum class EDialogSpeakerSide : uint8
{
	Left UMETA(DisplayName = "Left"),
	Right UMETA(DisplayName = "Right"),
};


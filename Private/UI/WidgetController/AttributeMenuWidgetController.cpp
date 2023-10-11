// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AttributeSetBase.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "LassevaniaGameplayTags.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{

	UAttributeSetBase* AS = CastChecked<UAttributeSetBase>(AttributeSet);

	for (auto& Pair : AS->TagsToAttributesMap)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this, Pair, AS](const FOnAttributeChangeData& Data)
			{
			
				BroadcastAttributeInfo(Pair.Key, Pair.Value());
			});
	}

}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAttributeSetBase* AS = CastChecked< UAttributeSetBase>(AttributeSet);

	check(AttributeInfoDataAsset);
	
	/*
	
	FLassevaniAttributeInfo Info = AttributeInfoDataAsset->FindAttributeInfoForTag(FLassevaniaGameplayTags::Get().Attributes_Primary_Strength, true);
	Info.AttributeValue = AS->GetStrength();
	AttributeInfoDelegate.Broadcast(Info);

	*/


	for (auto& Pair : AS->TagsToAttributesMap)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());

		

	}

}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute)
{
	FLassevaniAttributeInfo Info = AttributeInfoDataAsset->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}

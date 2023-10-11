// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Math/Color.h"
#include "DialogEntryObjectWidget.generated.h"

/**
 * 
 */
UCLASS()
class LASSEVANIA_API UDialogEntryObjectWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:

	virtual bool Initialize() override;

	//Use initialize
//	UDialogEntryObjectWidget(const FObjectInitializer& object_initializer);

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY(EditANywhere, BlueprintReadWrite, Category = "Dialogue", meta = (AllowPrivateAccess = true))
	class UTextBlock* ReplyText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue", meta = (AllowPrivateAccess = true))
	class UButton* ReplyButton;


	FLinearColor HoveredColor;
	FSlateColor DefaultColor;

	class UDialogReplyListObject* DialogObject;

	UFUNCTION()
	void OnHoveredBegin();


	UFUNCTION()
		void OnHoveredEnd();

	UFUNCTION()
		void DialogButtonClicked();

private:
	
};

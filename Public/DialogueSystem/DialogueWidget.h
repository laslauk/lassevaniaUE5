// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../LassevaniaCommonTypes.h"
#include "DialogueWidget.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FExitDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpeakFinishedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReplyFinishedDelegate, int32, ReplyIndex);

/**
 * 
 */
UCLASS()
class LASSEVANIA_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/* Inherited from UUserWidgetr */


	/* Inherited  UUserWidgetr */


	// virtual FEventReply OnMouseButtonDown(FGeometry MyGeometry, const FPointerEvent& MouseEvent) ;
	//virtual OnMouseButtonDown(UGeometryStru)


	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UFUNCTION(BlueprintCallable)
	void ExitDialogue();

	UFUNCTION(BlueprintCallable)
	void Speak(FText DialogText, FDialogSpeakerData SpeakerData, EDialogSpeakerSide Side);

	UFUNCTION(BlueprintCallable)
	void SetSpeaker(EDialogSpeakerSide Side, UTexture2D* Image, FName SpeakerName);

	UFUNCTION(BlueprintCallable)
	void Reply(TArray<FDialogContentData> Replies);

	UFUNCTION(BlueprintCallable)
	void SetDialogState(bool bIsReply);

	UFUNCTION(BlueprintCallable)
	void OnClickedReply(class UDialogReplyListObject* ReplyObject);


	/* EventDispatchers / Delegates */
	/* To add callback function, call AddDynamic on this delegate*/
	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FExitDelegate OnExit;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnSpeakFinishedDelegate OnSpeakFinished;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnReplyFinishedDelegate OnReplyFinished;




	void UnBindFromOnReplyFinished();

	/* Widget Blueprint Element bindings */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* ImageIconLeft;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UListView* RepliesList;
	

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* ImageIconRight;


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* NameLeft;


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* NameRigth;


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class USizeBox* ReplySizebox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* NPCSpeakText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class USizeBox* SpeakSizeBox;
	/* END Widget Blueprint Element bindings */



	UPROPERTY(EditAnywhere)
	bool bIsReplyDialogue;


private:
	
};

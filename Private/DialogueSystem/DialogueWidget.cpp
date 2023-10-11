// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueSystem/DialogueWidget.h"
#include "Delegates/DelegateBase.h"
#include "Blueprint/WidgetBlueprintLibrary.h" /* MakeBrushFromTexture()*/
#include "Components/TextBlock.h"
#include "Components/Image.h"


#include "DialogueSystem/DialogReplyListObject.h"


#include "Components/ListView.h"
#include "Components/SizeBox.h"








 FReply UDialogueWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	
	 if (!bIsReplyDialogue)
	 {
		 bool bClicked = InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton);
		 if (bClicked)
		 {


			 if (OnSpeakFinished.IsBound())
			 {
				 UE_LOG(LogTemp, Warning, TEXT("OnSpeakFinished ON BOUND!! lets broadcast"));

			 }

			 OnSpeakFinished.Broadcast();
			 UE_LOG(LogTemp, Warning, TEXT("GAYYYYYYY"));
		 }
	 }

	 return FReply::Handled();

}



void UDialogueWidget::ExitDialogue()
{
	OnExit.Broadcast();
}

void UDialogueWidget::Speak(FText DialogText, FDialogSpeakerData SpeakerData, EDialogSpeakerSide Side)
{
	NPCSpeakText->SetText(DialogText);
	SetDialogState(false /*isReply */);
	SetSpeaker(Side, SpeakerData.Image, SpeakerData.Name);

}

void UDialogueWidget::SetSpeaker(EDialogSpeakerSide Side, UTexture2D* Image, FName SpeakerName)
{


	FSlateBrush Brush = UWidgetBlueprintLibrary::MakeBrushFromTexture(Image);


	switch (Side)
	{
	case EDialogSpeakerSide::Left:
	{
		ImageIconLeft->SetBrush(Brush);
		NameRigth->SetVisibility(ESlateVisibility::Hidden);
		NameLeft->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		NameLeft->SetText(FText::FromName(SpeakerName));
		ImageIconLeft->SetOpacity(1.f);
		ImageIconRight->SetOpacity(0.2f);
		break;
	}
	case EDialogSpeakerSide::Right:
	{
		ImageIconRight->SetBrush(Brush);
		NameLeft->SetVisibility(ESlateVisibility::Hidden);
		NameRigth->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		NameRigth->SetText(FText::FromName(SpeakerName));
		ImageIconLeft->SetOpacity(0.2f);
		ImageIconRight->SetOpacity(1.f);
		break;

	}
	default: break;

	}
}

void UDialogueWidget::Reply(TArray<FDialogContentData> Replies) 
{
	/* Clear visible replies if exists*/
	RepliesList->ClearListItems();
	SetDialogState(true);

	for (auto ReplyData : Replies)
	{
		/* Creating Objects in UE, use UObject factory method for garbage collection, reflection! no basic c++ style*/
		/* TODO: Check if possible to call specific constructor or add its parameters?*/
		UDialogReplyListObject* ListObj = NewObject<UDialogReplyListObject>();
		ListObj->Text = ReplyData.TextContent;
		ListObj->Index = ReplyData.Index;

	//	UStaticMeshComponent* comp = NewNamedObject<UStaticMeshComponent>(this, *node->GetAttribute("name"));
		ListObj->OnClicked.AddDynamic(this, &UDialogueWidget::OnClickedReply);
		RepliesList->AddItem(ListObj);
	}

}


void UDialogueWidget::SetDialogState(bool bIsReply)
{
	bIsReplyDialogue = bIsReply;
	/* Speak mode*/
	if (!bIsReplyDialogue)
	{
		UE_LOG(LogTemp, Warning, TEXT(" Setting Dialogue Mode: -- SPEAK -- "));
		ReplySizebox->SetVisibility(ESlateVisibility::Collapsed);
		SpeakSizeBox->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}

	/* Reply mode */
	else
	{
		UE_LOG(LogTemp, Warning, TEXT(" Setting Dialogue Mode: -- Reply  -- "));
		ReplySizebox->SetVisibility(ESlateVisibility::Visible);
		SpeakSizeBox->SetVisibility(ESlateVisibility::Collapsed);

	}

}

void UDialogueWidget::OnClickedReply(UDialogReplyListObject* ReplyObject)
{
	UE_LOG(LogTemp, Warning, TEXT(" UDialogueWidget::OnClickedReply(UDialogReplyListObject* ReplyObject) "));
	OnReplyFinished.Broadcast(ReplyObject->Index);
}

void UDialogueWidget::UnBindFromOnReplyFinished()
{

	OnReplyFinished.Clear();
}

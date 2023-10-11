// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueSystem/DialogEntryObjectWidget.h"
#include "Components/Button.h"

#include "DialogueSystem/DialogReplyListObject.h"
#include "Components/TextBlock.h"




void UDialogEntryObjectWidget::DialogButtonClicked()
{

	if (DialogObject)
	{

		UE_LOG(LogTemp, Warning, TEXT(" Clicked button UDialogEntryObjectWidget, time to broadcast "));
		DialogObject->OnClicked.Broadcast(DialogObject);
	}
}


void UDialogEntryObjectWidget::OnHoveredBegin()
{
	if (ReplyText)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hover started inx: %d"), DialogObject->Index);
		FSlateColor Color(HoveredColor);
		ESlateColorStylingMode Mode = ESlateColorStylingMode::UseColor_Specified;

		ReplyText->SetColorAndOpacity(Color);
	}
}

void UDialogEntryObjectWidget::OnHoveredEnd()
{
	if (ReplyText)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hover end inx: %d"), DialogObject->Index);
		ReplyText->SetColorAndOpacity(DefaultColor);
	}
}


bool UDialogEntryObjectWidget::Initialize()
{
	if (Super::Initialize())
	{

		UE_LOG(LogTemp, Warning, TEXT(" UDialogEntryObjectWidget Constrcutor "));

		if (ReplyText)
		{
			DefaultColor = ReplyText->GetColorAndOpacity();
		}


		if (ReplyButton)
		{
			UE_LOG(LogTemp, Warning, TEXT(" UDialogEntryObjectWidget Constrcutor -- ReplyButton set"));
			ReplyButton->OnHovered.AddDynamic(this, &UDialogEntryObjectWidget::OnHoveredBegin);
			ReplyButton->OnUnhovered.AddDynamic(this, &UDialogEntryObjectWidget::OnHoveredEnd);
			ReplyButton->OnClicked.AddDynamic(this, &UDialogEntryObjectWidget::DialogButtonClicked);
		}


		return true;
	}

	else
	{
		return false;
	}
}

void UDialogEntryObjectWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	DialogObject = Cast<UDialogReplyListObject>(ListItemObject);

	if (DialogObject)
	{
		UE_LOG(LogTemp, Warning, TEXT("Moro --- DialogText: %s"), *DialogObject->Text.ToString());

		if (!(DialogObject->Text.EqualTo(FText::FromString("[-]"), ETextComparisonLevel::Quinary)))
		{
			UE_LOG(LogTemp, Warning, TEXT("---- Not equal tesxts!"));
			ReplyText->SetText(DialogObject->Text);


		}
		else
		{
		

			SetVisibility(ESlateVisibility::Collapsed);
		}

	}







}


// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MapMenuWidget.h"

FReply UMapMenuWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::M || InKeyEvent.GetKey() == EKeys::Escape)
	{
		SetVisibility(ESlateVisibility::Collapsed);
		GetOwningPlayer()->SetShowMouseCursor(false);

		FInputModeGameOnly InputMode;
		GetOwningPlayer()->SetInputMode(InputMode);
	}

	return FReply::Handled();
}


void UMapMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetIsFocusable(true);
}
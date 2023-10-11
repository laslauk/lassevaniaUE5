// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UserWidgetBase.h"

void UUserWidgetBase::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();

}

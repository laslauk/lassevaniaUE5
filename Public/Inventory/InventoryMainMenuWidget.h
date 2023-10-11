// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryMainMenuWidget.generated.h"

/**
 * https://www.reddit.com/r/unrealengine/comments/v72hq1/how_to_properly_send_input_to_widgets/
 * 
 * Basically "game and ui" mode is fine, it will turn to game when you click on the widget 
 
 space that have no collisions or outside of widget space, so if you want to make widgets to

 always get focus, then make widget background to register your clicks even with no events, 
 
 you can just add a "border" to your widget background with "visible" so it will override your 
 
 clicks. Also "OnMouseButtonDown" you can use mouse capture for widget handle, so it will capture 
 the widget focus while your mouse is down, and release capture on "MouseButtonUp" hope it helps.
 * 
 */
UCLASS()
class LASSEVANIA_API UInventoryMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	

	
  virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) ;

	virtual void NativeConstruct() override;

	class UInventoryComponent* GetInventoryComponent();
};

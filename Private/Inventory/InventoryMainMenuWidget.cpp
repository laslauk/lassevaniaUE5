// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryMainMenuWidget.h"
#include "PlayerControllerBase.h"
#include "LassevaniaGameStatics.h"
#include "Inventory/InventoryComponent.h"


 FReply UInventoryMainMenuWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{

	 if (InKeyEvent.GetKey() == EKeys::I || InKeyEvent.GetKey() == EKeys::Escape)
	 {

	
		 UInventoryComponent* InventoryComp = GetInventoryComponent();
		 if (GetInventoryComponent())
		 {
			 if (InventoryComp->bIsMenuWidgetOpen)
			 {
				 InventoryComp->SetShowInventoryMenu(EInventoryMenuVisibility::Hide);
			 }
		 }

	 }

	return FReply::Handled();
} 


 void UInventoryMainMenuWidget::NativeConstruct()
 {
	 Super::NativeConstruct();
	 /* BIND DELEGATES HERE*/
	 UE_LOG(LogTemp, Warning, TEXT("asd cosntuctor"));

	// bIsFocusable = true; jos haluu k‰ytt‰‰ enhanced input niin pit‰‰ olla focused
 }


 UInventoryComponent* UInventoryMainMenuWidget::GetInventoryComponent()
 {
	 return ULassevaniaGameStatics::GetPlayerInventoryComponent(GetWorld());
 }

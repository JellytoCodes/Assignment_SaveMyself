// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialManagerWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UTutorialManagerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//InputMode 전환
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if(PC)
	{
		FInputModeUIOnly inputMode;
		inputMode.SetWidgetToFocus(TakeWidget());
		inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

		PC->SetInputMode(inputMode);
		PC->bShowMouseCursor = true;
	}

	if(ButtonClose) ButtonClose->OnClicked.AddDynamic(this, &UTutorialManagerWidget::OnCloseClicked);
}

void UTutorialManagerWidget::OnCloseClicked()
{
	UGameplayStatics::OpenLevel(this, FName("Stage_01"));
}

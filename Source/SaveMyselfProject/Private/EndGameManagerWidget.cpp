// Fill out your copyright notice in the Description page of Project Settings.

#include "EndGameManagerWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UEndGameManagerWidget::NativeConstruct()
{
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

	if(ButtonTitle) ButtonTitle->OnClicked.AddDynamic(this, &UEndGameManagerWidget::OnTitleClicked);
}

void UEndGameManagerWidget::OnTitleClicked()
{
	ButtonTitle->SetIsEnabled(false);

	RemoveFromParent();

	UGameplayStatics::OpenLevel(this, TEXT("GameTitle"));
	UGameplayStatics::DeleteGameInSlot(TEXT("DefenseSaveSlot"), 0);
}

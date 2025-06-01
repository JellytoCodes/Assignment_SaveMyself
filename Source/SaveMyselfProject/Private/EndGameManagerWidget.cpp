// Fill out your copyright notice in the Description page of Project Settings.

#include "EndGameManagerWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UEndGameManagerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//InputMode 전환
	FInputModeUIOnly inputMode;
	inputMode.SetWidgetToFocus(nullptr);
	inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if(PC)
	{
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

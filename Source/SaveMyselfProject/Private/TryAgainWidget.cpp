// Fill out your copyright notice in the Description page of Project Settings.

#include "TryAgainWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SaveMyselfGameInstance.h"
#include "DefenseCharacter.h"
#include "SaveHelper.h"

void UTryAgainWidget::NativeConstruct()
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
	}

	if(ButtonRetry && ImageRetry)
	{
		ImageRetry->SetVisibility(ESlateVisibility::Hidden);

		ButtonRetry->OnClicked.AddDynamic(this, &UTryAgainWidget::OnRetryClicked);
		ButtonRetry->OnHovered.AddDynamic(this, &UTryAgainWidget::OnRetryHovered);
		ButtonRetry->OnUnhovered.AddDynamic(this, &UTryAgainWidget::OnRetryUnhovered);
	}

	if(ButtonQuit && ImageQuit)
	{
		ImageQuit->SetVisibility(ESlateVisibility::Hidden);

		ButtonQuit->OnClicked.AddDynamic(this, &UTryAgainWidget::OnQuitClicked);
		ButtonQuit->OnHovered.AddDynamic(this, &UTryAgainWidget::OnQuitHovered);
		ButtonQuit->OnUnhovered.AddDynamic(this, &UTryAgainWidget::OnQuitUnhovered);
	}
}

void UTryAgainWidget::OnRetryClicked()
{
	if(UGameplayStatics::DoesSaveGameExist(TEXT("DefenseSaveSlot"), 0))
	{
		UGameplayStatics::OpenLevel(this, USaveHelper::LoadStageData());
	}
}

void UTryAgainWidget::OnRetryHovered()
{
	ImageRetry->SetVisibility(ESlateVisibility::Visible);
}

void UTryAgainWidget::OnRetryUnhovered()
{
	ImageRetry->SetVisibility(ESlateVisibility::Hidden);
}

void UTryAgainWidget::OnQuitClicked()
{
	auto PC = UGameplayStatics::GetPlayerController(this, 0);
	if(!PC) return;

	UKismetSystemLibrary::QuitGame(this, PC, EQuitPreference::Quit, true);
}

void UTryAgainWidget::OnQuitHovered()
{
	ImageQuit->SetVisibility(ESlateVisibility::Visible);
}

void UTryAgainWidget::OnQuitUnhovered()
{
	ImageQuit->SetVisibility(ESlateVisibility::Hidden);
}

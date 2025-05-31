// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SaveMyselfGameInstance.h"
#include "SaveHelper.h"
#include "DefenseHUD.h"

void UPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//InputMode ÀüÈ¯
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if(PC)
	{
		FInputModeUIOnly inputMode;
		inputMode.SetWidgetToFocus(TakeWidget());
		inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

		PC->SetInputMode(inputMode);
		PC->bShowMouseCursor = true;

		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}

	if(ButtonContinue && ImageContinue) 
	{
		ImageContinue->SetVisibility(ESlateVisibility::Hidden);

		ButtonContinue->OnClicked.AddDynamic(this, &UPauseWidget::OnContinueClicked);
		ButtonContinue->OnHovered.AddDynamic(this, &UPauseWidget::OnContinueHovered);
		ButtonContinue->OnUnhovered.AddDynamic(this, &UPauseWidget::OnContinueUnhovered);
	}

	if(ButtonRetry && ImageRetry) 
	{
		ImageRetry->SetVisibility(ESlateVisibility::Hidden);

		ButtonRetry->OnClicked.AddDynamic(this, &UPauseWidget::OnRetryClicked);
		ButtonRetry->OnHovered.AddDynamic(this, &UPauseWidget::OnRetryHovered);
		ButtonRetry->OnUnhovered.AddDynamic(this, &UPauseWidget::OnRetryUnhovered);
	}

	if(ButtonTitleMenu && ImageTitleMenu)
	{
		ImageTitleMenu->SetVisibility(ESlateVisibility::Hidden);

		ButtonTitleMenu->OnClicked.AddDynamic(this, &UPauseWidget::OnTitleMenuClicked);
		ButtonTitleMenu->OnHovered.AddDynamic(this, &UPauseWidget::OnTitleMenuHovered);
		ButtonTitleMenu->OnUnhovered.AddDynamic(this, &UPauseWidget::OnTitleMenuUnhovered);
	}

	if(ButtonQuit && ImageQuit)
	{
		ImageQuit->SetVisibility(ESlateVisibility::Hidden);

		ButtonQuit->OnClicked.AddDynamic(this, &UPauseWidget::OnQuitClicked);
		ButtonQuit->OnHovered.AddDynamic(this, &UPauseWidget::OnQuitHovered);
		ButtonQuit->OnUnhovered.AddDynamic(this, &UPauseWidget::OnQuitUnhovered);
	}
}

void UPauseWidget::OnContinueClicked()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if(PC)
	{
		PC->SetInputMode(FInputModeGameOnly());
		PC->bShowMouseCursor = false;
		
		UGameplayStatics::SetGamePaused(GetWorld(), false);
	}

	OnPauseWidgetClosed.Broadcast();
}

void UPauseWidget::OnRetryClicked()
{
	if(UGameplayStatics::DoesSaveGameExist(TEXT("DefenseSaveSlot"), 0))
	{
		UGameplayStatics::OpenLevel(this, USaveHelper::LoadStageData());
	}
}

void UPauseWidget::OnTitleMenuClicked()
{
	UGameplayStatics::OpenLevel(this, FName("GameTitle"));
}

void UPauseWidget::OnQuitClicked()
{
	auto PC = UGameplayStatics::GetPlayerController(this, 0);
	if(!PC) return;

	UKismetSystemLibrary::QuitGame(this, PC, EQuitPreference::Quit, true);
}

void UPauseWidget::OnContinueHovered() { ImageContinue->SetVisibility(ESlateVisibility::Visible); }
void UPauseWidget::OnContinueUnhovered() { ImageContinue->SetVisibility(ESlateVisibility::Hidden); }

void UPauseWidget::OnRetryHovered() { ImageRetry->SetVisibility(ESlateVisibility::Visible); }
void UPauseWidget::OnRetryUnhovered() { ImageRetry->SetVisibility(ESlateVisibility::Hidden); }

void UPauseWidget::OnTitleMenuHovered()  { ImageTitleMenu->SetVisibility(ESlateVisibility::Visible); }
void UPauseWidget::OnTitleMenuUnhovered() { ImageTitleMenu->SetVisibility(ESlateVisibility::Hidden); }

void UPauseWidget::OnQuitHovered()  { ImageQuit->SetVisibility(ESlateVisibility::Visible); }
void UPauseWidget::OnQuitUnhovered() { ImageQuit->SetVisibility(ESlateVisibility::Hidden); }
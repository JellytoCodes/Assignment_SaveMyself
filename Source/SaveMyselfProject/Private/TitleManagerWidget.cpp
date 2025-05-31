// Fill out your copyright notice in the Description page of Project Settings.

#include "TitleManagerWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SaveMyselfGameInstance.h"
#include "SaveHelper.h"

void UTitleManagerWidget::NativeConstruct()
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

	if(ButtonStart && ImageStart) 
	{
		ImageStart->SetVisibility(ESlateVisibility::Hidden);

		ButtonStart->OnClicked.AddDynamic(this, &UTitleManagerWidget::OnStartClicked);
		ButtonStart->OnHovered.AddDynamic(this, &UTitleManagerWidget::OnStartHovered);
		ButtonStart->OnUnhovered.AddDynamic(this, &UTitleManagerWidget::OnStartUnhovered);
	}

	if(ButtonLoad && ImageLoad && TextLoad) 
	{
		ImageLoad->SetVisibility(ESlateVisibility::Hidden);

		//세이브 데이터 유무에 따른 컬러 전환
		const bool bHasSave = UGameplayStatics::DoesSaveGameExist(TEXT("DefenseSaveSlot"), 0);
		FLinearColor saveColor = bHasSave ? FLinearColor::White : FLinearColor(.5f, .5f, .5f, 1.f);
		TextLoad->SetColorAndOpacity(FSlateColor(saveColor));

		ButtonLoad->OnClicked.AddDynamic(this, &UTitleManagerWidget::OnLoadClicked);
		ButtonLoad->OnHovered.AddDynamic(this, &UTitleManagerWidget::OnLoadHovered);
		ButtonLoad->OnUnhovered.AddDynamic(this, &UTitleManagerWidget::OnLoadUnhovered);
	}

	if(ButtonSetting && ImageSetting)
	{
		ImageSetting->SetVisibility(ESlateVisibility::Hidden);

		ButtonSetting->OnClicked.AddDynamic(this, &UTitleManagerWidget::OnSettingClicked);
		ButtonSetting->OnHovered.AddDynamic(this, &UTitleManagerWidget::OnSettingHovered);
		ButtonSetting->OnUnhovered.AddDynamic(this, &UTitleManagerWidget::OnSettingUnhovered);
	}

	if(ButtonQuit && ImageQuit)
	{
		ImageQuit->SetVisibility(ESlateVisibility::Hidden);

		ButtonQuit->OnClicked.AddDynamic(this, &UTitleManagerWidget::OnQuitClicked);
		ButtonQuit->OnHovered.AddDynamic(this, &UTitleManagerWidget::OnQuitHovered);
		ButtonQuit->OnUnhovered.AddDynamic(this, &UTitleManagerWidget::OnQuitUnhovered);
	}
}

void UTitleManagerWidget::OnStartClicked()
{
	UGameplayStatics::OpenLevel(this, FName("Stage_Tutorial"));
}

void UTitleManagerWidget::OnLoadClicked()
{
	if(UGameplayStatics::DoesSaveGameExist(TEXT("DefenseSaveSlot"), 0))
	{
		UGameplayStatics::OpenLevel(this, USaveHelper::LoadStageData());
	}
}

void UTitleManagerWidget::OnSettingClicked() { /* Not Implemented */ }

void UTitleManagerWidget::OnQuitClicked()
{
	auto PC = UGameplayStatics::GetPlayerController(this, 0);
	if(!PC) return;

	UKismetSystemLibrary::QuitGame(this, PC, EQuitPreference::Quit, true);
}

void UTitleManagerWidget::OnStartHovered() { ImageStart->SetVisibility(ESlateVisibility::Visible); }
void UTitleManagerWidget::OnStartUnhovered(){ ImageStart->SetVisibility(ESlateVisibility::Hidden); }

void UTitleManagerWidget::OnLoadHovered() { ImageLoad->SetVisibility(ESlateVisibility::Visible); }
void UTitleManagerWidget::OnLoadUnhovered() { ImageLoad->SetVisibility(ESlateVisibility::Hidden); }

void UTitleManagerWidget::OnSettingHovered() { ImageSetting->SetVisibility(ESlateVisibility::Visible); }
void UTitleManagerWidget::OnSettingUnhovered() { ImageSetting->SetVisibility(ESlateVisibility::Hidden); }

void UTitleManagerWidget::OnQuitHovered() { ImageQuit->SetVisibility(ESlateVisibility::Visible); }
void UTitleManagerWidget::OnQuitUnhovered() { ImageQuit->SetVisibility(ESlateVisibility::Hidden); }

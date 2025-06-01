// Fill out your copyright notice in the Description page of Project Settings.

#include "StageClearWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "DefenseCharacter.h"
#include "SaveHelper.h"
#include "SaveMyselfGameInstance.h"

void UStageClearWidget::NativeConstruct()
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

	if(ButtonNextStage && ImageNextStage)
	{
		ImageNextStage->SetVisibility(ESlateVisibility::Hidden);

		ButtonNextStage->OnClicked.AddDynamic(this, &UStageClearWidget::OnNextStageClicked);
		ButtonNextStage->OnHovered.AddDynamic(this, &UStageClearWidget::OnNextStageHovered);
		ButtonNextStage->OnUnhovered.AddDynamic(this, &UStageClearWidget::OnNextStageUnhovered);
	}

	if(ButtonTitleMenu && ImageTitleMenu)
	{
		ImageTitleMenu->SetVisibility(ESlateVisibility::Hidden);

		ButtonTitleMenu->OnClicked.AddDynamic(this, &UStageClearWidget::OnTitleMenuClicked);
		ButtonTitleMenu->OnHovered.AddDynamic(this, &UStageClearWidget::OnTitleMenuHovered);
		ButtonTitleMenu->OnUnhovered.AddDynamic(this, &UStageClearWidget::OnTitleMenuUnhovered);
	}
}

void UStageClearWidget::OnNextStageClicked()
{
	auto gInstance = Cast<USaveMyselfGameInstance>(GetGameInstance());
	if(!gInstance) return;

	UGameplayStatics::OpenLevel(this, gInstance->GetNextStageID());
}

void UStageClearWidget::OnTitleMenuClicked()
{
	auto gInstance = Cast<USaveMyselfGameInstance>(GetGameInstance());
	if(!gInstance) return;

	if(gInstance->GetNextStageID() == "EndGame") return;

	USaveHelper::SaveStageData(gInstance->GetNextStageID());

	UGameplayStatics::OpenLevel(this, FName("GameTitle"));
}

void UStageClearWidget::OnNextStageHovered() { ImageNextStage->SetVisibility(ESlateVisibility::Visible); }
void UStageClearWidget::OnNextStageUnhovered() { ImageNextStage->SetVisibility(ESlateVisibility::Hidden); }

void UStageClearWidget::OnTitleMenuHovered() { ImageTitleMenu->SetVisibility(ESlateVisibility::Visible); }
void UStageClearWidget::OnTitleMenuUnhovered() { ImageTitleMenu->SetVisibility(ESlateVisibility::Hidden); }

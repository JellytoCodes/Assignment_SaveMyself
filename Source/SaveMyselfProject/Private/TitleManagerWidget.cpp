// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleManagerWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SaveMyselfGameInstance.h"
#include "SaveHelper.h"

void UTitleManagerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(ButtonStart) ButtonStart->OnClicked.AddDynamic(this, &UTitleManagerWidget::OnstartClicked);
	if(ButtonLoad) ButtonLoad->OnClicked.AddDynamic(this, &UTitleManagerWidget::OnLoadClicked);
	if(ButtonSetting) ButtonSetting->OnClicked.AddDynamic(this, &UTitleManagerWidget::OnSettingClicked);
	if(ButtonQuit) ButtonQuit->OnClicked.AddDynamic(this, &UTitleManagerWidget::OnQuitClicked);
}

void UTitleManagerWidget::OnstartClicked()
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
	UKismetSystemLibrary::QuitGame(this, PC, EQuitPreference::Quit, true);
}

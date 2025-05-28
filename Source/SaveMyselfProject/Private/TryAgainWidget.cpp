// Fill out your copyright notice in the Description page of Project Settings.

#include "TryAgainWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SaveMyselfGameInstance.h"
#include "DefenseCharacter.h"
#include "SaveHelper.h"

void UTryAgainWidget::NativeConstruct()
{	
	if(ButtonReTry) ButtonReTry->OnClicked.AddDynamic(this, &UTryAgainWidget::OnReTryClicked);
	if(ButtonQuit) ButtonQuit->OnClicked.AddDynamic(this, &UTryAgainWidget::OnReQuitClicked);
}

void UTryAgainWidget::OnReTryClicked()
{
	if(UGameplayStatics::DoesSaveGameExist(TEXT("DefenseSaveSlot"), 0))
	{
		UGameplayStatics::OpenLevel(this, USaveHelper::LoadStageData());
	}
}

void UTryAgainWidget::OnReQuitClicked()
{
	auto PC = UGameplayStatics::GetPlayerController(this, 0);
	if(!PC) return;

	UKismetSystemLibrary::QuitGame(this, PC, EQuitPreference::Quit, true);
}

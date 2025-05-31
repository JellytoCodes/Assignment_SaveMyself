// Fill out your copyright notice in the Description page of Project Settings.

#include "StageClearWidget.h"
#include "SaveMyselfGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "DefenseCharacter.h"
#include "Components/Button.h"

void UStageClearWidget::NativeConstruct()
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

	if(ButtonNextStage) ButtonNextStage->OnClicked.AddDynamic(this, &UStageClearWidget::OnNextStageClicked);
}

void UStageClearWidget::OnNextStageClicked()
{
	auto GInstance = Cast<USaveMyselfGameInstance>(GetGameInstance());
	if(!GInstance) return;

	UGameplayStatics::OpenLevel(this, GInstance->GetNextStageID());
}

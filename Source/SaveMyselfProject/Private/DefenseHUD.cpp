// Fill out your copyright notice in the Description page of Project Settings.

#include "DefenseHUD.h"
#include "StageWidget.h"

ADefenseHUD::ADefenseHUD()
{
	static ConstructorHelpers::FClassFinder<UStageWidget> StageWidgetBP(TEXT("/Game/WidgetBP/WBP_StageWidget.WBP_StageWidget_C"));
	if(StageWidgetBP.Succeeded())
	{
		StageWidgetClass = StageWidgetBP.Class;
	}
}

void ADefenseHUD::ShowStageWidget(EStageState NewState)
{
	if(!StageWidgetClass) return;

	if(StageWidgetInstance)
	{
		StageWidgetInstance->RemoveFromParent();
		StageWidgetInstance = nullptr;
	}

	StageWidgetInstance = CreateWidget<UStageWidget>(GetWorld(), StageWidgetClass);
	if(StageWidgetInstance)
	{
		StageWidgetInstance->AddToViewport();

		FText StageText;
		switch(NewState)
		{
			case EStageState::Prepare :
				StageText = FText::FromString(TEXT("Prepare Phase"));
			break;

			case EStageState::Battle :
				StageText = FText::FromString(TEXT("Battle Phase"));
			break;

			case EStageState::Victory :
				StageText = FText::FromString(TEXT("Victory"));
			break;

			case EStageState::Defeat :
				StageText = FText::FromString(TEXT("Defeat"));
			break;
		}
		StageWidgetInstance->SetStageText(StageText);
	}
}

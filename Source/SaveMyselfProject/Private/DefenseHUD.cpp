// Fill out your copyright notice in the Description page of Project Settings.

#include "DefenseHUD.h"
#include "StageWidget.h"
#include "QuickSlotWidget.h"
#include "StorageWidget.h"
#include "PlayerHPWidget.h"

ADefenseHUD::ADefenseHUD()
{
	//Stage Widget 생성
	static ConstructorHelpers::FClassFinder<UStageWidget> StageWidgetBP(TEXT("/Game/WidgetBP/WBP_StageWidget.WBP_StageWidget_C"));
	if(StageWidgetBP.Succeeded())
	{
		StageWidgetClass = StageWidgetBP.Class;
	}
	
	//플레이어 QuickSlot Widget 생성
	static ConstructorHelpers::FClassFinder<UQuickSlotWidget> quickSlotWidgetBP(TEXT("/Game/WidgetBP/WBP_QuickSlotWidget.WBP_QuickSlotWidget_C"));
	if(quickSlotWidgetBP.Succeeded())
	{
		quickSlotWidgetClass = quickSlotWidgetBP.Class;
	}

	//플레이어 HP Widget 생성
	static ConstructorHelpers::FClassFinder<UPlayerHPWidget> HPWidgetBP(TEXT("/Game/WidgetBP/WBP_PlayerHPWidget.WBP_PlayerHPWidget_C"));
	if(HPWidgetBP.Succeeded())
	{
		HPWidgetClass = HPWidgetBP.Class;
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

void ADefenseHUD::ShowPlayerQuickSlotWidget()
{
	quickSlotWidgetInstance = CreateWidget<UQuickSlotWidget>(GetWorld(), quickSlotWidgetClass);
	if(quickSlotWidgetInstance) quickSlotWidgetInstance->AddToViewport();
}

void ADefenseHUD::ShowPlayerHPWidget()
{
	HPWidgetInstance = CreateWidget<UPlayerHPWidget>(GetWorld(), HPWidgetClass);
	if(HPWidgetInstance) HPWidgetInstance->AddToViewport();
}

void ADefenseHUD::UpdatedPlayerHP(int32 getHP)
{
	HPWidgetInstance->UpdatedPlayerHPWidget(getHP);
}

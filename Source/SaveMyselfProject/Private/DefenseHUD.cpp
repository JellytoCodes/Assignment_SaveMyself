// Fill out your copyright notice in the Description page of Project Settings.

#include "DefenseHUD.h"
#include "StageWidget.h"
#include "QuickSlotWidget.h"
#include "StorageWidget.h"
#include "PlayerHPWidget.h"
#include "StageClearWidget.h"

ADefenseHUD::ADefenseHUD()
{
	//Stage Widget 积己
	static ConstructorHelpers::FClassFinder<UStageWidget> StageWidgetBP(TEXT("/Game/WidgetBP/WBP_StageWidget.WBP_StageWidget_C"));
	if(StageWidgetBP.Succeeded())
	{
		StageWidgetClass = StageWidgetBP.Class;
	}
	
	//敲饭捞绢 QuickSlot Widget 积己
	static ConstructorHelpers::FClassFinder<UQuickSlotWidget> quickSlotWidgetBP(TEXT("/Game/WidgetBP/WBP_QuickSlotWidget.WBP_QuickSlotWidget_C"));
	if(quickSlotWidgetBP.Succeeded())
	{
		quickSlotWidgetClass = quickSlotWidgetBP.Class;
	}

	//敲饭捞绢 HP Widget 积己
	static ConstructorHelpers::FClassFinder<UPlayerHPWidget> HPWidgetBP(TEXT("/Game/WidgetBP/WBP_PlayerHPWidget.WBP_PlayerHPWidget_C"));
	if(HPWidgetBP.Succeeded())
	{
		HPWidgetClass = HPWidgetBP.Class;
	}

	//Stage Clear Widget 积己
	static ConstructorHelpers::FClassFinder<UStageClearWidget> StageClearWidgetBP(TEXT("/Game/WidgetBP/WBP_StageClearWidget.WBP_StageClearWidget_C"));
	if(StageClearWidgetBP.Succeeded())
	{
		StageClearWidgetClass = StageClearWidgetBP.Class;
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
				ShowStageClearWidget();
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

void ADefenseHUD::ShowStageClearWidget()
{
	StageClearWidgetInstance = CreateWidget<UStageClearWidget>(GetWorld(), StageClearWidgetClass);
	if(StageClearWidgetInstance) StageClearWidgetInstance->AddToViewport();
}

void ADefenseHUD::UpdatedPlayerHP(int32 getHP)
{
	HPWidgetInstance->UpdatedPlayerHPWidget(getHP);
}

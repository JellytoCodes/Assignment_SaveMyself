// Fill out your copyright notice in the Description page of Project Settings.

#include "DefenseHUD.h"
#include "StageWidget.h"
#include "QuickSlotWidget.h"
#include "StorageWidget.h"
#include "PlayerHPWidget.h"
#include "StageClearWidget.h"
#include "TryAgainWidget.h"
#include "SaveMyselfGameInstance.h"
#include "Kismet/GameplayStatics.h"

ADefenseHUD::ADefenseHUD()
{
	//Stage Widget BP 생성
	static ConstructorHelpers::FClassFinder<UStageWidget> StageWidgetBP
	(TEXT("/Game/WidgetBP/WBP_StageWidget.WBP_StageWidget_C"));
	if(StageWidgetBP.Succeeded()) StageWidgetClass = StageWidgetBP.Class;
	
	//플레이어 QuickSlot Widget BP 생성
	static ConstructorHelpers::FClassFinder<UQuickSlotWidget> quickSlotWidgetBP
	(TEXT("/Game/WidgetBP/WBP_QuickSlotWidget.WBP_QuickSlotWidget_C"));
	
	if(quickSlotWidgetBP.Succeeded()) quickSlotWidgetClass = quickSlotWidgetBP.Class;

	//플레이어 HP Widget BP 생성
	static ConstructorHelpers::FClassFinder<UPlayerHPWidget> HPWidgetBP
	(TEXT("/Game/WidgetBP/WBP_PlayerHPWidget.WBP_PlayerHPWidget_C"));

	if(HPWidgetBP.Succeeded()) HPWidgetClass = HPWidgetBP.Class;

	//Stage Clear Widget BP 생성
	static ConstructorHelpers::FClassFinder<UStageClearWidget> StageClearWidgetBP
	(TEXT("/Game/WidgetBP/WBP_StageClearWidget.WBP_StageClearWidget_C"));

	if(StageClearWidgetBP.Succeeded()) StageClearWidgetClass = StageClearWidgetBP.Class;

	//Storage Widget BP 생성
	static ConstructorHelpers::FClassFinder<UStorageWidget> storageWidgetBP
	(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Widgets/WBP_HUD.WBP_HUD_C'"));

	if(storageWidgetBP.Succeeded()) StorageWidgetClass = storageWidgetBP.Class;

	//Try Again Widget BP 생성
	static ConstructorHelpers::FClassFinder<UTryAgainWidget> TryAgainWidgetBP
	(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/WidgetBP/WBP_TryAgainWidget.WBP_TryAgainWidget_C'"));

	if(TryAgainWidgetBP.Succeeded()) TryAgainWidgetClass = TryAgainWidgetBP.Class;

}

void ADefenseHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    GetWorld()->GetTimerManager().ClearTimer(StageHUDUpdateHandle);
    Super::EndPlay(EndPlayReason);
}

void ADefenseHUD::StartStageHUDUpdate(UStageManagerComponent *StageManager)
{	
	GetWorld()->GetTimerManager().SetTimer(StageHUDUpdateHandle, [this, StageManager]()
	{
		//StageWidget이 제거 되었을 시 StageHUDUpdateHandle 제거
		if (!IsValid(StageManager) || !IsValid(StageWidgetInstance)) 
		{	
			GetWorld()->GetTimerManager().ClearTimer(StageHUDUpdateHandle);
			return;
		}

		int32 Remaining = StageManager->GetPhaseRemaining();
		EStageState State = StageManager->GetCurStage();

		StageWidgetInstance->UpdatePhaseTimeText(State, Remaining);
	}, .5f, true);
}

void ADefenseHUD::ShowStageWidget(EStageState NewState, UStageManagerComponent* StageManager)
{
	if(!StageWidgetInstance && StageWidgetClass)
	{
		StageWidgetInstance = CreateWidget<UStageWidget>(GetWorld(), StageWidgetClass);
		StageWidgetInstance->AddToViewport();
	}

	auto GInstance = Cast<USaveMyselfGameInstance>(GetGameInstance());
	if(GInstance)
	{
		StageWidgetInstance->SetStageNumberText(GInstance->GetStageID());
	}

	StartStageHUDUpdate(StageManager);
}

void ADefenseHUD::ShowPlayerQuickSlotWidget()
{
	if(!quickSlotWidgetInstance && quickSlotWidgetClass)
	{
		quickSlotWidgetInstance = CreateWidget<UQuickSlotWidget>(GetWorld(), quickSlotWidgetClass);
		quickSlotWidgetInstance->AddToViewport();
	}
}

void ADefenseHUD::ShowPlayerHPWidget()
{
	if(!HPWidgetInstance && HPWidgetClass)
	{
		HPWidgetInstance = CreateWidget<UPlayerHPWidget>(GetWorld(), HPWidgetClass);
		HPWidgetInstance->AddToViewport();
	}
}

void ADefenseHUD::ShowStageClearWidget()
{
	if(!StageClearWidgetInstance && StageClearWidgetClass)
	{
		StageClearWidgetInstance = CreateWidget<UStageClearWidget>(GetWorld(), StageClearWidgetClass);
		if(StageClearWidgetInstance) StageClearWidgetInstance->AddToViewport();
	}
}

void ADefenseHUD::ShowTryAgainWidget()
{
	if(!TryAgainWidgetInstance && TryAgainWidgetClass)
	{
		TryAgainWidgetInstance = CreateWidget<UTryAgainWidget>(GetWorld(), TryAgainWidgetClass);
		if(TryAgainWidgetInstance) TryAgainWidgetInstance->AddToViewport();
	}
}

void ADefenseHUD::ShowStorageWidget(const TArray<const FStorageArrRow*>& Data)
{	
	if(!StorageWidgetInstance && StorageWidgetClass)
	{
		StorageWidgetInstance = CreateWidget<UStorageWidget>(GetWorld(), StorageWidgetClass);
		StorageWidgetInstance->AddItemStorage(Data);
		StorageWidgetInstance->AddToViewport();
	}
	
	StorageWidgetInstance->SetVisibility(ESlateVisibility::Visible);
}

void ADefenseHUD::HideStorageWidget()
{
	if(!StorageWidgetInstance) return;
	
	StorageWidgetInstance->SetVisibility(ESlateVisibility::Collapsed);
}

void ADefenseHUD::UpdatedPlayerHP(int32 getHP)
{
	if(!HPWidgetInstance) return;

	HPWidgetInstance->UpdatedPlayerHPWidget(getHP);
}

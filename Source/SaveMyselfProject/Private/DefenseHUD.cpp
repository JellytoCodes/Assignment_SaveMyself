// Fill out your copyright notice in the Description page of Project Settings.

#include "DefenseHUD.h"
#include "Kismet/GameplayStatics.h"
#include "StageWidget.h"
#include "QuickSlotWidget.h"
#include "StorageWidget.h"
#include "PlayerHPWidget.h"
#include "StageClearWidget.h"
#include "TryAgainWidget.h"
#include "PauseWidget.h"
#include "SaveMyselfGameInstance.h"
#include "SlotToolTipWidget.h"


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

	//Pause Widget BP 생성
	static ConstructorHelpers::FClassFinder<UPauseWidget> PauseWidgetBP
	(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/WidgetBP/WBP_PauseMenuWidget.WBP_PauseMenuWidget_C'"));

	if(PauseWidgetBP.Succeeded()) PauseWidgetClass = PauseWidgetBP.Class;

	//Slot ToopTip Widget BP 생성
	static ConstructorHelpers::FClassFinder<USlotToolTipWidget> slotToolTipWidgetBP
	(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/WidgetBP/WBP_SlotToolTipWidget.WBP_SlotToolTipWidget_C'"));

	if(slotToolTipWidgetBP.Succeeded()) SlotToolTipWidgetClass = slotToolTipWidgetBP.Class;

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
		if(HPWidgetInstance) HPWidgetInstance->RemoveFromParent();
		if(quickSlotWidgetInstance) quickSlotWidgetInstance->RemoveFromParent();
		if(StageWidgetInstance) StageWidgetInstance->RemoveFromParent();

		StageClearWidgetInstance = CreateWidget<UStageClearWidget>(GetWorld(), StageClearWidgetClass);
		if(StageClearWidgetInstance) StageClearWidgetInstance->AddToViewport();
	}
}

void ADefenseHUD::ShowTryAgainWidget()
{
	if(!TryAgainWidgetInstance && TryAgainWidgetClass)
	{
		if(HPWidgetInstance) HPWidgetInstance->RemoveFromParent();
		if(quickSlotWidgetInstance) quickSlotWidgetInstance->RemoveFromParent();
		if(StageWidgetInstance) StageWidgetInstance->RemoveFromParent();

		TryAgainWidgetInstance = CreateWidget<UTryAgainWidget>(GetWorld(), TryAgainWidgetClass);
		if(TryAgainWidgetInstance) TryAgainWidgetInstance->AddToViewport();
	}
}

void ADefenseHUD::ShowPauseWidget()
{
	if(!PauseWidgetInstance && PauseWidgetClass)
	{
		PauseWidgetInstance = CreateWidget<UPauseWidget>(GetWorld(), PauseWidgetClass);
		if(PauseWidgetInstance)
		{
			PauseWidgetInstance->AddToViewport();
			PauseWidgetInstance->OnPauseWidgetClosed.AddDynamic(this, &ADefenseHUD::HidePauseWidget);
		}
	}
}

void ADefenseHUD::HidePauseWidget()
{
	if(PauseWidgetInstance)
	{
		PauseWidgetInstance->RemoveFromParent();
		PauseWidgetInstance = nullptr;
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

	SetInputModeToUI();
}

void ADefenseHUD::HideStorageWidget()
{
	if(StorageWidgetInstance) StorageWidgetInstance->SetVisibility(ESlateVisibility::Collapsed);

	SetInputModeToGame();
}

void ADefenseHUD::ShowSlotToolTipWidget(const FItemMasterDataRow& inData)
{
	if(!SlotToolTipWidgetInstance && SlotToolTipWidgetClass)
	{		
		SlotToolTipWidgetInstance = CreateWidget<USlotToolTipWidget>(GetWorld(), SlotToolTipWidgetClass);
	}

	if(SlotToolTipWidgetInstance)
	{
		SlotToolTipWidgetInstance->AddToViewport();
		SlotToolTipWidgetInstance->SetVisibility(ESlateVisibility::HitTestInvisible);
		SlotToolTipWidgetInstance->Setup(inData);
	}
}

void ADefenseHUD::HideSlotToolTipWidget()
{
	if(SlotToolTipWidgetInstance) SlotToolTipWidgetInstance->RemoveFromParent();
}

void ADefenseHUD::UpdatedPlayerHP(int32 getHP)
{
	if(!HPWidgetInstance) return;

	HPWidgetInstance->UpdatedPlayerHPWidget(getHP);
}

void ADefenseHUD::SetInputModeToUI()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetHideCursorDuringCapture(false);
		InputMode.SetWidgetToFocus(nullptr); // 필요시 StorageWidgetInstance->TakeWidget()
		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = true;
	}
}

void ADefenseHUD::SetInputModeToGame()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		FInputModeGameOnly InputMode;
		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = false;
	}
}

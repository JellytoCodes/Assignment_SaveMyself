﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "StageManagerComponent.h"
#include "ItemSubsystem.h"
#include "ItemMasterTable.h"
#include "DefenseHUD.generated.h"

class UStageWidget;
class UQuickSlotWidget;
class UPlayerHPWidget;
class UStageClearWidget;
class UStorageWidget;
class UTryAgainWidget;
class UPauseWidget;
class USlotToolTipWidget;

UCLASS()
class SAVEMYSELFPROJECT_API ADefenseHUD : public AHUD
{
	GENERATED_BODY()

public :
	ADefenseHUD();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	FTimerHandle StageHUDUpdateHandle;

	void StartStageHUDUpdate(UStageManagerComponent* StageManager);

	void ShowStageWidget(EStageState NewState, UStageManagerComponent* StageManager);
	void ShowPlayerQuickSlotWidget();
	void ShowPlayerHPWidget();
	void ShowStageClearWidget();
	void ShowTryAgainWidget();

	void ShowPauseWidget();

	UFUNCTION()
	void HidePauseWidget();

	void ShowStorageWidget(const TArray<const FStorageArrRow*>& Data);
	void HideStorageWidget();

	void ShowSlotToolTipWidget(const FItemMasterDataRow& inData);
	void HideSlotToolTipWidget();

	void UpdatedPlayerHP(int32 getHP);

	void SetInputModeToUI();
	void SetInputModeToGame();

	FORCEINLINE UQuickSlotWidget* GetQuicklotWidget() const { return quickSlotWidgetInstance; }
	FORCEINLINE UStorageWidget* GetStorageWidget() const { return StorageWidgetInstance; }

private :
	//Stage Widget
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UStageWidget> StageWidgetClass;

	UStageWidget* StageWidgetInstance;

	//Player QuickSlot Widget
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UQuickSlotWidget> quickSlotWidgetClass;

	UQuickSlotWidget* quickSlotWidgetInstance;

	//Player HP Widget
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UPlayerHPWidget> HPWidgetClass;

	UPlayerHPWidget* HPWidgetInstance;

	//Stage Clear Widget
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UStageClearWidget> StageClearWidgetClass;

	UStageClearWidget* StageClearWidgetInstance;

	//Storage Widget
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UStorageWidget> StorageWidgetClass;

	UStorageWidget* StorageWidgetInstance;

	//Try Again Widget
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UTryAgainWidget> TryAgainWidgetClass;

	UTryAgainWidget* TryAgainWidgetInstance;

	//Pause Widget
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UPauseWidget> PauseWidgetClass;

	UPauseWidget* PauseWidgetInstance;

	//Slot ToolTip Widget
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<USlotToolTipWidget> SlotToolTipWidgetClass;

	USlotToolTipWidget* SlotToolTipWidgetInstance;
};

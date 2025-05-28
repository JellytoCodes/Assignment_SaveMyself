// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "StageManagerComponent.h"
#include "DefenseHUD.generated.h"

class UStageWidget;
class UQuickSlotWidget;
class UPlayerHPWidget;
class UStageClearWidget;

UCLASS()
class SAVEMYSELFPROJECT_API ADefenseHUD : public AHUD
{
	GENERATED_BODY()

public :
	ADefenseHUD();

	void ShowStageWidget(EStageState NewState);
	void ShowPlayerQuickSlotWidget();
	void ShowPlayerHPWidget();
	void ShowStageClearWidget();

	void UpdatedPlayerHP(int32 getHP);

	FORCEINLINE UQuickSlotWidget* GetQuicklotWidget() const { return quickSlotWidgetInstance; }

private :
	//Stage Widget
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UStageWidget> StageWidgetClass;

	UStageWidget* StageWidgetInstance;

	//Player QuickSlot Widget
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UQuickSlotWidget> quickSlotWidgetClass;

	UQuickSlotWidget* quickSlotWidgetInstance;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UPlayerHPWidget> HPWidgetClass;

	UPlayerHPWidget* HPWidgetInstance;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UStageClearWidget> StageClearWidgetClass;

	UStageClearWidget* StageClearWidgetInstance;
};

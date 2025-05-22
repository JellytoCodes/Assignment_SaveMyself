// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemSubsystem.h"
#include "QuickSlotWidget.generated.h"

class UPlayerQuickSlot;
class UWrapBox;
class UProgressBar;
class UTextBlock;

UCLASS()
class SAVEMYSELFPROJECT_API UQuickSlotWidget : public UUserWidget
{
	GENERATED_BODY()

protected :
	UPROPERTY(EditDefaultsOnly, Category = "PlayerQuickSlot")
	TSubclassOf<UPlayerQuickSlot> itemSlotWidgetClass;

	int32 maxQuantity = 99;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* curWeightBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* curWeightText;

	UPROPERTY(meta = (BindWidget))
	UWrapBox* QuickSlotWrapBox;

	int32 slotArr = 0;

public :

	bool SetBagWeight(FStorageArrRow& InData);

	UFUNCTION(BlueprintCallable)
	void AddItemQuickSlot(UStorageSlot* pSlotData);

	const FStorageArrRow* GetQuickSlotItem(int32 index);

	TArray<FStorageArrRow> saveSlot;

	UFUNCTION(BlueprintCallable)
	void UseQuickSlotItem(int32 index);

	
};

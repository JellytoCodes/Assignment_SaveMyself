// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemSubsystem.h"
#include "QuickSlotWidget.generated.h"

class UPlayerQuickSlot;
class UWrapBox;

UCLASS()
class SAVEMYSELFPROJECT_API UQuickSlotWidget : public UUserWidget
{
	GENERATED_BODY()

protected :
	UPROPERTY(EditDefaultsOnly, Category = "PlayerQuickSlot")
	TSubclassOf<UPlayerQuickSlot> itemSlotWidgetClass;

	//캐릭터 배낭 무게 설정
	int32 maxBagWeight = 20;
	int32 curBagWeight = 0;

	int32 maxQuantity = 99;

	bool GetBagWeight(FStorageArray& InData);

	UPROPERTY(meta = (BindWidget))
	UWrapBox* QuickSlotWrapBox;

public :



	UFUNCTION(BlueprintCallable)
	void AddItemQuickSlot(UStorageSlot* pSlotData);
};

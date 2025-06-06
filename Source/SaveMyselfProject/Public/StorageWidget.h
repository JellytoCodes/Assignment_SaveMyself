﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemSubsystem.h"
#include "StorageWidget.generated.h"

class UStorageSlot;
class UWrapBox;

UCLASS()
class SAVEMYSELFPROJECT_API UStorageWidget : public UUserWidget
{
	GENERATED_BODY()

protected :
	UPROPERTY(EditDefaultsOnly, Category = "StorageSlot")
	TSubclassOf<UStorageSlot> itemSlotWidgetClass;

	UPROPERTY(meta = (BindWidget))
	UWrapBox* storageWrapBox;
	
	UPROPERTY(EditDefaultsOnly, Category = "QuickSlot")
	class UQuickSlotWidget* QuickSlotWidgetInstance;

public :

	void AddItemStorage(const TArray<const FStorageArrRow*> InData);

	UFUNCTION()
	void ItemRegist(UStorageSlot* pSlotData);


};

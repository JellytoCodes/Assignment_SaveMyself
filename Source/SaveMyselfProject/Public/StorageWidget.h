// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StorageWidget.generated.h"

class UStorageSlot;
class UWrapBox;
UCLASS()
class SAVEMYSELFPROJECT_API UStorageWidget : public UUserWidget
{
	GENERATED_BODY()

protected :
	UPROPERTY(EditDefaultsOnly, Category = "StorageSlot")
	TSubclassOf<UStorageSlot> ItemSlotWidgetClass;

	UPROPERTY(meta = (BindWidget))
	UWrapBox* StorageWrapBox;
};

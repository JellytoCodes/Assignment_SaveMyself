// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemSubsystem.h"
#include "PlayerQuickSlot.generated.h"

class UTextBlock;
class UImage;
class UButton;

UCLASS()
class SAVEMYSELFPROJECT_API UPlayerQuickSlot : public UUserWidget
{
	GENERATED_BODY()

protected : 
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnItemButtonClicked();
	
	const FItemMasterDataRow* ItemSlotData;

	FStorageArrRow StorageArr;

public :

	UPROPERTY(meta = (BindWidget))	UImage* ItemImage;
	UPROPERTY(meta = (BindWidget))	UTextBlock* ItemName;
	UPROPERTY(meta = (BindWidget))	UImage* ItemCountImage;
	UPROPERTY(meta = (BindWidget))	UTextBlock* ItemCountText;
	UPROPERTY(meta = (BindWidget))	UButton* ItemButton;

	int32 curQuickQuantity;

	void SetItemData(const FStorageArrRow* InData);
	FStorageArrRow& GetItemData() { return StorageArr; }

	UFUNCTION()
	bool DecreaseQuantity();
};

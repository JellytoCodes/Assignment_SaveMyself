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

private : 
	virtual void NativeConstruct() override;
	
	const FItemMasterDataRow* ItemSlotData;

	FStorageArrRow StorageArr;

	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))	
	UImage* ItemImage;

	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))	
	UTextBlock* ItemName;

	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))	
	UTextBlock* ItemCountText;

	int32 curQuickQuantity;

public :
	void SetItemData(const FStorageArrRow* InData);
	FStorageArrRow& GetItemData() { return StorageArr; }

	void SetQuickQuantity(int32 index) { curQuickQuantity += index; }
	int32 GetQuickQuantity() const { return curQuickQuantity; }

	UFUNCTION()
	bool DecreaseQuantity();

	FORCEINLINE UTextBlock* GetItemName() const { return ItemName; }
	FORCEINLINE UTextBlock* GetItemCountText() const { return ItemCountText; }
};

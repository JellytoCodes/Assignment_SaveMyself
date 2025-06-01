// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemSubsystem.h"
#include "StorageSlot.generated.h"

class UTextBlock;
class UImage;
class UButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemSlotDelegate, UStorageSlot*, pStorageSlot);

UCLASS()
class SAVEMYSELFPROJECT_API UStorageSlot : public UUserWidget
{
	GENERATED_BODY()

protected : 
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnItemButtonClicked();

	void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	void NativeOnMouseLeave(const FPointerEvent& InMouseEvent);

	void OnMouseEnterSlot();
	void OnMouseLeaveSlot();

public :
	UPROPERTY(meta = (BindWidget))	
	UImage* ItemImage;

	UPROPERTY(meta = (BindWidget))	
	UTextBlock* ItemName;

	UPROPERTY(meta = (BindWidget))	
	UTextBlock* ItemCountText;

	UPROPERTY(meta = (BindWidget))
	UButton* ItemButton;

	const FItemMasterDataRow* ItemSlotData;

	FStorageArrRow StorageArr;

	FItemSlotDelegate ItemSlotDelegate;
	
	void SetItemData(const FStorageArrRow* InData);
	FStorageArrRow& GetItemData() { return StorageArr; }

	bool bIsAmount = true;

	//bIsAmount Getter/Setter
	const bool GetIsAmount() { return bIsAmount; }
	void SetIsAmount(bool IsAmount) { bIsAmount = IsAmount; }
};

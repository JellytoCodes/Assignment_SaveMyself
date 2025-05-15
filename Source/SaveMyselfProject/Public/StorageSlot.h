// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemSubsystem.h"
#include "StorageSlot.generated.h"

class UTextBlock;
class UImage;
class UButton;

USTRUCT(BlueprintType)
struct FStorageArray
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quantity;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemSlotDelegate, UStorageSlot*, pItemSlot);

UCLASS()
class SAVEMYSELFPROJECT_API UStorageSlot : public UUserWidget
{
	GENERATED_BODY()

private :
	UPROPERTY(meta = (BindWidget))	UButton* ItemButton;
	UPROPERTY(meta = (BindWidget))	UImage* ItemImage;
	UPROPERTY(meta = (BindWidget))	UTextBlock* ItemName;
	UPROPERTY(meta = (BindWidget))	UImage* ItemCountImage;
	UPROPERTY(meta = (BindWidget))	UTextBlock* ItemCountText;

protected : 
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnItemButtonClicked();

	const FItemMasterDataRow* ItemSlotData;

public :
	void SetItemData(const FStorageArray& InData);
};

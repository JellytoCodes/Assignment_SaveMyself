// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemSubsystem.h"
#include "ItemMasterTable.h"
#include "SlotToolTipWidget.generated.h"

class UTextBlock;

UCLASS()
class SAVEMYSELFPROJECT_API USlotToolTipWidget : public UUserWidget
{
	GENERATED_BODY()

private :
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UTextBlock* TextName;

	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UTextBlock* TextDescription;

	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UTextBlock* TextWeight;

	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UTextBlock* TextType;

	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UTextBlock* TextStat;

	UPROPERTY(meta = (BindWidgetAnim), meta = (AllowPrivateAccess = "true"), Transient)
	class UWidgetAnimation* FadeInAnim;

public :
	UFUNCTION(BlueprintCallable)
	void Setup(const FItemMasterDataRow& inData);
};

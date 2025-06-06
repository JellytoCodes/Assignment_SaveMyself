﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "StorageSlot.h"
#include "StorageWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "DefenseGameModeBase.h"
#include "DefenseHUD.h"

void UStorageSlot::NativeConstruct()
{
	Super::NativeConstruct();

	if(ItemButton)
	{
		ItemButton->OnClicked.AddDynamic(this, &UStorageSlot::OnItemButtonClicked);
	}
}

void UStorageSlot::OnItemButtonClicked()
{
	ADefenseGameModeBase* DefenseMode = Cast<ADefenseGameModeBase>(UGameplayStatics::GetGameMode(this));
	if(GetIsAmount())
	{
		ItemSlotDelegate.Broadcast(this);
	}
}

void UStorageSlot::NativeOnMouseEnter(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	OnMouseEnterSlot();
}

void UStorageSlot::NativeOnMouseLeave(const FPointerEvent &InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	OnMouseLeaveSlot();
}

void UStorageSlot::OnMouseEnterSlot()
{
	auto PC = UGameplayStatics::GetPlayerController(this, 0);
	if(!PC || !ItemSlotData) return;

	ADefenseHUD* HUD = Cast<ADefenseHUD>(PC->GetHUD());
	if(!HUD) return;

	HUD->ShowSlotToolTipWidget(*ItemSlotData);
}

void UStorageSlot::OnMouseLeaveSlot()
{
	auto PC = UGameplayStatics::GetPlayerController(this, 0);
	if(!PC || !ItemSlotData) return;

	ADefenseHUD* HUD = Cast<ADefenseHUD>(PC->GetHUD());
	if(!HUD) return;

	HUD->HideSlotToolTipWidget();
}

void UStorageSlot::SetItemData(const FStorageArrRow* InData)
{
	UItemSubsystem* ItemDB = GetGameInstance()->GetSubsystem<UItemSubsystem>();
	if(!ItemDB) return;

	ItemSlotData = ItemDB->GetItemMasterData(InData->ItemID);

	StorageArr = *InData;

	ItemImage->SetOpacity(1.0f);

	//아이콘이 없을 경우를 대비하여 else if 조건 분기점 생성
	if(ItemImage && ItemSlotData->ItemIcon)	ItemImage->SetBrushFromTexture(ItemSlotData->ItemIcon);
	else if(ItemImage)						ItemImage->SetBrushFromTexture(nullptr);

	if(ItemName)							ItemName->SetText(FText::FromString(ItemSlotData->DisplayName.ToString()));
	//아이템 수량
	if(ItemCountText)						ItemCountText->SetText(FText::AsNumber(InData->Quantity));
}

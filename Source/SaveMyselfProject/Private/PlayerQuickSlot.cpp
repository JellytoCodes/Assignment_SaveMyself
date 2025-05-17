// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerQuickSlot.h"
#include "QuickSlotWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UPlayerQuickSlot::NativeConstruct()
{
	Super::NativeConstruct();

	if(ItemButton)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(__FUNCTION__));
		ItemButton->OnClicked.AddDynamic(this, &UPlayerQuickSlot::OnItemButtonClicked);
	}
}

//아이템 구매 취소 기능 구현 대기
void UPlayerQuickSlot::OnItemButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(__FUNCTION__));
}

void UPlayerQuickSlot::SetItemData(const FStorageArray& InData)
{
	UE_LOG(LogTemp, Log, TEXT("SetItemData"));
	UItemSubsystem* ItemDB = GetGameInstance()->GetSubsystem<UItemSubsystem>();
	if(!ItemDB) return;

	ItemSlotData = ItemDB->GetItemMasterData(InData.ItemID);

	StorageArr = InData;

	//아이콘이 없을 경우를 대비하여 else if 조건 분기점 생성
	if(ItemImage && ItemSlotData->ItemIcon)	ItemImage->SetBrushFromTexture(ItemSlotData->ItemIcon);
	else if(ItemImage)						ItemImage->SetBrushFromTexture(nullptr);

	if(ItemName)							ItemName->SetText(ItemSlotData->DisplayName);
}
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

}

void UPlayerQuickSlot::SetItemData(const FStorageArrRow* InData)
{
	UE_LOG(LogTemp, Log, TEXT("SetItemData : %d"), curQuickQuantity);
	UItemSubsystem* ItemDB = GetGameInstance()->GetSubsystem<UItemSubsystem>();
	if(!ItemDB) return;

	ItemSlotData = ItemDB->GetItemMasterData(InData->ItemID);

	StorageArr = *InData;

	//아이콘이 없을 경우를 대비하여 else if 조건 분기점 생성
	if(ItemImage && ItemSlotData->ItemIcon)	ItemImage->SetBrushFromTexture(ItemSlotData->ItemIcon);
	else if(ItemImage)						ItemImage->SetBrushFromTexture(nullptr);

	if(ItemName)							ItemName->SetText(ItemSlotData->DisplayName);

}

bool UPlayerQuickSlot::DecreaseQuantity()
{
	if (curQuickQuantity > 0)
	{
		curQuickQuantity--;
		ItemCountText->SetText(FText::AsNumber(curQuickQuantity));
		return curQuickQuantity == 0; // 0이면 true 반환 → 제거 신호
	}

	return false;
}

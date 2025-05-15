// Fill out your copyright notice in the Description page of Project Settings.


#include "StorageSlot.h"
#include "Components/Image.h"
#include "Components/ButtonSlot.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UStorageSlot::NativeConstruct()
{
	Super::NativeConstruct();
}

void UStorageSlot::OnItemButtonClicked()
{
	
}

void UStorageSlot::SetItemData(const FStorageArray& InData)
{
	UItemSubsystem* ItemDB = GetGameInstance()->GetSubsystem<UItemSubsystem>();
	if(!ItemDB) return;

	ItemSlotData = ItemDB->GetItemMasterData(InData.ItemID);

	//�������� ���� ��츦 ����Ͽ� else if ���� �б��� ����
	if(ItemImage && ItemSlotData->ItemIcon)	ItemImage->SetBrushFromTexture(ItemSlotData->ItemIcon);
	else if(ItemImage)						ItemImage->SetBrushFromTexture(nullptr);

	//������ ����
	if(ItemCountText)						ItemCountText->SetText(FText::AsNumber(InData.Quantity));
}

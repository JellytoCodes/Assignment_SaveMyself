// Fill out your copyright notice in the Description page of Project Settings.


#include "StorageSlot.h"
#include "StorageWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UStorageSlot::NativeConstruct()
{
	Super::NativeConstruct();
	if(ItemButton)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(__FUNCTION__));
		ItemButton->OnClicked.AddDynamic(this, &UStorageSlot::OnItemButtonClicked);
	}
}

void UStorageSlot::OnItemButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(__FUNCTION__));
	ItemSlotDelegate.Broadcast(this);
}

void UStorageSlot::SetItemData(const FStorageArrRow* InData)
{
	UE_LOG(LogTemp, Log, TEXT("SetItemData"));
	UItemSubsystem* ItemDB = GetGameInstance()->GetSubsystem<UItemSubsystem>();
	if(!ItemDB) return;

	ItemSlotData = ItemDB->GetItemMasterData(InData->ItemID);

	StorageArr = *InData;

	//�������� ���� ��츦 ����Ͽ� else if ���� �б��� ����
	if(ItemImage && ItemSlotData->ItemIcon)	ItemImage->SetBrushFromTexture(ItemSlotData->ItemIcon);
	else if(ItemImage)						ItemImage->SetBrushFromTexture(nullptr);

	if(ItemName)							ItemName->SetText(ItemSlotData->DisplayName);
	//������ ����
	if(ItemCountText)						ItemCountText->SetText(FText::AsNumber(InData->Quantity));
}

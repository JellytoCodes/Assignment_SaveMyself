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

//������ ���� ��� ��� ���� ���
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

	//�������� ���� ��츦 ����Ͽ� else if ���� �б��� ����
	if(ItemImage && ItemSlotData->ItemIcon)	ItemImage->SetBrushFromTexture(ItemSlotData->ItemIcon);
	else if(ItemImage)						ItemImage->SetBrushFromTexture(nullptr);

	if(ItemName)							ItemName->SetText(ItemSlotData->DisplayName);
}
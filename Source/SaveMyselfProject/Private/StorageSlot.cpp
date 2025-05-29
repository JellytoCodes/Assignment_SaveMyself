// Fill out your copyright notice in the Description page of Project Settings.


#include "StorageSlot.h"
#include "StorageWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "DefenseGameModeBase.h"

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
	if(GetIsAmount() && DefenseMode->GetBagAmount())
	{
		ItemSlotDelegate.Broadcast(this);
	}
}

void UStorageSlot::SetItemData(const FStorageArrRow* InData)
{
	UItemSubsystem* ItemDB = GetGameInstance()->GetSubsystem<UItemSubsystem>();
	if(!ItemDB) return;

	ItemSlotData = ItemDB->GetItemMasterData(InData->ItemID);

	StorageArr = *InData;

	ItemImage->SetOpacity(1.0f);

	//�������� ���� ��츦 ����Ͽ� else if ���� �б��� ����
	if(ItemImage && ItemSlotData->ItemIcon)	ItemImage->SetBrushFromTexture(ItemSlotData->ItemIcon);
	else if(ItemImage)						ItemImage->SetBrushFromTexture(nullptr);

	if(ItemName)							ItemName->SetText(ItemSlotData->DisplayName);
	//������ ����
	if(ItemCountText)						ItemCountText->SetText(FText::AsNumber(InData->Quantity));
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "StorageWidget.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "Kismet/GameplayStatics.h"
#include "DefenseCharacter.h"
#include "StorageSlot.h"
#include "QuickSlotWidget.h"
#include "SaveMyselfGameInstance.h"
#include "DefenseGameModeBase.h"

void UStorageWidget::AddItemStorage(const TArray<const FStorageArrRow*> InData)
{
	if(!storageWrapBox) return;

	const int32 SlotCount = storageWrapBox->GetChildrenCount();

	for(int32 i = 0 ; i < InData.Num() && i < SlotCount ; ++i)
	{
		UWidget* ChildWidget = storageWrapBox->GetChildAt(i);
		UStorageSlot* pNewStorageSlot = Cast<UStorageSlot>(ChildWidget);

		if(pNewStorageSlot && InData[i])
		{
			pNewStorageSlot->SetItemData(InData[i]);
			pNewStorageSlot->ItemSlotDelegate.AddDynamic(this, &UStorageWidget::ItemRegist);

			if(ADefenseCharacter* PC = Cast<ADefenseCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
			{
				PC->BindStorageSlot(pNewStorageSlot);
			}
		}
		else if(pNewStorageSlot && !InData[i])
		{
			pNewStorageSlot->SetItemData(nullptr);
		}
	}
}

void UStorageWidget::ItemRegist(UStorageSlot* pSlotData)
{	
	FStorageArrRow& ItemData = pSlotData->GetItemData();

	auto gInstance = Cast<USaveMyselfGameInstance>(GetGameInstance());	
	if(!gInstance) return;

	auto defenseMode = Cast<ADefenseGameModeBase>(UGameplayStatics::GetGameMode(this));
	if(!defenseMode) return;

	UItemSubsystem* ItemDB = GetGameInstance()->GetSubsystem<UItemSubsystem>();

	const FItemMasterDataRow* DataRow = ItemDB->GetItemMasterData(ItemData.ItemID);
	if(!DataRow) return;

	const bool isdecreaseQuantity = (defenseMode->GetCurBagWeight() + DataRow->ItemWeight) > gInstance->GetMaxBagWeight() ? true : false;
	if(isdecreaseQuantity) return;

	if(!defenseMode->GetBagAmount()) return;

	if(ItemData.Quantity > 1) ItemData.Quantity--;
	else
	{
		ItemData.Quantity = 0;
		pSlotData->SetIsAmount(false);
	}

	if(pSlotData->ItemCountText) pSlotData->ItemCountText->SetText(FText::AsNumber(ItemData.Quantity));
}

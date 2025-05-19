// Fill out your copyright notice in the Description page of Project Settings.

#include "StorageWidget.h"
#include "StorageSlot.h"
#include "QuickSlotWidget.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "DefenseCharacter.h"
#include "Kismet/GameplayStatics.h"

void UStorageWidget::AddItemStorage(const TArray<const FStorageArrRow*> InData)
{
	if(storageWrapBox)
	{
		for(auto child : InData)
		{
			UStorageSlot* pNewStorageSlot = CreateWidget<UStorageSlot>(storageWrapBox, itemSlotWidgetClass);
			if(pNewStorageSlot)
			{
				pNewStorageSlot->SetItemData(child);
				storageWrapBox->AddChildToWrapBox(pNewStorageSlot);
				pNewStorageSlot->ItemSlotDelegate.AddDynamic(this, &UStorageWidget::ItemRegist);
				if (ADefenseCharacter* PC = Cast<ADefenseCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
				{
					PC->BindStorageSlot(pNewStorageSlot);
				}
				UE_LOG(LogTemp, Log, TEXT("Get ItemStorage"));
			}
		}
	}
}

void UStorageWidget::ItemRegist(UStorageSlot* pSlotData)
{	
	FStorageArrRow& ItemData = pSlotData->GetItemData();

	if(ItemData.Quantity > 0)
	{
		ItemData.Quantity--;

		if(pSlotData->ItemCountText)
		{
			pSlotData->ItemCountText->SetText(FText::AsNumber(ItemData.Quantity));
		}
		UE_LOG(LogTemp, Log, TEXT("Used %s : %d"), *ItemData.ItemID.ToString(), ItemData.Quantity);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Inventory Exhaustion"));
	}
}

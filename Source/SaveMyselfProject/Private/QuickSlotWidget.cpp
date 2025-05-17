// Fill out your copyright notice in the Description page of Project Settings.

#include "QuickSlotWidget.h"
#include "Components/WrapBox.h"
#include "Components/TextBlock.h"
#include "PlayerQuickSlot.h"
#include "StorageSlot.h"

void UQuickSlotWidget::AddItemQuickSlot(UStorageSlot* pSlotData)
{
	UE_LOG(LogTemp, Log, TEXT("Called AddItemQuickSlot"));
	FStorageArray& InData = pSlotData->GetItemData();
	
	if(GetBagWeight(InData)) return;
	
	if(QuickSlotWrapBox)
	{
		UPlayerQuickSlot* pSlot = nullptr;
		for(UWidget* child : QuickSlotWrapBox->GetAllChildren())
		{
			pSlot = Cast<UPlayerQuickSlot>(child);
			if(pSlot && pSlot->ItemName->GetText().EqualTo(InData.DisplayName))
			{
				if(maxQuantity > pSlot->curQuickQuantity)
				{
					pSlot->curQuickQuantity++;
					pSlot->ItemCountText->SetText(FText::AsNumber(pSlot->curQuickQuantity));
					return;
				}
			}
			UE_LOG(LogTemp, Log, TEXT("Loop Completed"));
			pSlot = nullptr;
		}

		if(pSlot == nullptr)
		{
			UPlayerQuickSlot* pNewQuickSlot = CreateWidget<UPlayerQuickSlot>(QuickSlotWrapBox, itemSlotWidgetClass);
			if(pNewQuickSlot)
			{
				pNewQuickSlot->SetItemData(InData);
				QuickSlotWrapBox->AddChildToWrapBox(pNewQuickSlot);
				pNewQuickSlot->curQuickQuantity++;
				pNewQuickSlot->ItemCountText->SetText(FText::AsNumber(pNewQuickSlot->curQuickQuantity));
				UE_LOG(LogTemp, Log, TEXT("Get ItemQuickSlot"));
			}
		}
	}
}

bool UQuickSlotWidget::GetBagWeight(FStorageArray& InData)
{
	UItemSubsystem* ItemDB = GetGameInstance()->GetSubsystem<UItemSubsystem>();

	const FItemMasterDataRow* DataRow = ItemDB->GetItemMasterData(InData.ItemID);
	if(!DataRow) return true;
	
	if(curBagWeight >= maxBagWeight) return true;

	curBagWeight = curBagWeight + DataRow->ItemWeight;
	UE_LOG(LogTemp, Log, TEXT("curBagWeight : %d"), curBagWeight);	
	return false;
}
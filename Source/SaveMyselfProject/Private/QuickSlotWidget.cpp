// Fill out your copyright notice in the Description page of Project Settings.

#include "QuickSlotWidget.h"
#include "Components/WrapBox.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "PlayerQuickSlot.h"
#include "StorageSlot.h"
#include "DefenseCharacter.h"

void UQuickSlotWidget::AddItemQuickSlot(UStorageSlot* pSlotData)
{
	UE_LOG(LogTemp, Log, TEXT("Called AddItemQuickSlot"));
	FStorageArray& InData = pSlotData->GetItemData();
	
	if(SetBagWeight(InData)) return;
	
	if(QuickSlotWrapBox)
	{
		UPlayerQuickSlot* pSlot = nullptr;

		//기존 슬롯에 있는 아이템일 경우 수량만 증가
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

		//슬롯에 없는 아이템일 경우 새로 생성
		if(pSlot == nullptr && slotArr < 10)
		{
			UPlayerQuickSlot* pNewQuickSlot = CreateWidget<UPlayerQuickSlot>(QuickSlotWrapBox, itemSlotWidgetClass);
			if(pNewQuickSlot)
			{
				pNewQuickSlot->SetItemData(InData);
				QuickSlotWrapBox->AddChildToWrapBox(pNewQuickSlot);
				pNewQuickSlot->curQuickQuantity++;
				pNewQuickSlot->ItemCountText->SetText(FText::AsNumber(pNewQuickSlot->curQuickQuantity));
				UE_LOG(LogTemp, Log, TEXT("Get ItemQuickSlot"));
				slotArr++;
				saveSlot.Add(InData);
			}
		}
	}
}

bool UQuickSlotWidget::SetBagWeight(FStorageArray& InData)
{
	UItemSubsystem* ItemDB = GetGameInstance()->GetSubsystem<UItemSubsystem>();

	const FItemMasterDataRow* DataRow = ItemDB->GetItemMasterData(InData.ItemID);
	if(!DataRow) return true;
	
	if(curBagWeight >= maxBagWeight || (maxBagWeight - curBagWeight) < DataRow->ItemWeight) return true;

	curBagWeight = curBagWeight + DataRow->ItemWeight;
	UE_LOG(LogTemp, Log, TEXT("curBagWeight : %d"), curBagWeight);
	
	//배낭 무게 현황 체크 (현재 버그있음 수정 필요)
	if(curWeightBar)
	{
		curWeightBar->SetFillColorAndOpacity(FColor::Green);
		curWeightBar->SetPercent((float)(curBagWeight / maxBagWeight));
		UE_LOG(LogTemp, Log, TEXT("curWeightBar : %d"), curWeightBar->GetParent());		
	}
	
	return false;
}

const FStorageArray* UQuickSlotWidget::GetQuickSlotItem(int32 index)
{
	if(!QuickSlotWrapBox) return nullptr;

	if(index < 0 || index >= saveSlot.Num()) return nullptr;

	UE_LOG(LogTemp, Log, TEXT("return ItemID : %s"), *saveSlot[index].ItemID.ToString());
	return &saveSlot[index];
}

void UQuickSlotWidget::UseQuickSlotItem(int32 index)
{
	if (!QuickSlotWrapBox || index < 0 || index >= QuickSlotWrapBox->GetChildrenCount()) return;

	UPlayerQuickSlot* quickSlot = Cast<UPlayerQuickSlot>(QuickSlotWrapBox->GetChildAt(index));
	if (!quickSlot) return;

	bool bSlotEmpty = quickSlot->DecreaseQuantity();

	if (bSlotEmpty)
	{
		QuickSlotWrapBox->RemoveChildAt(index);
		saveSlot.RemoveAt(index);
		slotArr--;
	}
}
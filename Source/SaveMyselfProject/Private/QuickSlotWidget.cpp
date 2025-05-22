// Fill out your copyright notice in the Description page of Project Settings.

#include "QuickSlotWidget.h"
#include "Components/WrapBox.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "PlayerQuickSlot.h"
#include "StorageSlot.h"
#include "SaveMyselfGameInstance.h"

void UQuickSlotWidget::AddItemQuickSlot(UStorageSlot* pSlotData)
{
	auto GInstance = Cast<USaveMyselfGameInstance>(GetGameInstance());
	if(!GInstance) return;

	UE_LOG(LogTemp, Log, TEXT("Called AddItemQuickSlot"));
	FStorageArrRow& InData = pSlotData->GetItemData();
	
	if(SetBagWeight(InData))
	{
		GInstance->SetBagAmount(false);
		return;
	}
	
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
				pNewQuickSlot->SetItemData(&InData);
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

bool UQuickSlotWidget::SetBagWeight(FStorageArrRow& InData)
{
	auto GInstance = Cast<USaveMyselfGameInstance>(GetGameInstance());	
	if(!GInstance) return true;

	UItemSubsystem* ItemDB = GetGameInstance()->GetSubsystem<UItemSubsystem>();

	const FItemMasterDataRow* DataRow = ItemDB->GetItemMasterData(InData.ItemID);
	if(!DataRow) return true;

	if((GInstance->GetCurBagWeight() + DataRow->ItemWeight) > GInstance->GetMaxBagWeight()) return true;

	GInstance->SetBagWeight(DataRow->ItemWeight);
	UE_LOG(LogTemp, Log, TEXT("curBagWeight : %d"), GInstance->GetCurBagWeight());
	
	if(!curWeightBar && !curWeightText) return true;

	//적재 초과 여부 컬러 표시
	if(GInstance->GetCurBagWeight() >= GInstance->GetMaxBagWeight())	curWeightBar->SetFillColorAndOpacity(FColor::Red);
	else								curWeightBar->SetFillColorAndOpacity(FColor::Green);

	curWeightBar->
	SetPercent(static_cast<float>(GInstance->GetCurBagWeight()) / static_cast<float>(GInstance->GetMaxBagWeight()));

	FString BagTextString = FString::Printf(TEXT("Bag : %d / %d"), GInstance->GetCurBagWeight(), GInstance->GetMaxBagWeight());
	curWeightText->SetText(FText::FromString(BagTextString));

	return false;
}

const FStorageArrRow* UQuickSlotWidget::GetQuickSlotItem(int32 index)
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
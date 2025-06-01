// Fill out your copyright notice in the Description page of Project Settings.

#include "QuickSlotWidget.h"
#include "Components/WrapBox.h"
#include "Components/WrapBoxSlot.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerQuickSlot.h"
#include "StorageSlot.h"
#include "SaveMyselfGameInstance.h"
#include "DefenseGameModeBase.h"

void UQuickSlotWidget::NativeConstruct()
{
	auto GInstance = Cast<USaveMyselfGameInstance>(GetGameInstance());	
	if(!GInstance) return;

	auto DefenseMode = Cast<ADefenseGameModeBase>(UGameplayStatics::GetGameMode(this));
	if(!DefenseMode) return;

	if(curWeightText)
	{
		FString BagTextString = FString::Printf(TEXT("Weight : %d / %d"), DefenseMode->GetCurBagWeight(), GInstance->GetMaxBagWeight());
		curWeightText->SetText(FText::FromString(BagTextString));
	}
}

void UQuickSlotWidget::AddItemQuickSlot(UStorageSlot* pSlotData)
{
	auto DefenseMode = Cast<ADefenseGameModeBase>(UGameplayStatics::GetGameMode(this));
	if(!DefenseMode) return;

	FStorageArrRow& InData = pSlotData->GetItemData();
	
	if(SetBagWeight(InData)) return;
	
	if(QuickSlotWrapBox)
	{
		UPlayerQuickSlot* pSlot = nullptr;

		//기존 슬롯에 있는 아이템일 경우 수량만 증가
		for(UWidget* child : QuickSlotWrapBox->GetAllChildren())
		{
			pSlot = Cast<UPlayerQuickSlot>(child);
			if(pSlot && pSlot->GetItemName()->GetText().EqualTo(InData.DisplayName))
			{
				if(maxQuantity > pSlot->GetQuickQuantity())
				{
					pSlot->SetQuickQuantity(1);
					pSlot->GetItemCountText()->SetText(FText::AsNumber(pSlot->GetQuickQuantity()));
					return;
				}
			}
			pSlot = nullptr;
		}

		//슬롯에 없는 아이템일 경우 새로 생성
		if(pSlot == nullptr && slotArr < 8)
		{
			UPlayerQuickSlot* pNewQuickSlot = CreateWidget<UPlayerQuickSlot>(QuickSlotWrapBox, itemSlotWidgetClass);
			if(pNewQuickSlot)
			{
				FStorageArrRow copy = InData;
				copy.Quantity = 1;
				pNewQuickSlot->SetItemData(&copy);
				QuickSlotWrapBox->AddChildToWrapBox(pNewQuickSlot);

				pNewQuickSlot->SetQuickQuantity(1);
				pNewQuickSlot->GetItemCountText()->SetText(FText::AsNumber(pNewQuickSlot->GetQuickQuantity()));
				slotArr++;
				saveSlot.Add(copy);
			}
		}
	}
}

bool UQuickSlotWidget::SetBagWeight(FStorageArrRow& InData)
{
	auto gInstance = Cast<USaveMyselfGameInstance>(GetGameInstance());	
	if(!gInstance) return true;

	auto defenseMode = Cast<ADefenseGameModeBase>(UGameplayStatics::GetGameMode(this));
	if(!defenseMode) return true;

	UItemSubsystem* ItemDB = GetGameInstance()->GetSubsystem<UItemSubsystem>();

	const FItemMasterDataRow* DataRow = ItemDB->GetItemMasterData(InData.ItemID);
	if(!DataRow) return true;

	if((defenseMode->GetCurBagWeight() + DataRow->ItemWeight) > gInstance->GetMaxBagWeight()) return true;

	defenseMode->SetBagWeight(DataRow->ItemWeight);
	
	if(!curWeightBar && !curWeightText) return true;

	//적재 초과 여부 컬러 표시
	if(defenseMode->GetCurBagWeight() >= gInstance->GetMaxBagWeight())
	{
		curWeightBar->SetFillColorAndOpacity(FColor::Red);
		defenseMode->SetBagAmount(false);
	}
	else curWeightBar->SetFillColorAndOpacity(FColor::Green);

	curWeightBar->
	SetPercent(static_cast<float>(defenseMode->GetCurBagWeight()) / static_cast<float>(gInstance->GetMaxBagWeight()));

	FString BagTextString = FString::Printf(TEXT("Weight : %d / %d"), defenseMode->GetCurBagWeight(), gInstance->GetMaxBagWeight());
	curWeightText->SetText(FText::FromString(BagTextString));

	return false;
}

const FStorageArrRow* UQuickSlotWidget::GetQuickSlotItem(int32 index)
{
	if(!QuickSlotWrapBox) return nullptr;

	if(index < 0 || index >= saveSlot.Num()) return nullptr;

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
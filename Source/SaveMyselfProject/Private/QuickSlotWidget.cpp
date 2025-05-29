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

void UQuickSlotWidget::AddItemQuickSlot(UStorageSlot* pSlotData)
{
	auto DefenseMode = Cast<ADefenseGameModeBase>(UGameplayStatics::GetGameMode(this));
	if(!DefenseMode) return;

	FStorageArrRow& InData = pSlotData->GetItemData();
	
	if(SetBagWeight(InData))
	{
		DefenseMode->SetBagAmount(false);
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

				pNewQuickSlot->curQuickQuantity = 1;
				pNewQuickSlot->ItemCountText->SetText(FText::AsNumber(pNewQuickSlot->curQuickQuantity));
				slotArr++;
				saveSlot.Add(copy);
				UE_LOG(LogTemp, Warning, TEXT("Get New Slot Quantity : %d"),pNewQuickSlot->curQuickQuantity);
			}
		}
	}
}

bool UQuickSlotWidget::SetBagWeight(FStorageArrRow& InData)
{
	auto GInstance = Cast<USaveMyselfGameInstance>(GetGameInstance());	
	if(!GInstance) return true;

	auto DefenseMode = Cast<ADefenseGameModeBase>(UGameplayStatics::GetGameMode(this));
	if(!DefenseMode) return true;

	UItemSubsystem* ItemDB = GetGameInstance()->GetSubsystem<UItemSubsystem>();

	const FItemMasterDataRow* DataRow = ItemDB->GetItemMasterData(InData.ItemID);
	if(!DataRow) return true;

	if((DefenseMode->GetCurBagWeight() + DataRow->ItemWeight) > GInstance->GetMaxBagWeight()) return true;

	DefenseMode->SetBagWeight(DataRow->ItemWeight);
	
	if(!curWeightBar && !curWeightText) return true;

	//적재 초과 여부 컬러 표시
	if(DefenseMode->GetCurBagWeight() >= GInstance->GetMaxBagWeight()) curWeightBar->SetFillColorAndOpacity(FColor::Red);
	else curWeightBar->SetFillColorAndOpacity(FColor::Green);

	curWeightBar->
	SetPercent(static_cast<float>(DefenseMode->GetCurBagWeight()) / static_cast<float>(GInstance->GetMaxBagWeight()));

	FString BagTextString = FString::Printf(TEXT("Weight : %d / %d"), DefenseMode->GetCurBagWeight(), GInstance->GetMaxBagWeight());
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
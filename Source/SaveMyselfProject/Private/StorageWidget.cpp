// Fill out your copyright notice in the Description page of Project Settings.

#include "StorageWidget.h"
#include "StorageSlot.h"
#include "Components/WrapBox.h"

void UStorageWidget::AddItemStorage(const TArray<FStorageArray>& InData)
{
	if(storageWrapBox)
	{
		int32 Index = 0;
		for(auto child : InData)
		{
			UStorageSlot* pNewStorageSlot = CreateWidget<UStorageSlot>(storageWrapBox, itemSlotWidgetClass);
			if(pNewStorageSlot)
			{
				pNewStorageSlot->SetItemData(InData[Index]);
				storageWrapBox->AddChildToWrapBox(pNewStorageSlot);
				UE_LOG(LogTemp, Log, TEXT("Get ItemStorage"));
			}
			Index++;
		}
	}
}

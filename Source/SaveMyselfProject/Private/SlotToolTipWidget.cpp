// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotToolTipWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "SaveMyselfGameInstance.h"

void USlotToolTipWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if(FadeInAnim)
	{
		PlayAnimation(FadeInAnim, 0.f, 1);
	}
}

void USlotToolTipWidget::NativeTick(const FGeometry &MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	FVector2D MousePos;
	if(GetWorld() && GetWorld()->GetFirstPlayerController() &&
	GetWorld()->GetFirstPlayerController()->GetMousePosition(MousePos.X, MousePos.Y))
	SetPositionInViewport(MousePos + FVector2D(15.f, 15.f), true);
}

void USlotToolTipWidget::Setup(const FItemMasterDataRow& itemData)
{	
	UItemSubsystem* itemDB = GetGameInstance()->GetSubsystem<UItemSubsystem>();
	if(!itemDB) return;

	if(TextName) TextName->SetText(FText::FromString(itemData.DisplayName.ToString()));
	if(TextDescription) TextDescription->SetText(itemData.Description);
	if(TextWeight) TextWeight->SetText(FText::AsNumber(itemData.ItemWeight));

	if(!TextType || !TextStat) return;

	UE_LOG(LogTemp, Warning, TEXT("ItemType : %d"), itemData.ItemType);
		
	if(itemData.ItemType == EItemTypes::Weapon)
	{
		auto itemWeaponData = itemDB->GetItemWeaponData(itemData.DisplayName);
		if(!itemWeaponData) return;

		FString itemDamage = FString::Printf(TEXT("%.2f"), itemWeaponData->WeaponDamage);
		TextType->SetText(FText::FromString("Weapon"));			
		TextStat->SetText(FText::FromString(itemDamage));
	}

	else if(itemData.ItemType == EItemTypes::Structure)
	{
		auto itemStructureData = itemDB->GetItemStructureData(itemData.DisplayName);
		if(!itemStructureData) return;

		FString itemHP = FString::Printf(TEXT("%.2f"), itemStructureData->StructureHP);
		TextType->SetText(FText::FromString("Structure"));
		TextStat->SetText(FText::FromString(itemHP));
	}

	else if(itemData.ItemType == EItemTypes::Trap)
	{
		auto itemTrapData = itemDB->GetItemTrapData(itemData.DisplayName);
		if(!itemTrapData) return;

		FString itemDamage = FString::Printf(TEXT("%.2f"), itemTrapData->TrapEffect);
		TextType->SetText(FText::FromString("Trap"));
		TextStat->SetText(FText::FromString(itemDamage));
	}
	else return;
}

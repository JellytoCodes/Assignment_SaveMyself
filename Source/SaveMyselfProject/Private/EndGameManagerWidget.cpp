// Fill out your copyright notice in the Description page of Project Settings.

#include "EndGameManagerWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UEndGameManagerWidget::NativeConstruct()
{
	if(ButtonTitle) ButtonTitle->OnClicked.AddDynamic(this, &UEndGameManagerWidget::OnTitleClicked);
}

void UEndGameManagerWidget::OnTitleClicked()
{
	UGameplayStatics::OpenLevel(this, TEXT("GameTitle"));
	UGameplayStatics::DeleteGameInSlot(TEXT("DefenseSaveSlot"), 0);
}

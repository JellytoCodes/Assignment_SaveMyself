// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialManagerWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UTutorialManagerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(ButtonClose) ButtonClose->OnClicked.AddDynamic(this, &UTutorialManagerWidget::OnCloseClicked);
}

void UTutorialManagerWidget::OnCloseClicked()
{
	UGameplayStatics::OpenLevel(this, FName("Stage_01"));
}

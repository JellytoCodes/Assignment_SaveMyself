// Fill out your copyright notice in the Description page of Project Settings.

#include "StageWidget.h"
#include "Components/TextBlock.h"
#include "TimerManager.h"

void UStageWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(Text_StageMessage)
	{
		Text_StageMessage->SetText(FText::FromString(""));
		Text_StageMessage->SetRenderOpacity(0.f);
	}
}

void UStageWidget::SetStageText(FText InText)
{
	if(!Text_StageMessage) return;

	Text_StageMessage->SetText(InText);
	Text_StageMessage->SetRenderOpacity(1.f);

	GetWorld()->GetTimerManager().ClearTimer(HideTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(HideTimerHandle, this, &UStageWidget::RemoveText, 1.5f, false);
}

void UStageWidget::RemoveText()
{
	if(Text_StageMessage)
	{
		Text_StageMessage->RemoveFromParent();
	}
}

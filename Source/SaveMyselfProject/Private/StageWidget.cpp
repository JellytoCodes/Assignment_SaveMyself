// Fill out your copyright notice in the Description page of Project Settings.

#include "StageWidget.h"
#include "Components/TextBlock.h"
#include "TimerManager.h"

void UStageWidget::SetStageNumberText(FName inStageID)
{
	if(TextStageNumber) TextStageNumber->SetText(FText::FromName(inStageID));
}

void UStageWidget::UpdatePhaseTimeText(EStageState inState, int32 remainingTime)
{
	if(!TextPhaseTime) return;

	FString PhaseStr;
	switch(inState)
	{
		case EStageState::Prepare: 
			PhaseStr = TEXT("Prepare Phase"); 
		break;

		case EStageState::Battle: 
			PhaseStr = TEXT("Battle Phase"); 
		break;
	}

	int32 Min = remainingTime / 60;
	int32 Sec = remainingTime % 60;

	TextPhaseTime->SetText(FText::FromString(FString::Printf(TEXT("%s %02d:%02d"), *PhaseStr, Min, Sec)));
}

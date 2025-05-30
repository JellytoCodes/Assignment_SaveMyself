// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StageManagerComponent.h"
#include "StageWidget.generated.h"

class UTextBlock;

UCLASS()
class SAVEMYSELFPROJECT_API UStageWidget : public UUserWidget
{
	GENERATED_BODY()

protected :
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextStageNumber;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextPhaseTime;

public :
	void SetStageNumberText(FName inStageID);
	void UpdatePhaseTimeText(EStageState inState, int32 remainingTime);
};

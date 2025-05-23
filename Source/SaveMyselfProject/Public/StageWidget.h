// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StageWidget.generated.h"

class UTextBlock;

UCLASS()
class SAVEMYSELFPROJECT_API UStageWidget : public UUserWidget
{
	GENERATED_BODY()

public :

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "Stage")
	void SetStageText(FText InText);

protected :
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_StageMessage;

	FTimerHandle HideTimerHandle;

	void RemoveText();
};

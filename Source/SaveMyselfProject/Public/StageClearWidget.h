// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StageClearWidget.generated.h"

/**
 * 
 */
UCLASS()
class SAVEMYSELFPROJECT_API UStageClearWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonNextStage;

private :
	UFUNCTION()
	void OnNextStageClicked();
};

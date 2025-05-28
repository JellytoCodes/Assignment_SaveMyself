// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndGameManagerWidget.generated.h"

class UButton;

UCLASS()
class SAVEMYSELFPROJECT_API UEndGameManagerWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonTitle;

private :
	UFUNCTION()
	void OnTitleClicked();
};

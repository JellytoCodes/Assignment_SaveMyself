// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TryAgainWidget.generated.h"

class UButton;

UCLASS()
class SAVEMYSELFPROJECT_API UTryAgainWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonReTry;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonQuit;

private :
	UFUNCTION()
	void OnReTryClicked();
	
	UFUNCTION()
	void OnReQuitClicked();
};

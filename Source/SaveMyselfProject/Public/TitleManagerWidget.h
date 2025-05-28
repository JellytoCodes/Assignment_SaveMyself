// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleManagerWidget.generated.h"

class UButton;

UCLASS()
class SAVEMYSELFPROJECT_API UTitleManagerWidget : public UUserWidget
{
	GENERATED_BODY()

private :
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnstartClicked();

	UFUNCTION()
	void OnLoadClicked();

	UFUNCTION()
	void OnSettingClicked();

	UFUNCTION()
	void OnQuitClicked();

public :
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonStart;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonLoad;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonSetting;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonQuit;
};

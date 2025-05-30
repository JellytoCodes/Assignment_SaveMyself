﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleManagerWidget.generated.h"

class UButton;
class UImage;
class UTextBlock;

UCLASS()
class SAVEMYSELFPROJECT_API UTitleManagerWidget : public UUserWidget
{
	GENERATED_BODY()

private :
	virtual void NativeConstruct() override;

	UFUNCTION() void OnStartClicked();
	UFUNCTION() void OnStartHovered();
	UFUNCTION() void OnStartUnhovered();

	UFUNCTION() void OnLoadClicked();
	UFUNCTION() void OnLoadHovered();
	UFUNCTION() void OnLoadUnhovered();

	UFUNCTION() void OnSettingClicked();
	UFUNCTION() void OnSettingHovered();
	UFUNCTION() void OnSettingUnhovered();

	UFUNCTION() void OnQuitClicked();		
	UFUNCTION() void OnQuitHovered();
	UFUNCTION() void OnQuitUnhovered();

	/* Hierarchy List*/
	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UButton* ButtonStart;

	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UImage* ImageStart;

	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UButton* ButtonLoad;

	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UImage* ImageLoad;

	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UTextBlock* TextLoad;

	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UButton* ButtonSetting;

	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UImage* ImageSetting;

	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UButton* ButtonQuit;

	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UImage* ImageQuit;
};

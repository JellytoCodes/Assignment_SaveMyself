// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TryAgainWidget.generated.h"

class UButton;
class UImage;

UCLASS()
class SAVEMYSELFPROJECT_API UTryAgainWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	virtual void NativeConstruct() override;



private :
	UFUNCTION() void OnRetryClicked();
	UFUNCTION() void OnRetryHovered();
	UFUNCTION() void OnRetryUnhovered();
	
	UFUNCTION() void OnQuitClicked();
	UFUNCTION() void OnQuitHovered();
	UFUNCTION() void OnQuitUnhovered();

	/* Hierarchy List*/
	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UButton* ButtonRetry;

	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UImage* ImageRetry;

	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UButton* ButtonQuit;

	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UImage* ImageQuit;
};

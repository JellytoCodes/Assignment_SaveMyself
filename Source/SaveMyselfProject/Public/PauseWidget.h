// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"

class UButton;
class UImage;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPauseWidgetClosed);

UCLASS()
class SAVEMYSELFPROJECT_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()

private :
	virtual void NativeConstruct() override;

	UFUNCTION() void OnContinueClicked();	
	UFUNCTION() void OnContinueHovered();
	UFUNCTION() void OnContinueUnhovered();

	UFUNCTION() void OnRetryClicked();
	UFUNCTION() void OnRetryHovered();
	UFUNCTION() void OnRetryUnhovered();

	UFUNCTION() void OnTitleMenuClicked();
	UFUNCTION() void OnTitleMenuHovered();
	UFUNCTION() void OnTitleMenuUnhovered();

	UFUNCTION() void OnQuitClicked();		
	UFUNCTION() void OnQuitHovered();
	UFUNCTION() void OnQuitUnhovered();

	/* Hierarchy List*/
	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UButton* ButtonContinue;

	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UImage* ImageContinue;

	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UButton* ButtonRetry;

	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UImage* ImageRetry;

	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UButton* ButtonTitleMenu;

	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UImage* ImageTitleMenu;

	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UButton* ButtonQuit;

	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UImage* ImageQuit;

public :
	UPROPERTY(BlueprintAssignable)
	FOnPauseWidgetClosed OnPauseWidgetClosed;
};

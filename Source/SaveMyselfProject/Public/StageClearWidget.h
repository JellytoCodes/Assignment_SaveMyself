// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StageClearWidget.generated.h"

class UButton;
class UImage;

UCLASS()
class SAVEMYSELFPROJECT_API UStageClearWidget : public UUserWidget
{
	GENERATED_BODY()

private :
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true")) 
	class UButton* ButtonNextStage;

	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UImage* ImageNextStage;

	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true")) 
	class UButton* ButtonTitleMenu;

	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UImage* ImageTitleMenu;
	
	UFUNCTION() void OnNextStageClicked();
	UFUNCTION() void OnNextStageHovered();
	UFUNCTION() void OnNextStageUnhovered();

	UFUNCTION() void OnTitleMenuClicked();
	UFUNCTION() void OnTitleMenuHovered();
	UFUNCTION() void OnTitleMenuUnhovered();

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHPWidget.generated.h"

class UImage;

UCLASS()
class SAVEMYSELFPROJECT_API UPlayerHPWidget : public UUserWidget
{
	GENERATED_BODY()

protected : 
	UPROPERTY(meta = (BindWidget))	
	UImage* HP_1;

	UPROPERTY(meta = (BindWidget))	
	UImage* HP_2;

	UPROPERTY(meta = (BindWidget))	
	UImage* HP_3;

	UPROPERTY(meta = (BindWidget))	
	UImage* HP_4;

	UPROPERTY(meta = (BindWidget))	
	UImage* HP_5;

public :
	void UpdatedPlayerHPWidget(int32 index);
};

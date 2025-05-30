// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "EndGameManagerHUD.generated.h"

/**
 * 
 */
UCLASS()
class SAVEMYSELFPROJECT_API AEndGameManagerHUD : public AHUD
{
	GENERATED_BODY()
public :
	AEndGameManagerHUD();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UEndGameManagerWidget> EndGameWidgetClass;

protected :
	virtual void BeginPlay() override;
};

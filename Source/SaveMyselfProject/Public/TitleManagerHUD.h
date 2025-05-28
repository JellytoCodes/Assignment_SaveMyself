// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TitleManagerHUD.generated.h"

/**
 * 
 */
UCLASS()
class SAVEMYSELFPROJECT_API ATitleManagerHUD : public AHUD
{
	GENERATED_BODY()

public :
	ATitleManagerHUD();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UTitleManagerWidget> titleWidgetClass;

protected :
	virtual void BeginPlay() override;


};

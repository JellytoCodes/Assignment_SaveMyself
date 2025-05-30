// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TutorialManagerHUD.generated.h"

/**
 * 
 */
UCLASS()
class SAVEMYSELFPROJECT_API ATutorialManagerHUD : public AHUD
{
	GENERATED_BODY()
public :
	ATutorialManagerHUD();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UTutorialManagerWidget> tutorialWidgetClass;

protected :
	virtual void BeginPlay() override;
};

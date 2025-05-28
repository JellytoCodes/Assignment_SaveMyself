// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TutorialManagerHUD.h"
#include "TutorialManagerBase.generated.h"

/**
 * 
 */
UCLASS()
class SAVEMYSELFPROJECT_API ATutorialManagerBase : public AGameModeBase
{
	GENERATED_BODY()

public :	
	ATutorialManagerBase()
	{
		HUDClass = ATutorialManagerHUD::StaticClass();
	}

protected :
	virtual void BeginPlay() override;
};

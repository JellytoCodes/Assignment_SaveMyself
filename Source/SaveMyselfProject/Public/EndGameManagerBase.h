// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndGameManagerHUD.h"
#include "EndGameManagerBase.generated.h"

/**
 * 
 */
UCLASS()
class SAVEMYSELFPROJECT_API AEndGameManagerBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AEndGameManagerBase()
	{
		HUDClass = AEndGameManagerHUD::StaticClass();
	}

protected :
	virtual void BeginPlay() override;
};

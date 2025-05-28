// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TitleManagerHUD.h"
#include "TitleManagerBase.generated.h"

/**
 * 
 */
UCLASS()
class SAVEMYSELFPROJECT_API ATitleManagerBase : public AGameModeBase
{
	GENERATED_BODY()

public :
	ATitleManagerBase()
	{
		HUDClass = ATitleManagerHUD::StaticClass();
	}
};

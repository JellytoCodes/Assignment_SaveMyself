// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StageManagerComponent.h"
#include "DefenseGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SAVEMYSELFPROJECT_API ADefenseGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public :
	ADefenseGameModeBase();

	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	class UStageManagerComponent* StageManager;

	UFUNCTION()
	void HandleStageState(EStageState NewState);
};

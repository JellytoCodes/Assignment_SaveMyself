﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NormalMonsterCon.generated.h"

UCLASS()
class SAVEMYSELFPROJECT_API ANormalMonsterCon : public AAIController
{
	GENERATED_BODY()

public :
	ANormalMonsterCon();

protected :

	virtual void OnPossess(APawn* InPawn) override;

private :

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly,Category = "Perception", meta = (AllowPrivateAccess = "true"))
	class ANormalMonster* ControlledMonster;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly,Category = "Perception", meta = (AllowPrivateAccess = "true"))
	class UAIPerceptionComponent* PerceptionComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly,Category = "Perception", meta = (AllowPrivateAccess = "true"))
	class UAISenseConfig_Sight* SightConfig;

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	TArray<AActor*> FoundRegions;
	int32 regionIndex = 0;

public :
	void HandleIdle();
	void HandlePatrol();
	void HandleChase();
	void HandleAttack();

	void EvaluateState();
};
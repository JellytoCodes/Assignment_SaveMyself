// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NormalMonsterCon.generated.h"

/**
 * 
 */
UCLASS()
class SAVEMYSELFPROJECT_API ANormalMonsterCon : public AAIController
{
	GENERATED_BODY()

public :
	ANormalMonsterCon();

protected :
	
	virtual void Tick(float DeltaTime) override;
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY()
	class ANormalMonster* ControlledMonster;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	class UAIPerceptionComponent* PerceptionComp;

	UPROPERTY()
	class UAISenseConfig_Sight* SightConfig;

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float AttackRange = 200.f;

public :
	void HandleIdle();
	void HandlePatrol();
	void HandleChase();
	void HandleAttack();

	void EvaluateState();

	float GetAttackRange() { return AttackRange; }
};

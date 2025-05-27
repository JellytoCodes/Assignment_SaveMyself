// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EliteMonsterCon.generated.h"

UCLASS()
class SAVEMYSELFPROJECT_API AEliteMonsterCon : public AAIController
{
	GENERATED_BODY()

public :
	AEliteMonsterCon();
protected :

	virtual void OnPossess(APawn* InPawn) override;

private :

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly,Category = "Perception", meta = (AllowPrivateAccess = "true"))
	class AEliteMonster* ControlledMonster;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly,Category = "Perception", meta = (AllowPrivateAccess = "true"))
	class UAIPerceptionComponent* PerceptionComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly,Category = "Perception", meta = (AllowPrivateAccess = "true"))
	class UAISenseConfig_Sight* SightConfig;

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float AttackRange = 200.f;

	TArray<AActor*> FoundRegions;
	int32 regionIndex = 0;

public :
	void HandleIdle();
	void HandlePatrol();
	void HandleChase();
	void HandleAttack();

	void EvaluateState();

	float GetAttackRange() { return AttackRange; }	
};

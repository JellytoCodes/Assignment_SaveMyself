// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterBase.h"
#include "EliteMonster.generated.h"

UCLASS()
class SAVEMYSELFPROJECT_API AEliteMonster : public AMonsterBase
{
	GENERATED_BODY()
public :
	AEliteMonster();

protected :
	virtual void Tick(float DeltaTime) override;
	
	virtual void OnEnterIdle() override;
	virtual void OnEnterPatrol() override;
	virtual void OnEnterChase() override;
	virtual void OnEnterAttack() override;
	virtual void OnEnterDamage() override;
	virtual void OnEnterDead() override;

	float attackPower = 10;
	float attackElapsedTime = 0.f;
	float attackInterval = 3.f;
	float attackRange = 150.f;

	bool bCanEvaluateState = true;

public :
	void TryAttack(float DeltaTime);
	float GetAttackRange() { return attackRange;}
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterBase.h"
#include "NormalMonster.generated.h"

UCLASS()
class SAVEMYSELFPROJECT_API ANormalMonster : public AMonsterBase
{
	GENERATED_BODY()

public :
	ANormalMonster();

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
	float attackInterval = 5.f;
	float attackRange = 150.f;

public :
	void EquipWeapon();
	void TryAttack();
	float GetAttackRange() { return attackRange;}
};

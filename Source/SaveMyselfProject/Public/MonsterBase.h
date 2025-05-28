// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DamagebleInterface.h"
#include "MonsterMasterTable.h"
#include "MonsterBase.generated.h"

UENUM(BlueprintType)
enum class EMonsterState : uint8
{
    Idle,		//대기 상태
    Patrol,		//목표 지점(맵끝) 이동
    Chase,		//플레이어, 구조물 대상 추적
    Attack,		//대상 공격
    Damage,		//피격 반응
    Dead,		//사망 처리
};

UCLASS()
class SAVEMYSELFPROJECT_API AMonsterBase : public ACharacter, public IDamagebleInterface
{
	GENERATED_BODY()

public:
	AMonsterBase();

protected:
	virtual void BeginPlay() override;

protected : 
	//몬스터 공통 스탯
	float maxHP;
	float curHP;
	float moveSpeed;
	float attackPower;
	float attackElapsedTime;
	float attackInterval;
	float attackRange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MonsterState")
	EMonsterState curState = EMonsterState::Idle;

	EMonsterType monsterType;
	EEliteAIType eliteAIType;
	class UStaticMesh* weaponMesh;

	void LoadMonsterData();
	void ApplyStat();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MonsterID")
	FName MonsterID;	

	//상속 클래스 가상 함수 적용을 위한 선언
	virtual void OnEnterIdle() { /*NULL*/ }
	virtual void OnEnterPatrol() { /*NULL*/ }
	virtual void OnEnterChase() { /*NULL*/ }
	virtual void OnEnterAttack() { /*NULL*/ }
	virtual void OnEnterDamage() { /*NULL*/ }
	virtual void OnEnterDead() { /*NULL*/ }

	UPROPERTY()
	AActor* TargetActor;

	virtual void ReceiveDamage_Implementation(float Damage) override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Nav")
	class UNavigationInvokerComponent* NavInvoker;

	void EquipWeapon();

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	FVector FinalGoalLocation;

	UPROPERTY()
	class AMonsterSpawner* OwnerSpawner;

	void Dead();

public : //Getter & Setter 관리
	FORCEINLINE void SetTargetActor(AActor* NewTarget) { TargetActor = NewTarget; }
	FORCEINLINE AActor* GetTargetActor() const { return TargetActor; }

	void SetMonsterState(EMonsterState NewState); 
	EMonsterState GetMonsterState() const { return curState; }

	float GetAttackRange() const { return attackRange;}
};

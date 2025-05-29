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
    Idle,		//��� ����
    Patrol,		//��ǥ ����(�ʳ�) �̵�
    Chase,		//�÷��̾�, ������ ��� ����
    Attack,		//��� ����
    Damage,		//�ǰ� ����
    Dead,		//��� ó��
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MonsterState")
	EMonsterState curState = EMonsterState::Patrol;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MonsterID")
	FName MonsterID;	

	UPROPERTY()
	AActor* TargetActor;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Nav")
	class UNavigationInvokerComponent* NavInvoker;

	//���� ���� ����
	float maxHP;
	float curHP;
	float moveSpeed;
	float attackPower;
	float attackElapsedTime;
	float attackInterval;
	float attackRange;
	EMonsterType monsterType;
	EEliteAIType eliteAIType;
	class UStaticMesh* weaponMesh;

	void LoadMonsterData();
	void ApplyStat();
	void EquipWeapon();
	virtual void ReceiveDamage_Implementation(float Damage) override;

	//��� Ŭ���� ���� �Լ� ������ ���� ����
	virtual void OnEnterIdle() { /*NULL*/ }
	virtual void OnEnterPatrol() { /*NULL*/ }
	virtual void OnEnterChase() { /*NULL*/ }
	virtual void OnEnterAttack() { /*NULL*/ }
	virtual void OnEnterDamage() { /*NULL*/ }
	virtual void OnEnterDead() { /*NULL*/ }

	//State ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State")
	bool isDeath = false;

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	FVector FinalGoalLocation;

	UPROPERTY()
	class AMonsterSpawner* OwnerSpawner;

	void Dead();
	
public : //Getter & Setter ����
	FORCEINLINE void SetTargetActor(AActor* NewTarget) { TargetActor = NewTarget; }
	FORCEINLINE AActor* GetTargetActor() const { return TargetActor; }

	void SetMonsterState(EMonsterState NewState); 
	EMonsterState GetMonsterState() const { return curState; }

	float GetAttackRange() const { return attackRange;}
};

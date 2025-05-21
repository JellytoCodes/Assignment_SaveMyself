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

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected : 
	//���� ���� ����
	float maxHP;
	float curHP;
	float moveSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MonsterState")
	EMonsterState curState;

	EMonsterType monsterType;
	EEliteAIType eliteAIType;
	FName monsterWeaponID;

	void LoadMonsterData();
	void ApplyStat();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MonsterID")
	FName MonsterID;	

	virtual void OnEnterIdle();
	virtual void OnEnterPatrol();
	virtual void OnEnterChase();
	virtual void OnEnterAttack();
	virtual void OnEnterDamage();
	virtual void OnEnterDead();

	UPROPERTY()
	AActor* TargetActor;

	virtual void ReceiveDamage_Implementation(float Damage) override;

public :
	void SetTargetActor(AActor* NewTarget) { TargetActor = NewTarget; }
	AActor* GetTargetActor() const { return TargetActor; }

	void SetMonsterState(EMonsterState NewState); 
	const EMonsterState GetMonsterState() { return curState; }

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	FVector FinalGoalLocation;

	void Dead();
};

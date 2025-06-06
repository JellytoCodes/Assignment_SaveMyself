﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NavigationInvokerComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"
#include "Engine/DataTable.h"
#include "MonsterSpawner.h"

// Sets default values
AMonsterBase::AMonsterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	GetCharacterMovement()->bUseRVOAvoidance = false;

	SoundOutComp = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundOutComp"));
	SoundOutComp->SetupAttachment(RootComponent);
	SoundOutComp->bAutoActivate = true;

	//건축 완료 사운드 설정
	static ConstructorHelpers::FObjectFinder<USoundBase> tempDeadSound
	(TEXT("/Script/Engine.SoundWave'/Game/Asset/Sound/SW_MonsterDead.SW_MonsterDead'"));

	if(tempDeadSound.Succeeded()) DeadSound = tempDeadSound.Object;
	
	//건축 완료 사운드 설정
	static ConstructorHelpers::FObjectFinder<USoundBase> tempAttackSound
	(TEXT("/Script/Engine.SoundWave'/Game/Asset/Sound/SW_MonsterAttack.SW_MonsterAttack'"));

	if(tempAttackSound.Succeeded()) AttackSound = tempAttackSound.Object;

	NavInvoker = CreateDefaultSubobject<UNavigationInvokerComponent>(TEXT("NavInvoker"));
	
	Tags.Add(FName("Monster"));
}

// Called when the game starts or when spawned
void AMonsterBase::BeginPlay()
{
	Super::BeginPlay();

	LoadMonsterData();
}

void AMonsterBase::LoadMonsterData()
{
	static const FString ContextStr(TEXT("MonsterStat Context"));

	const auto MonsterData = LoadObject<UDataTable>(nullptr, TEXT("/Game/DataTable/DT_MonsterStatRow.DT_MonsterStatRow"));
	if(!MonsterData) return;
	
	const auto StatRow = MonsterData->FindRow<FMonsterStatRow>(MonsterID, ContextStr);
	if(!StatRow) return;

	monsterType = StatRow->MonsterType;
	eliteAIType = StatRow->EliteAIType;
	weaponMesh = StatRow->WeaponMesh;
	maxHP = StatRow->MaxHP;
	curHP = maxHP;
	moveSpeed = FMath::RandRange(StatRow->MinMoveSpeed, StatRow->MaxMoveSpeed);
	attackPower = StatRow->AttackPower;
	attackInterval = StatRow->AttackInterval;
	attackRange = StatRow->AttackRange;
	attackElapsedTime = attackInterval;
	GetCharacterMovement()->MaxWalkSpeed = moveSpeed;

	EquipWeapon();
}

void AMonsterBase::ApplyStat()
{
	GetCharacterMovement()->MaxWalkSpeed = moveSpeed;
}

void AMonsterBase::SetMonsterState(EMonsterState NewState)
{
	if(bIsDeath) return;

	curState = NewState;

	switch(NewState)
	{
		case EMonsterState::Idle :
			OnEnterIdle();
		break;

		case EMonsterState::Patrol :
			OnEnterPatrol();
		break;

		case EMonsterState::Chase :
			OnEnterChase();
		break;

		case EMonsterState::Attack :
			OnEnterAttack();
		break;

		case EMonsterState::Damage :
			OnEnterDamage();
		break;

		case EMonsterState::Dead:
			OnEnterDead();
		break;
	}
}

void AMonsterBase::Dead()
{
	if(OwnerSpawner) OwnerSpawner->OnMonsterDied(this);
	if(GetCharacterMovement()) GetCharacterMovement()->DisableMovement();
	if(GetCapsuleComponent()) GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	if(!SoundOutComp->IsPlaying())
	{
		SoundOutComp->SetSound(DeadSound);
		SoundOutComp->Play();
	}

	bIsDeath = true;
	SetLifeSpan(1.3f);
}

void AMonsterBase::ReceiveDamage_Implementation(float Damage)
{
	curHP -= Damage;
	if(curHP > 0)
	{
		SetMonsterState(EMonsterState::Damage);
	}
	else
	{
		curHP = 0;
		SetMonsterState(EMonsterState::Dead);
	}
}

void AMonsterBase::EquipWeapon()
{
	if(!weaponMesh) return;

	UStaticMeshComponent* WeaponMeshComp = NewObject<UStaticMeshComponent>(this);
	WeaponMeshComp->RegisterComponent();
	WeaponMeshComp->SetStaticMesh(weaponMesh);

	WeaponMeshComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("armRightSocket"));
	WeaponMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponMeshComp->SetGenerateOverlapEvents(false);
}
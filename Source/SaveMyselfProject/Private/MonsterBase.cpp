// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/DataTable.h"

// Sets default values
AMonsterBase::AMonsterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMonsterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMonsterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMonsterBase::LoadMonsterData()
{
	static const FString ContextStr(TEXT("MonsterStat COntext"));

	const auto MonsterData = LoadObject<UDataTable>(nullptr, TEXT("/Game/DataTable/DT_MonsterStatRow.DT_MonsterStatRow"));
	if(MonsterData) return;
	
	const auto StatRow = MonsterData->FindRow<FMonsterStatRow>(MonsterID, ContextStr);
	if(!StatRow) return;

	monsterType = StatRow->MonsterType;
	eliteAIType = StatRow->EliteAIType;
	monsterWeaponID = StatRow->MonsterWeaponID;
	maxHP = StatRow->MaxHP;
	curHP = maxHP;
	moveSpeed = StatRow->MoveSpeed;
}

void AMonsterBase::ApplyStat()
{
	GetCharacterMovement()->MaxWalkSpeed = moveSpeed;
}

void AMonsterBase::SetMonsterState(EMonsterState NewState)
{
	if(curState == NewState) return;

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

void AMonsterBase::OnEnterIdle()
{
	UE_LOG(LogTemp, Log, TEXT("Entered Idle State"));
}

void AMonsterBase::OnEnterPatrol()
{
	UE_LOG(LogTemp, Log, TEXT("Entered Patrol State"));
}

void AMonsterBase::OnEnterChase()
{
	UE_LOG(LogTemp, Log, TEXT("Entered Chase State"));
}

void AMonsterBase::OnEnterAttack()
{
	UE_LOG(LogTemp, Log, TEXT("Entered Attack State"));
}

void AMonsterBase::OnEnterDamage()
{
	UE_LOG(LogTemp, Log, TEXT("Entered Damage State"));
}

void AMonsterBase::OnEnterDead()
{
	UE_LOG(LogTemp, Log, TEXT("Entered Dead State"));
}

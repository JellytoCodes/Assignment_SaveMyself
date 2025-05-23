// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NavigationInvokerComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DataTable.h"

// Sets default values
AMonsterBase::AMonsterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	GetCharacterMovement()->bUseRVOAvoidance = false;

	NavInvoker = CreateDefaultSubobject<UNavigationInvokerComponent>(TEXT("NavInvoker"));
}

// Called when the game starts or when spawned
void AMonsterBase::BeginPlay()
{
	Super::BeginPlay();

	LoadMonsterData();

	UE_LOG(LogTemp, Log, TEXT("monster Type : %d"), monsterType);
	UE_LOG(LogTemp, Log, TEXT("elite AI Type : %d"), eliteAIType);
	UE_LOG(LogTemp, Log, TEXT("monsterWeaponID : %s"), *monsterWeaponID.ToString());
	UE_LOG(LogTemp, Log, TEXT("max HP : %.2f"), maxHP);
	UE_LOG(LogTemp, Log, TEXT("cur HP : %.2f"), curHP);
	UE_LOG(LogTemp, Log, TEXT("moveSpeed : %.2f"), moveSpeed);
	UE_LOG(LogTemp, Log, TEXT("monsterWeaponID : %.2f"), GetCharacterMovement()->MaxWalkSpeed);
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
	static const FString ContextStr(TEXT("MonsterStat Context"));

	const auto MonsterData = LoadObject<UDataTable>(nullptr, TEXT("/Game/DataTable/DT_MonsterStatRow.DT_MonsterStatRow"));
	if(!MonsterData) return;
	
	const auto StatRow = MonsterData->FindRow<FMonsterStatRow>(MonsterID, ContextStr);
	if(!StatRow) return;

	monsterType = StatRow->MonsterType;
	eliteAIType = StatRow->EliteAIType;
	monsterWeaponID = StatRow->MonsterWeaponID;
	maxHP = StatRow->MaxHP;
	curHP = maxHP;
	moveSpeed = FMath::RandRange(StatRow->MinMoveSpeed, StatRow->MaxMoveSpeed);
	GetCharacterMovement()->MaxWalkSpeed = moveSpeed;
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

void AMonsterBase::Dead()
{
	UE_LOG(LogTemp, Log, TEXT("Monster Die"));
	GetCharacterMovement()->DisableMovement();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetActorRotation(FRotator(90.f, 0.f, 0.f));
	SetLifeSpan(3.f);
}

void AMonsterBase::ReceiveDamage_Implementation(float Damage)
{
	UE_LOG(LogTemp, Warning, TEXT("MonsterDamaged!"))
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
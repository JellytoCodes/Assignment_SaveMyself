// Fill out your copyright notice in the Description page of Project Settings.

#include "NormalMonster.h"
#include "NormalMonsterCon.h"
#include "DamagebleInterface.h"

ANormalMonster::ANormalMonster()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANormalMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(GetMonsterState() == EMonsterState::Attack)
	{
		attackElapsedTime += DeltaTime;
		if(attackElapsedTime > AttackInterval)
		{
			attackElapsedTime = 0.f;
			TryAttack();
			UE_LOG(LogTemp, Log, TEXT("Try Attack"));
		}
	}
}

void ANormalMonster::OnEnterIdle()
{
	if(auto* AICon = Cast<ANormalMonsterCon>(GetController()))
	{
		UE_LOG(LogTemp, Log, TEXT("[NormalMonster] Entered Idle State"));
		AICon->HandleIdle();
	}
}

void ANormalMonster::OnEnterPatrol()
{
	if(auto* AICon = Cast<ANormalMonsterCon>(GetController()))
	{
		UE_LOG(LogTemp, Log, TEXT("[NormalMonster] Entered Patrol State"));
		AICon->HandlePatrol();
	}
}

void ANormalMonster::OnEnterChase()
{
	if(auto* AICon = Cast<ANormalMonsterCon>(GetController()))
	{
		UE_LOG(LogTemp, Log, TEXT("[NormalMonster] Entered Chase State"));
		AICon->HandleChase();
	}
}

void ANormalMonster::OnEnterAttack()
{
	UE_LOG(LogTemp, Log, TEXT("[NormalMonster] Entered Attack State"));
	//EquipWeapon();
	if(auto* AICon = Cast<ANormalMonsterCon>(GetController()))
	{
		AICon->HandleAttack();
		attackElapsedTime = 0;
	}
}

void ANormalMonster::OnEnterDamage()
{
	UE_LOG(LogTemp, Log, TEXT("[NormalMonster] Entered Damage State"));
	//���⼭ �ٷ� �浹 ó���� HP ���� �ݿ� ����
}

void ANormalMonster::OnEnterDead()
{
	UE_LOG(LogTemp, Log, TEXT("[NormalMonster] Entered Dead State"));
	//�ִϸ��̼� ��� �� Destroy() ���� ����
	Dead();
}

void ANormalMonster::EquipWeapon()
{
	
}

void ANormalMonster::TryAttack()
{
	if(!TargetActor) return;

	auto* AICon = Cast<ANormalMonsterCon>(GetController());
	if(!AICon) return;
	
	const float Distance = FVector::Dist(TargetActor->GetActorLocation(), GetActorLocation());
	if(Distance > AICon->GetAttackRange()) return;

	if(TargetActor->Implements<UDamagebleInterface>())
	{
		if(TargetActor->ActorHasTag(FName("Structure")))
		{
			IDamagebleInterface::Execute_ReceiveDamage(TargetActor, attackPower);
		}
		else if(TargetActor->ActorHasTag(FName("Player")))
		{
			IDamagebleInterface::Execute_ReceiveDamage(TargetActor, 1);
		}
	}
}
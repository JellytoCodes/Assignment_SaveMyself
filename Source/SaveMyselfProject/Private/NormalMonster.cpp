// Fill out your copyright notice in the Description page of Project Settings.

#include "NormalMonster.h"
#include "NormalMonsterCon.h"
#include "DamagebleInterface.h"

void ANormalMonster::OnEnterIdle()
{
	UE_LOG(LogTemp, Log, TEXT("[NormalMonster] Entered Idle State"));
	if(auto* AICon = Cast<ANormalMonsterCon>(GetController()))
	{
		AICon->HandleIdle();
	}
}

void ANormalMonster::OnEnterPatrol()
{
	UE_LOG(LogTemp, Log, TEXT("[NormalMonster] Entered Patrol State"));
	if(auto* AICon = Cast<ANormalMonsterCon>(GetController()))
	{
		AICon->HandlePatrol();
	}
}

void ANormalMonster::OnEnterChase()
{
	UE_LOG(LogTemp, Log, TEXT("[NormalMonster] Entered Chase State"));
	if(auto* AICon = Cast<ANormalMonsterCon>(GetController()))
	{
		AICon->HandleChase();
	}
}

void ANormalMonster::OnEnterAttack()
{
	UE_LOG(LogTemp, Log, TEXT("[NormalMonster] Entered Attack State"));
	EquipWeapon();
	if(auto* AICon = Cast<ANormalMonsterCon>(GetController()))
	{
		AICon->HandleAttack();
	}
}

void ANormalMonster::OnEnterDamage()
{
	UE_LOG(LogTemp, Log, TEXT("[NormalMonster] Entered Damage State"));
	//여기서 바로 충돌 처리로 HP 감소 반영 예정
}

void ANormalMonster::OnEnterDead()
{
	UE_LOG(LogTemp, Log, TEXT("[NormalMonster] Entered Dead State"));
	//애니메이션 재생 후 Destroy() 구현 예정
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
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
}

void ANormalMonster::OnEnterIdle()
{
	if(auto* AICon = Cast<ANormalMonsterCon>(GetController()))
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] Entered Idle State"), *GetName());
		AICon->HandleIdle();
	}
}

void ANormalMonster::OnEnterPatrol()
{
	if (auto* AICon = Cast<ANormalMonsterCon>(GetController()))
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] Entered Patrol State"), *GetName());
		AICon->HandlePatrol();
	}
}

void ANormalMonster::OnEnterChase()
{
	if(auto* AICon = Cast<ANormalMonsterCon>(GetController()))
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] Entered Chase State"), *GetName());
		AICon->HandleChase();
	}
}

void ANormalMonster::OnEnterAttack()
{
	UE_LOG(LogTemp, Log, TEXT("[%s] Entered Attack State"), *GetName());
	//EquipWeapon();
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
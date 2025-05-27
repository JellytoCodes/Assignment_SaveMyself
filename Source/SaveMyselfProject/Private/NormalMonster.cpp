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

	if(bCanEvaluateState)
	{
		if(auto* AICon = Cast<ANormalMonsterCon>(GetController()))
		{
			AICon->EvaluateState();
		}
	}

	if(GetMonsterState() == EMonsterState::Attack)
	{
		TryAttack(DeltaTime);
	}
}

void ANormalMonster::OnEnterIdle()
{
	if(auto* AICon = Cast<ANormalMonsterCon>(GetController()))
	{
		AICon->HandleIdle();
	}
}

void ANormalMonster::OnEnterPatrol()
{
	if (auto* AICon = Cast<ANormalMonsterCon>(GetController()))
	{
		AICon->HandlePatrol();
	}
}

void ANormalMonster::OnEnterChase()
{
	if(auto* AICon = Cast<ANormalMonsterCon>(GetController()))
	{
		AICon->HandleChase();
	}
}

void ANormalMonster::OnEnterAttack()
{
	bCanEvaluateState = false;

	FTimerHandle EvaluateResumeTimer;
	GetWorld()->GetTimerManager().SetTimer(EvaluateResumeTimer, [this]()
	{
		bCanEvaluateState = true;
	}, 1.f, false);
}

void ANormalMonster::OnEnterDamage()
{
	//Polish �ݿ� ����
}

void ANormalMonster::OnEnterDead()
{
	//�ִϸ��̼� ��� �� Destroy() ���� ����
	Dead();
}

void ANormalMonster::TryAttack(float DeltaTime)
{
	if(!TargetActor) return;

	auto* AICon = Cast<ANormalMonsterCon>(GetController());
	if(!AICon) return;
	
	const float distance = FVector::Dist(TargetActor->GetActorLocation(), GetActorLocation());
	if(distance > AICon->GetAttackRange()) return;
	
	attackElapsedTime += DeltaTime;
	if(attackElapsedTime < attackInterval) return;

	attackElapsedTime = 0.f;

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
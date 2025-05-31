// Fill out your copyright notice in the Description page of Project Settings.

#include "NormalMonster.h"
#include "NormalMonsterCon.h"
#include "DamagebleInterface.h"
#include "MonsterAnim.h"

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

	FTimerHandle evaluateResumeTimer;
	GetWorld()->GetTimerManager().SetTimer(evaluateResumeTimer, [this]()
	{
		bCanEvaluateState = true;
	}, attackInterval, false);
}

void ANormalMonster::OnEnterDamage()
{
	UMonsterAnim* monsterAnim = Cast<UMonsterAnim>(GetMesh()->GetAnimInstance());
	if(monsterAnim) monsterAnim->PlayDamageMontage();
}

void ANormalMonster::OnEnterDead()
{
	UMonsterAnim* monsterAnim = Cast<UMonsterAnim>(GetMesh()->GetAnimInstance());
	if(monsterAnim) monsterAnim->PlayDeadMontage();

	Dead();
}

void ANormalMonster::TryAttack(float DeltaTime)
{
	if(!TargetActor) return;
	
	const float distance = FVector::Dist(TargetActor->GetActorLocation(), GetActorLocation());
	if(distance > GetAttackRange()) return;
	
	attackElapsedTime += DeltaTime;
	if(attackElapsedTime < attackInterval) return;

	attackElapsedTime = 0.f;

	UMonsterAnim* monsterAnim = Cast<UMonsterAnim>(GetMesh()->GetAnimInstance());
	if(monsterAnim) monsterAnim->PlayAttackMontage();

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
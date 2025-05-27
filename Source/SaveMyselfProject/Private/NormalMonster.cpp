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

	bCanEvaluateState = false;

	FTimerHandle EvaluateResumeTimer;
	GetWorld()->GetTimerManager().SetTimer(EvaluateResumeTimer, [this]()
	{
		bCanEvaluateState = true;
	}, 1.f, false);
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
		UE_LOG(LogTemp, Warning, TEXT("Try Attack Damaged"));
	}
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "EliteMonster.h"
#include "EliteMonsterCon.h"
#include "DamagebleInterface.h"

AEliteMonster::AEliteMonster()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEliteMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bCanEvaluateState)
	{
		if(auto* AICon = Cast<AEliteMonsterCon>(GetController()))
		{
			AICon->EvaluateState();
		}
	}

	if(GetMonsterState() == EMonsterState::Attack)
	{
		TryAttack(DeltaTime);
	}
}

void AEliteMonster::OnEnterIdle()
{
	if(auto* AICon = Cast<AEliteMonsterCon>(GetController()))
	{
		AICon->HandleIdle();
	}
}

void AEliteMonster::OnEnterPatrol()
{
	if (auto* AICon = Cast<AEliteMonsterCon>(GetController()))
	{
		AICon->HandlePatrol();
	}
}

void AEliteMonster::OnEnterChase()
{
	if(auto* AICon = Cast<AEliteMonsterCon>(GetController()))
	{
		AICon->HandleChase();
	}
}

void AEliteMonster::OnEnterAttack()
{
	bCanEvaluateState = false;

	FTimerHandle EvaluateResumeTimer;
	GetWorld()->GetTimerManager().SetTimer(EvaluateResumeTimer, [this]()
	{
		bCanEvaluateState = true;
	}, 1.f, false);
}

void AEliteMonster::OnEnterDamage()
{
	//Polish �ݿ� ����
}

void AEliteMonster::OnEnterDead()
{
	//�ִϸ��̼� ��� �� Destroy() ���� ����
	Dead();
}

void AEliteMonster::TryAttack(float DeltaTime)
{
	if(!TargetActor) return;

	auto* AICon = Cast<AEliteMonsterCon>(GetController());
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
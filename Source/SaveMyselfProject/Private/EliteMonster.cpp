// Fill out your copyright notice in the Description page of Project Settings.

#include "EliteMonster.h"
#include "EliteMonsterCon.h"
#include "DamagebleInterface.h"
#include "MonsterAnim.h"

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

	}, attackInterval, false);
}

void AEliteMonster::OnEnterDamage()
{
	UMonsterAnim* monsterAnim = Cast<UMonsterAnim>(GetMesh()->GetAnimInstance());
	if(monsterAnim) monsterAnim->PlayDamageMontage();
}

void AEliteMonster::OnEnterDead()
{
	UMonsterAnim* monsterAnim = Cast<UMonsterAnim>(GetMesh()->GetAnimInstance());
	if(monsterAnim) monsterAnim->PlayDeadMontage();

	Dead();
}

void AEliteMonster::TryAttack(float DeltaTime)
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
		UE_LOG(LogTemp, Warning, TEXT("Try Attack Damaged"));
	}
}
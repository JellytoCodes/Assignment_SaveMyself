// Fill out your copyright notice in the Description page of Project Settings.

#include "NormalMonster.h"
#include "NormalMonsterCon.h"

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
	//���⼭ �ٷ� �浹 ó���� HP ���� �ݿ� ����
}

void ANormalMonster::OnEnterDead()
{
	UE_LOG(LogTemp, Log, TEXT("[NormalMonster] Entered Dead State"));
	//�ִϸ��̼� ��� �� Destroy() ���� ����
}

void ANormalMonster::EquipWeapon()
{

}

void ANormalMonster::TryAttack()
{

}

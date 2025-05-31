// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterAnim.h"
#include "MonsterBase.h"

void UMonsterAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	auto ownerPawn = TryGetPawnOwner();
	auto player = Cast<AMonsterBase>(ownerPawn);

	if(player)
	{
		FVector velocity = player->GetVelocity();
		FVector rightVector = player->GetActorRightVector();
		hDirectionSpeed = FVector::DotProduct(rightVector, velocity);

		FVector forwardVector = player->GetActorForwardVector();
		vDirectionSpeed = FVector::DotProduct(forwardVector, velocity);
	}
}

void UMonsterAnim::PlayDeadMontage()
{
	if(!deadMontage) return;

	Montage_Play(deadMontage);
}

void UMonsterAnim::PlayAttackMontage()
{
	if(!attackMontage) return;

	Montage_Play(attackMontage, 1.3f);
}

void UMonsterAnim::PlayDamageMontage()
{
	if(!damageMontage) return;

	Montage_Play(damageMontage);
}

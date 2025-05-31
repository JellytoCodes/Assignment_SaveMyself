// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"
#include "DefenseCharacter.h"

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	auto ownerPawn = TryGetPawnOwner();
	auto player = Cast<ADefenseCharacter>(ownerPawn);

	if(player)
	{
		FVector velocity = player->GetVelocity();
		FVector rightVector = player->GetActorRightVector();
		hDirectionSpeed = FVector::DotProduct(rightVector, velocity);

		FVector forwardVector = player->GetActorForwardVector();
		vDirectionSpeed = FVector::DotProduct(forwardVector, velocity);
	}
}

void UPlayerAnim::PlayDeadMontage()
{
	if(!deadMontage) return;

	Montage_Play(deadMontage);
}

void UPlayerAnim::PlayThrowMontage()
{
	if(!throwMontage) return;

	Montage_Play(throwMontage, 1.5f);
}

void UPlayerAnim::PlayVictoryMontage()
{
	if(!victoryMontage) return;

	Montage_Play(victoryMontage, 1.5f);
}

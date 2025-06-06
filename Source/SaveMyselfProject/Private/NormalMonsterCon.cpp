﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "NormalMonsterCon.h"
#include "NormalMonster.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RegionPatrolPoint.h"

ANormalMonsterCon::ANormalMonsterCon()
{
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));
	SetPerceptionComponent(*PerceptionComp);

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	SightConfig->SightRadius = 500.f;
	SightConfig->LoseSightRadius = 600.f;
	SightConfig->PeripheralVisionAngleDegrees = 130.f;
	SightConfig->SetMaxAge(3.f);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	PerceptionComp->ConfigureSense(*SightConfig);
	PerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());
}

void ANormalMonsterCon::OnPossess(APawn *InPawn)
{
	Super::OnPossess(InPawn);

	ControlledMonster = Cast<ANormalMonster>(InPawn);

	if(PerceptionComp)
	{
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &ANormalMonsterCon::OnTargetPerceptionUpdated);
	}

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARegionPatrolPoint::StaticClass(), FoundRegions);
	if(FoundRegions.Num() > 0)
	{
		regionIndex = FMath::RandRange(0, FoundRegions.Num() - 1);
	}
}

void ANormalMonsterCon::HandleIdle()
{
	if(!ControlledMonster) return;

	ControlledMonster->GetMovementComponent()->StopMovementImmediately();
}

void ANormalMonsterCon::HandlePatrol()
{
	if (!ControlledMonster) return;

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn && LineOfSightTo(PlayerPawn))
	{
		FVector TargetLocation = PlayerPawn->GetActorLocation();
		ControlledMonster->FinalGoalLocation = TargetLocation;

		MoveToLocation(ControlledMonster->FinalGoalLocation);
	}

	else
	{
		AActor* PatrolTarget = FoundRegions[regionIndex];

		ControlledMonster->FinalGoalLocation = PatrolTarget->GetActorLocation();
		MoveToLocation(ControlledMonster->FinalGoalLocation);
	}
}

void ANormalMonsterCon::HandleChase()
{
	if(!ControlledMonster) return;

	AActor* Target = ControlledMonster->GetTargetActor();
	if(Target)
	{
		MoveToActor(Target);
	}
	else
	{
		ControlledMonster->SetMonsterState(EMonsterState::Patrol);
	}
}

void ANormalMonsterCon::HandleAttack() { /* NULL */ }

void ANormalMonsterCon::EvaluateState()
{
	if(!ControlledMonster || !PerceptionComp) return;

	TArray<AActor*> PerceivedActors;
	PerceptionComp->GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceivedActors);

	AActor* ClosestTarget = nullptr;
	float MinDistance = FLT_MAX;

	for(AActor* Actor : PerceivedActors)
	{
		if(Actor->IsA<AMonsterBase>()) continue;

		if(!Actor->ActorHasTag(FName("Structure")) && !Actor->ActorHasTag(FName("Player"))) continue;

		float Dist = FVector::Dist(Actor->GetActorLocation(), ControlledMonster->GetActorLocation());
		if(Dist < MinDistance)
		{
			MinDistance = Dist;
			ClosestTarget = Actor;
		}
	}

	if(ClosestTarget)
	{
		ControlledMonster->SetTargetActor(ClosestTarget);
		if(MinDistance <= ControlledMonster->GetAttackRange())
		{
			ControlledMonster->SetMonsterState(EMonsterState::Attack);
		}
		else
		{
			ControlledMonster->SetMonsterState(EMonsterState::Chase);
		}
	}
	else
	{
		ControlledMonster->SetMonsterState(EMonsterState::Patrol);	
	}
}

void ANormalMonsterCon::OnTargetPerceptionUpdated(AActor *Actor, FAIStimulus Stimulus)
{
	if(!Actor || !ControlledMonster) return;

	if(Actor->IsA<AMonsterBase>()) return;

	bool bIsStructure = Actor->ActorHasTag(FName("Structure"));
	bool bIsPlayer = Actor->ActorHasTag(FName("Player"));
}
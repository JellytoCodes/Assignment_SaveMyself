// Fill out your copyright notice in the Description page of Project Settings.


#include "NormalMonsterCon.h"
#include "NormalMonster.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

ANormalMonsterCon::ANormalMonsterCon()
{
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));
	SetPerceptionComponent(*PerceptionComp);

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	SightConfig->SightRadius = 1000.f;
	SightConfig->LoseSightRadius = 1200.f;
	SightConfig->PeripheralVisionAngleDegrees = 150.f;
	SightConfig->SetMaxAge(5.f);

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
}

void ANormalMonsterCon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	EvaluateState();
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
	if (PlayerPawn)
	{
		FVector TargetLocation = PlayerPawn->GetActorLocation();
		ControlledMonster->FinalGoalLocation = TargetLocation;

		MoveToLocation(TargetLocation);
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

void ANormalMonsterCon::HandleAttack()
{
	if(!ControlledMonster) return;

	ControlledMonster->TryAttack();
}

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

		if(!Actor->ActorHasTag(FName("Structure")) && !Actor->ActorHasTag(FName("Player")))
		continue;

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

		if(MinDistance <= GetAttackRange())
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
		ControlledMonster->SetTargetActor(nullptr);
		ControlledMonster->SetMonsterState(EMonsterState::Patrol);	
	}
}

void ANormalMonsterCon::OnTargetPerceptionUpdated(AActor *Actor, FAIStimulus Stimulus)
{
	if(!Actor || !ControlledMonster) return;

	if(Actor->IsA<AMonsterBase>()) return;

	bool bIsStructure = Actor->ActorHasTag(FName("Structure"));
	bool bIsPlayer = Actor->ActorHasTag(FName("Player"));

	if(Stimulus.WasSuccessfullySensed())
	{
		if(bIsStructure)
		{
			UE_LOG(LogTemp, Log, TEXT("Structure Detected : %s"), *Actor->GetName());
		}
		else if(bIsPlayer)
		{
			UE_LOG(LogTemp, Log, TEXT("Player Detected : %s"), *Actor->GetName());
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Lost sight of : %s"), *Actor->GetName());
	}
}
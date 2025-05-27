// Fill out your copyright notice in the Description page of Project Settings.

#include "StageManagerComponent.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "MonsterSpawner.h"
#include "SaveMyselfGameInstance.h"
#include "Kismet/GameplayStatics.h"

UStageManagerComponent::UStageManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UStageManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundSpawners;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMonsterSpawner::StaticClass(), FoundSpawners);

	TotalSpawnerCount = FoundSpawners.Num();

	for(AActor* Actor : FoundSpawners)
    {
		if(AMonsterSpawner* Spawner = Cast<AMonsterSpawner>(Actor))
        {
			MonsterSpawner.Add(Spawner);
		}
	}
}

void UStageManagerComponent::PreparePhase()
{
	CurrentStageState = EStageState::Prepare;
	OnStageStateChanged.Broadcast(CurrentStageState);

	GetWorld()->GetTimerManager().SetTimer(PrepareTimerHandle, this, &UStageManagerComponent::BattlePhase, PrepareTime, false);
}

void UStageManagerComponent::BattlePhase()
{
	CurrentStageState = EStageState::Battle;
	OnStageStateChanged.Broadcast(CurrentStageState);

	for(AMonsterSpawner* Spawner : MonsterSpawner)
	{
		if(Spawner)
		{
			Spawner->StartSpawning();
		}
	}

	GetWorld()->GetTimerManager().SetTimer(BattleTimerHandle, this, &UStageManagerComponent::EndPhaseVictory, BattleTime, false);
}

void UStageManagerComponent::EndPhaseVictory()
{
	UE_LOG(LogTemp, Warning, TEXT("Set Victory"));

    CurrentStageState = EStageState::Victory;
	bHasEnded = true;
    OnStageStateChanged.Broadcast(CurrentStageState);
}

void UStageManagerComponent::EndPhaseDefeat()
{
	UE_LOG(LogTemp, Warning, TEXT("Set Defeat"));

    CurrentStageState = EStageState::Defeat;
	bHasEnded = true;
    OnStageStateChanged.Broadcast(CurrentStageState);
}

void UStageManagerComponent::StartStage()
{
	PreparePhase();
}

void UStageManagerComponent::CheckEndPhaseConditions()
{
	if(bHasEnded) return;

	DestroyedSpawnerCount++;

	if(DestroyedSpawnerCount >= TotalSpawnerCount)
	{
		EndPhaseVictory();
	}
}

void UStageManagerComponent::CheckEndPhaseConditions(bool bPlayerDead)
{
	if(bHasEnded) return;

	if(bPlayerDead)
	{
		EndPhaseDefeat();
	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "StageManagerComponent.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "MonsterSpawner.h"
#include "SaveMyselfGameInstance.h"
#include "DefenseCharacter.h"
#include "Kismet/GameplayStatics.h"

UStageManagerComponent::UStageManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
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

	auto GInstance = Cast<USaveMyselfGameInstance>(GetWorld()->GetGameInstance());
	if(!GInstance) return;

	GetWorld()->GetTimerManager().SetTimer
	(PrepareTimerHandle, this, &UStageManagerComponent::BattlePhase, GInstance->GetPrepareTime(), false);
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
	auto GInstance = Cast<USaveMyselfGameInstance>(GetWorld()->GetGameInstance());
	if(!GInstance) return;

	GetWorld()->GetTimerManager().SetTimer
	(BattleTimerHandle, this, &UStageManagerComponent::EndPhaseDefeat, GInstance->GetBattleTime(), false);
}

void UStageManagerComponent::EndPhaseVictory()
{
	GetWorld()->GetTimerManager().ClearTimer(BattleTimerHandle);

    CurrentStageState = EStageState::Victory;
	bHasEnded = true;
    OnStageStateChanged.Broadcast(CurrentStageState);

	if(ADefenseCharacter* pPlayer = Cast<ADefenseCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
	{
		pPlayer->bEntranceShowMouseCursor();
		pPlayer->SetVictory(true);
	}
}

void UStageManagerComponent::EndPhaseDefeat()
{
	GetWorld()->GetTimerManager().ClearTimer(BattleTimerHandle);

    CurrentStageState = EStageState::Defeat;
	bHasEnded = true;
    OnStageStateChanged.Broadcast(CurrentStageState);

	if(ADefenseCharacter* pPlayer = Cast<ADefenseCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
	{
		pPlayer->PlayerDead();
		pPlayer->bEntranceShowMouseCursor();
	}
}

int32 UStageManagerComponent::GetPhaseRemaining() const
{
	if(CurrentStageState == EStageState::Prepare)
		return GetWorld()->GetTimerManager().GetTimerRemaining(PrepareTimerHandle);

	else if(CurrentStageState == EStageState::Battle)
		return GetWorld()->GetTimerManager().GetTimerRemaining(BattleTimerHandle);

	return 0;
}

EStageState UStageManagerComponent::GetCurStage() const
{
	return CurrentStageState;
}

void UStageManagerComponent::StartStage()
{
	FTimerHandle PhaseTimer;
	GetWorld()->GetTimerManager().SetTimer(PhaseTimer, [this]{ PreparePhase(); }, 0.2f, false);
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

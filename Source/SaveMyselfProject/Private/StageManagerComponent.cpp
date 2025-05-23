// Fill out your copyright notice in the Description page of Project Settings.

#include "StageManagerComponent.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "MonsterSpawner.h"
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
	if(FoundSpawners.Num() > 0)
    {
        MonsterSpawner = Cast<AMonsterSpawner>(FoundSpawners[0]);
	}
}

void UStageManagerComponent::PreparePhase()
{
	UE_LOG(LogTemp, Warning, TEXT("Set PreparePhase"));

	CurrentStageState = EStageState::Prepare;
	OnStageStateChanged.Broadcast(CurrentStageState);

	GetWorld()->GetTimerManager().SetTimer(PrepareTimerHandle, this, &UStageManagerComponent::BattlePhase, PrepareTime, false);
}

void UStageManagerComponent::BattlePhase()
{
	UE_LOG(LogTemp, Warning, TEXT("Set BattlePhase"));

	CurrentStageState = EStageState::Battle;
	OnStageStateChanged.Broadcast(CurrentStageState);

	if(MonsterSpawner)
	{
		MonsterSpawner->StartSpawning();
	}

	GetWorld()->GetTimerManager().SetTimer(BattleTimerHandle, this, &UStageManagerComponent::EndPhase, BattleTime, false);
}

void UStageManagerComponent::EndPhase()
{
	UE_LOG(LogTemp, Warning, TEXT("Set EndPhase"));

    CurrentStageState = EStageState::End;
    OnStageStateChanged.Broadcast(CurrentStageState);

	//铰菩 贸府 肺流 备泅
}

void UStageManagerComponent::StartStage()
{
	PreparePhase();
}

void UStageManagerComponent::CheckEndPhaseConditions()
{
	if(bHasEnded) return;

	bool bAllMonstersDead = true;
	bool bPlayerDead = false;

	if(bPlayerDead)
	{
		EndPhase();
	}
	else if(bAllMonstersDead)
	{
		EndPhase();
	}
}
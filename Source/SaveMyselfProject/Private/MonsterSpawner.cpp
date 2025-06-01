// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawner.h"
#include "MonsterBase.h"
#include "DefenseGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
AMonsterSpawner::AMonsterSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	SpawnerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpawnerMesh"));
    RootComponent = SpawnerMesh;
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (CubeMesh.Succeeded())
    {
        SpawnerMesh->SetStaticMesh(CubeMesh.Object);
        SpawnerMesh->SetWorldScale3D(FVector(0.5f));
    }
    
    SpawnedEffectComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("SpawnedEffectComp"));
    SpawnedEffectComp->SetupAttachment(RootComponent);
    SpawnedEffectComp->SetRelativeScale3D(FVector(1.3f));
    SpawnedEffectComp->SetAutoActivate(false);
}

void AMonsterSpawner::BeginPlay()
{
    Super::BeginPlay();

    ADefenseGameModeBase* DefenseMode = Cast<ADefenseGameModeBase>(UGameplayStatics::GetGameMode(this));
    if(DefenseMode)
    {
        StageManager = DefenseMode->GetStageManager();
    }
}

void AMonsterSpawner::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(!bIsSpawning) return;

    SpawnTimer += DeltaTime;
    if(SpawnTimer >= SpawnCooldown)
    {
        
        TrySpawn();
        SpawnTimer = 0.0f;
    }
}

void AMonsterSpawner::Destroyed()
{
    Super::Destroyed();

    if(StageManager)
    {
        StageManager->CheckEndPhaseConditions();
    }
}

void AMonsterSpawner::StartSpawning()
{
    bIsSpawning = true;
    SetActorTickEnabled(true);
}

void AMonsterSpawner::StopSpawning()
{
    bIsSpawning = false;
    SetActorTickEnabled(false);
}

void AMonsterSpawner::OnMonsterDied(AMonsterBase *Monster)
{
    SpawnedMonsters.Remove(Monster);

    const bool bAllSpawned = SpawnedMonsterCount == MaxSpawnCount;
    const bool bAllDead = SpawnedMonsters.Num() == 0;

    if(bAllSpawned)
    {
        StopSpawning();
        if(bAllDead && StageManager) 
        {
            Destroy();
        }
    }
}

void AMonsterSpawner::TrySpawn()
{
    if(!MonsterClass) return;

    if(SpawnedMonsterCount >= MaxSpawnCount) return;
    
    if(SpawnedEffectComp) SpawnedEffectComp->SetActive(true);

    bIsSpawn = true;
    SpawnMonster();
}

void AMonsterSpawner::SpawnMonster()
{
	if(!MonsterClass) return;

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AMonsterBase* Spawned = GetWorld()->SpawnActor<AMonsterBase>(MonsterClass, GetActorLocation(), GetActorRotation(), Params);
    if(Spawned)
    {
        Spawned->OwnerSpawner = this;
        SpawnedMonsters.Add(Spawned);
        SpawnedMonsterCount++;
    }
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawner.h"
#include "MonsterBase.h"
#include "Components/StaticMeshComponent.h"

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
}

void AMonsterSpawner::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(!bIsSpawning) return;

    SpawnTimer += DeltaTime;
    if (SpawnTimer >= SpawnCooldown)
    {
        TrySpawn();
        SpawnTimer = 0.0f;
    }

    SpawnedMonsters.RemoveAll(
    [](AMonsterBase* M) 
    {
        return !IsValid(M);
    });
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

void AMonsterSpawner::TrySpawn()
{
    if(SpawnedMonsters.Num() >= MaxSpawnCount || !MonsterClass) return;
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
        SpawnedMonsters.Add(Spawned);
        UE_LOG(LogTemp, Log, TEXT("Spawned %s at %s"), *MonsterClass->GetName(), *GetActorLocation().ToString());
    }
}

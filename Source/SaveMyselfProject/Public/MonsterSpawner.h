// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonsterSpawner.generated.h"

class AMonsterBase;

UCLASS()
class SAVEMYSELFPROJECT_API AMonsterSpawner : public AActor
{
	GENERATED_BODY()
	
public : 
	AMonsterSpawner();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;

	UFUNCTION()
    void StartSpawning();
  
	UFUNCTION()
    void StopSpawning();

	void OnMonsterDied(AMonsterBase* Monster);

private :	
	UPROPERTY(EditAnywhere, Category = "Monster", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AMonsterBase> MonsterClass;

	UPROPERTY(EditAnywhere, Category = "Monster", meta = (AllowPrivateAccess = "true"))
	int32 MaxSpawnCount = 5;

	UPROPERTY(EditAnywhere, Category = "Monster", meta = (AllowPrivateAccess = "true"))
	float SpawnCooldown = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = "Monster", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* SpawnerMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Monster", meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* SpawnedEffectComp;

	class UStageManagerComponent* StageManager;

	float SpawnTimer = 0.f;
	int32 SpawnedMonsterCount = 0;

	UPROPERTY()
	TArray<AMonsterBase*> SpawnedMonsters;

	bool bIsSpawning = false;
	bool bSpawnCompleted = false;
	bool bIsSpawn = false;

	void TrySpawn();
	void SpawnMonster();
};

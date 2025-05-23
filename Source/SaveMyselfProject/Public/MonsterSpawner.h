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

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
    void StartSpawning(); // 스폰 시작 신호
    UFUNCTION()
    void StopSpawning();  // 스폰 중지

private :	
	UPROPERTY(EditDefaultsOnly, Category = "Monster", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AMonsterBase> MonsterClass;

	UPROPERTY(EditDefaultsOnly, Category = "Monster", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* SpawnerMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Monster", meta = (AllowPrivateAccess = "true"))
	int32 MaxSpawnCount = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Monster", meta = (AllowPrivateAccess = "true"))
	float SpawnCooldown = 3.f;

	float SpawnTimer = 0.f;

	UPROPERTY()
	TArray<AMonsterBase*> SpawnedMonsters;

	bool bIsSpawning = false;

	void TrySpawn();
	void SpawnMonster();
};

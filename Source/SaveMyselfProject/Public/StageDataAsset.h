// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "StageDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FMonsterSpawnInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class AMonsterBase> MonsterClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 SpawnCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpawnInterval = 1.5f;
};

UCLASS()
class SAVEMYSELFPROJECT_API UStageDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StageInfo")
	FName StageID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StageInfo")
	float PrepareTime = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StageInfo")
	float BattleTime = 60.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StageInfo")
	TArray<FMonsterSpawnInfo> MonsterList;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StageInfo")
	int32 MaxBagWeight = 20;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StageInfo")
	bool bAllowElite = false;
};

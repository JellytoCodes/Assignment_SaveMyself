﻿
#pragma once

#include "CoreMinimal.h"
#include "MonsterMasterTable.generated.h"

UENUM(BlueprintType)
enum class EMonsterType : uint8
{
	Normal,
	Elite,
};

UENUM(BlueprintType)
enum class EEliteAIType : uint8
{
	None,
	Destroyer,
	Mage,
};

USTRUCT(BlueprintType)
struct FMonsterStatRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MonsterID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMonsterType MonsterType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEliteAIType EliteAIType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinMoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxMoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackRange;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMesh* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AMonsterBase> MonsterClass;
};
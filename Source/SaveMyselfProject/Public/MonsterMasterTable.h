
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
	AoEAttacker,
	TrapDestroyer,
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	None,
	Axe,
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
	EWeaponType MonsterWeaponID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinMoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxMoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AMonsterBase> MonsterClass;
};
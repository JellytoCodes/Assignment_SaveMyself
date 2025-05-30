
#pragma once

#include "CoreMinimal.h"
#include "WeaponItemTable.generated.h"

//피격 시 단일인지, 광역인지 결정하기 위함
UENUM(BlueprintType)
enum class EDamageType : uint8
{
	Single,
	Multiple,
};

USTRUCT(BlueprintType)
struct FWeaponDataRow : public FTableRowBase
{
	GENERATED_BODY()

	//무기 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	FName WeaponName;

	//무기 데미지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	float WeaponDamage;

	//무기 사용 쿨타임
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	float MaxCoolTime;

	//피격 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	EDamageType DamageType;
};

#pragma once

#include "CoreMinimal.h"
#include "TrapItemTable.generated.h"

UENUM(BlueprintType)
enum class ETrapType : uint8
{
	Explosive,
	Binding,
};

USTRUCT(BlueprintType)
struct FTrapDataRow : public FTableRowBase
{
	GENERATED_BODY()

	//트랩 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName TrapName;

	//트랩 효과 
	//ex) Binding = 5.f (5초동안 묶이도록함), Explosive = 30.f (폭발하며 주변에 30의 데미지를 입힘)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TrapEffect;

	//트랩 설치 쿨타임
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxCoolTime;
};
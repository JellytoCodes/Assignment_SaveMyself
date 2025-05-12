
#pragma once

#include "CoreMinimal.h"
#include "StructureItemTable.generated.h"

USTRUCT(BlueprintType)
struct FStructureDataRow : public FTableRowBase
{
	GENERATED_BODY()

	//건축물 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName StructureName;

	//건축물 체력 
	//ex) Binding = 5.f (5초동안 묶이도록함), Explosive = 30.f (폭발하며 주변에 30의 데미지를 입힘)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StructureHP;

	//건축물 방어력 (현 개발에 넣을 요소는 아니나 추후 검토 후 사용하기 위함)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StructureDefense;

	//건설 쿨타임
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxCoolTime;
};
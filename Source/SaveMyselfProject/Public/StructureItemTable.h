
#pragma once

#include "CoreMinimal.h"
#include "StructureItemTable.generated.h"

USTRUCT(BlueprintType)
struct FStructureDataRow : public FTableRowBase
{
	GENERATED_BODY()

	//���๰ �̸�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName StructureName;

	//���๰ ü�� 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StructureHP;

	//���๰ ���� (�� ���߿� ���� ��Ҵ� �ƴϳ� ���� ���� �� ����ϱ� ����)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StructureDefense;

	//�Ǽ� ��Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxCoolTime;
};
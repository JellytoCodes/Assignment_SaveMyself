
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

	//Ʈ�� �̸�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName TrapName;

	//Ʈ�� ȿ�� 
	//ex) Binding = 5.f (5�ʵ��� ���̵�����), Explosive = 30.f (�����ϸ� �ֺ��� 30�� �������� ����)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TrapEffect;

	//Ʈ�� ��ġ ��Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxCoolTime;
};
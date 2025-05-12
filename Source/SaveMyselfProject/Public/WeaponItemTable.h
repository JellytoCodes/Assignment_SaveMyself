
#pragma once

#include "CoreMinimal.h"
#include "WeaponItemTable.generated.h"

//�ǰ� �� ��������, �������� �����ϱ� ����
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

	//���� �̸�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	FName WeaponName;

	//���� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	float WeaponDamage;

	//���� ��� ��Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	float MaxCoolTime;

	//�ǰ� Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	EDamageType DamageType;
};
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PlayerItem.h"
#include "ItemMasterTable.generated.h"

UENUM(BlueprintType)
enum class EItemTypes : uint8
{
	None		UMETA(DisplayName = "None"),
	Weapon		UMETA(DisplayName = "Weapon"),
	Structure	UMETA(DisplayName = "Structure"),
	Trap		UMETA(DisplayName = "Trap"),
};

USTRUCT(BlueprintType)
struct FItemDataRow : public FTableRowBase
{
	GENERATED_BODY()
	
	//ITEM ID ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemID;

	//ID Name ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DisplayName;

	//Item ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Discription;

	//ItemType ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemTypes ItemType;

	//ItemIcon ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* ItemIcon;

	//PlayerItem�� ���� �Ұ��ϵ��� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APlayerItem> ItemClass;

	//������ ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ItemWeight = 0.f;
};
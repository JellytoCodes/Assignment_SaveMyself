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
	
	//ITEM ID 지정
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemID;

	//ID Name 지정
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DisplayName;

	//Item 설명
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Discription;

	//ItemType 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemTypes ItemType;

	//ItemIcon 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* ItemIcon;

	//PlayerItem외 참조 불가하도록 제한
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APlayerItem> ItemClass;

	//아이템 무게 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ItemWeight = 0.f;
};
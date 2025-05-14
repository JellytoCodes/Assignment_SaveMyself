// Fill out your copyright notice in the Description page of Project Settings.

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
struct FItemMasterDataRow : public FTableRowBase
{
	GENERATED_BODY()
	
	//ITEM Index 지정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MasterData")
	int32 ItemID;

	//ID Name 지정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MasterData")
	FText DisplayName;

	//Item 설명
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MasterData")
	FText Description;

	//ItemType 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MasterData")
	EItemTypes ItemType;

	//ItemIcon 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MasterData")
	UTexture2D* ItemIcon;

	//PlayerItem외 참조 불가하도록 제한
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MasterData")
	TSubclassOf<APlayerItem> ItemClass;

	//아이템 무게 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MasterData")
	float ItemWeight = 0.f;

	//플레이어 기준으로 아이템을 스폰하기 위한 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MasterData")
	FVector LocalOffSet = FVector(0.f, 0.f, 0.f);
};
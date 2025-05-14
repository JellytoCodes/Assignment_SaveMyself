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
	
	//ITEM Index ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MasterData")
	int32 ItemID;

	//ID Name ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MasterData")
	FText DisplayName;

	//Item ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MasterData")
	FText Description;

	//ItemType ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MasterData")
	EItemTypes ItemType;

	//ItemIcon ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MasterData")
	UTexture2D* ItemIcon;

	//PlayerItem�� ���� �Ұ��ϵ��� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MasterData")
	TSubclassOf<APlayerItem> ItemClass;

	//������ ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MasterData")
	float ItemWeight = 0.f;

	//�÷��̾� �������� �������� �����ϱ� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MasterData")
	FVector LocalOffSet = FVector(0.f, 0.f, 0.f);
};
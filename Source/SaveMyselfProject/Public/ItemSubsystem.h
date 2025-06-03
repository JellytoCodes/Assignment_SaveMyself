// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemMasterTable.h"
#include "StorageArrayTable.h"
#include "TrapItemTable.h"
#include "StructureItemTable.h"
#include "WeaponItemTable.h"
#include "Engine/DataTable.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ItemSubsystem.generated.h"

class UDataTable;

UCLASS()
class SAVEMYSELFPROJECT_API UItemSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public :
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	const FItemMasterDataRow* GetItemMasterData(FName itemID) const;
	const FWeaponDataRow* GetItemWeaponData(FName itemID) const;
	const FStructureDataRow* GetItemStructureData(FName itemID) const;
	const FTrapDataRow* GetItemTrapData(FName itemID) const;

private :
	UPROPERTY(EditDefaultsOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	UDataTable* itemMasterTable;

	UPROPERTY(EditDefaultsOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	UDataTable* itemWeaponTable;

	UPROPERTY(EditDefaultsOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	UDataTable* itemStructureTable;

	UPROPERTY(EditDefaultsOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	UDataTable* itemTrapTable;
};

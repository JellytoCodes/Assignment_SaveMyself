// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemMasterTable.h"
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
	const FItemMasterDataRow* GetItemMasterData(FName ItemID) const;
	const FWeaponDataRow* GetItemWeaponData(FName ItemID) const;
	const FStructureDataRow* GetItemStructureData(FName ItemID) const;
	const FTrapDataRow* GetItemTrapData(FName ItemID) const;

protected :
	UPROPERTY(EditDefaultsOnly, Category = "Data")
	UDataTable* ItemMasterTable;

	UPROPERTY(EditDefaultsOnly, Category = "Data")
	UDataTable* ItemWeaponTable;

	UPROPERTY(EditDefaultsOnly, Category = "Data")
	UDataTable* ItemStructureTable;

	UPROPERTY(EditDefaultsOnly, Category = "Data")
	UDataTable* ItemTrapTable;


};

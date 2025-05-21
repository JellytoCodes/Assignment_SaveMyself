// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSubsystem.h"
#include "Engine/DataTable.h"
#include "UObject/ConstructorHelpers.h"

void UItemSubsystem::Initialize(FSubsystemCollectionBase &Collection)
{
	Super::Initialize(Collection);

	//Item Master Table Cast
	UDataTable* itemMasterTableFinder 
	= Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Game/DataTable/DT_ItemMasterDataRow.DT_ItemMasterDataRow")));
	if(itemMasterTableFinder) ItemMasterTable = itemMasterTableFinder;

	//Item Weapon Table Cast
	UDataTable* itemWeaponTableFinder
	= Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Game/DataTable/DT_WeaponDataRow.DT_WeaponDataRow")));
	if(itemWeaponTableFinder) ItemWeaponTable = itemWeaponTableFinder;

	//Item Structure Table Cast
	UDataTable* itemStructureTableFinder
	= Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Game/DataTable/DT_StructureDataRow.DT_StructureDataRow")));
	if(itemStructureTableFinder) ItemStructureTable = itemStructureTableFinder;

	//Item Trap Table Cast
	UDataTable* itemTrapTableFinder	
	= Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Game/DataTable/DT_TrapDataRow.DT_TrapDataRow")));
	if(itemTrapTableFinder)	ItemTrapTable = itemTrapTableFinder;
}

const FItemMasterDataRow *UItemSubsystem::GetItemMasterData(FName ItemID) const
{
	if(!ItemMasterTable) return nullptr;

	const FItemMasterDataRow* RowData = ItemMasterTable->FindRow<FItemMasterDataRow>(ItemID, TEXT("LookupMasterData"));
	return RowData;
}

const FWeaponDataRow *UItemSubsystem::GetItemWeaponData(FName ItemID) const
{
	if(!ItemWeaponTable) return nullptr;
	const FWeaponDataRow* RowData = ItemWeaponTable->FindRow<FWeaponDataRow>(ItemID, TEXT("LookupWeaponData"));
	
	return RowData;
}

const FStructureDataRow *UItemSubsystem::GetItemStructureData(FName ItemID) const
{	
	if(!ItemStructureTable) return nullptr;
	const FStructureDataRow* RowData = ItemStructureTable->FindRow<FStructureDataRow>(ItemID, TEXT("LookupStructureData"));
	
	return RowData;
}

const FTrapDataRow *UItemSubsystem::GetItemTrapData(FName ItemID) const
{	
	if(!ItemTrapTable) return nullptr;
	const FTrapDataRow* RowData = ItemTrapTable->FindRow<FTrapDataRow>(ItemID, TEXT("LookupTrapData"));
	
	return RowData;
}

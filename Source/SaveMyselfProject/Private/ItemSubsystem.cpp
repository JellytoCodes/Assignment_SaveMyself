// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSubsystem.h"
#include "Engine/DataTable.h"
#include "UObject/ConstructorHelpers.h"

void UItemSubsystem::Initialize(FSubsystemCollectionBase &Collection)
{
	Super::Initialize(Collection);

	//Item Master Table Cast
	UDataTable* itemMasterTableFinder = Cast<UDataTable>(
	StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Game/DataTable/DT_ItemMasterDataRow.DT_ItemMasterDataRow")));
	if(itemMasterTableFinder) itemMasterTable = itemMasterTableFinder;

	//Item Weapon Table Cast
	UDataTable* itemWeaponTableFinder= Cast<UDataTable>(
	StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Game/DataTable/DT_WeaponDataRow.DT_WeaponDataRow")));
	if(itemWeaponTableFinder) itemWeaponTable = itemWeaponTableFinder;

	//Item Structure Table Cast
	UDataTable* itemStructureTableFinder= Cast<UDataTable>(StaticLoadObject(
	UDataTable::StaticClass(), nullptr, TEXT("/Game/DataTable/DT_StructureDataRow.DT_StructureDataRow")));
	if(itemStructureTableFinder) itemStructureTable = itemStructureTableFinder;

	//Item Trap Table Cast
	UDataTable* itemTrapTableFinder	= Cast<UDataTable>(
	StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Game/DataTable/DT_TrapDataRow.DT_TrapDataRow")));
	if(itemTrapTableFinder)	itemTrapTable = itemTrapTableFinder;
}

const FItemMasterDataRow *UItemSubsystem::GetItemMasterData(FName itemID) const
{
	if(!itemMasterTable) return nullptr;

	const FItemMasterDataRow* RowData = itemMasterTable->FindRow<FItemMasterDataRow>(itemID, TEXT("LookupMasterData"));
	return RowData;
}

const FWeaponDataRow *UItemSubsystem::GetItemWeaponData(FName itemID) const
{
	if(!itemWeaponTable) return nullptr;
	const FWeaponDataRow* RowData = itemWeaponTable->FindRow<FWeaponDataRow>(itemID, TEXT("LookupWeaponData"));
	
	return RowData;
}

const FStructureDataRow *UItemSubsystem::GetItemStructureData(FName itemID) const
{	
	if(!itemStructureTable) return nullptr;
	const FStructureDataRow* RowData = itemStructureTable->FindRow<FStructureDataRow>(itemID, TEXT("LookupStructureData"));
	
	return RowData;
}

const FTrapDataRow *UItemSubsystem::GetItemTrapData(FName itemID) const
{	
	if(!itemTrapTable) return nullptr;
	const FTrapDataRow* RowData = itemTrapTable->FindRow<FTrapDataRow>(itemID, TEXT("LookupTrapData"));
	
	return RowData;
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "StructureItem.h"
#include "ItemMasterTable.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

AStructureItem::AStructureItem()
{
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	ItemMesh->SetupAttachment(RootComponent);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ItemMesh->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));
	RootComponent = ItemMesh;
}

void AStructureItem::BeginPlay()
{
	Super::BeginPlay();

	FItemMasterDataRow* MasterDataRow = ItemMasterData->FindRow<FItemMasterDataRow>(ItemMasterID, TEXT("LookUpItemMasterData"));
	if(MasterDataRow)
	{
		UE_LOG(LogTemp, Log, TEXT("ItemID : %s"), *MasterDataRow->ItemID.ToString());
		UE_LOG(LogTemp, Log, TEXT("DisplayName : %s"), *MasterDataRow->DisplayName.ToString());
		UE_LOG(LogTemp, Log, TEXT("Description : %s"), *MasterDataRow->Description.ToString());
		UE_LOG(LogTemp, Log, TEXT("ItemType(intiger) : %d"), MasterDataRow->ItemType);
		UE_LOG(LogTemp, Log, TEXT("ItemWeight : %2lf"), MasterDataRow->ItemWeight);
	}

	FStructureDataRow* StructureDataRow = StructureData->FindRow<FStructureDataRow>(ItemStructureID, TEXT("LookUpItemTrapData"));
	if(StructureDataRow)
	{
		UE_LOG(LogTemp, Log, TEXT("StructureName : %s"), *StructureDataRow->StructureName.ToString());
		UE_LOG(LogTemp, Log, TEXT("StructureHP : %2lf"), StructureDataRow->StructureHP);
		UE_LOG(LogTemp, Log, TEXT("StructureDefense : %2lf"), StructureDataRow->StructureDefense);
		UE_LOG(LogTemp, Log, TEXT("MaxCoolTime : %2lf"), StructureDataRow->MaxCoolTime);		
	}
}

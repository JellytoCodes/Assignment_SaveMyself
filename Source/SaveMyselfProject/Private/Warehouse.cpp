// Fill out your copyright notice in the Description page of Project Settings.

#include "Warehouse.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Engine/DataTable.h"
#include "DefenseHUD.h"
#include "DefenseCharacter.h"
#include "SaveMyselfGameInstance.h"
#include "ItemSubsystem.h"

AWarehouse::AWarehouse()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	BoxCollision->SetGenerateOverlapEvents(true);
	BoxCollision->SetRelativeScale3D(FVector(9.f, 15.f, 1.f));
	BoxCollision->BodyInstance.SetCollisionProfileName("Trigger");
	RootComponent = BoxCollision;

	UDataTable* WarehouseTableFinder
	= Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Game/DataTable/DT_ItemMasterDataRow.DT_ItemMasterDataRow")));
	if(WarehouseTableFinder) WarehouseItemTable	= WarehouseTableFinder;
}

void AWarehouse::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle InitTimer;
	GetWorld()->GetTimerManager().SetTimer(InitTimer,[this]{
		if(WarehouseItemTable)
		{	
			auto GInstance = Cast<USaveMyselfGameInstance>(GetGameInstance());
			if(GInstance)
			{
				TArray<FStorageArrRow*> AllRows;
				WarehouseItemTable->GetAllRows(TEXT("Init"), AllRows);

				for(auto Row : AllRows)
				{	
					if(Row->StageID == GInstance->GetStageID())
					{
						fInData.Add(Row);
					}
				}
			}
		}
	}, .2f, false);

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AWarehouse::OnWarehouseEntranceOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AWarehouse::OnWarehouseExitOverlap);
}

void AWarehouse::OnWarehouseEntranceOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	ADefenseCharacter* pPlayer = Cast<ADefenseCharacter>(OtherActor);
	if(pPlayer)
	{		
		pPlayer->bEntranceShowMouseCursor();

		APlayerController* PC = Cast<APlayerController>(pPlayer->GetController());
		if(!PC) return;

		ADefenseHUD* HUD = Cast<ADefenseHUD>(PC->GetHUD());
		if(!HUD) return;

		HUD->ShowStorageWidget(fInData);
	}
}

void AWarehouse::OnWarehouseExitOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
	ADefenseCharacter* pPlayer = Cast<ADefenseCharacter>(OtherActor);
	if(pPlayer)
	{
		APlayerController* PC = Cast<APlayerController>(pPlayer->GetController());
		if(!PC) return;

		ADefenseHUD* HUD = Cast<ADefenseHUD>(PC->GetHUD());
		if(!HUD) return;

		HUD->HideStorageWidget();

		pPlayer->bExitHideMouseCursor();
	}
}

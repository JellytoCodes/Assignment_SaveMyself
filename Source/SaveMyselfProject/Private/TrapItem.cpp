// Fill out your copyright notice in the Description page of Project Settings.

#include "TrapItem.h"
#include "PlayerItem.h"
#include "ItemMasterTable.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

ATrapItem::ATrapItem()
{
	SphereCollision = CreateDefaultSubobject<USphereComponent>("Collision");
	SphereCollision->SetGenerateOverlapEvents(true);
	SphereCollision->SetSphereRadius(10.f);
	SphereCollision->BodyInstance.SetCollisionProfileName("Projectile");
	SphereCollision->SetCollisionResponseToAllChannels(ECR_Block);
	SphereCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	RootComponent = SphereCollision;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	ItemMesh->SetupAttachment(RootComponent);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	ItemMesh->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TrapMash(TEXT(""));
	
	if(TrapMash.Succeeded())
	{
		ItemMesh->SetStaticMesh(TrapMash.Object);
	}
}

void ATrapItem::BeginPlay()
{
	Super::BeginPlay();

	FItemMasterDataRow* MasterDataRow = ItemMasterData->FindRow<FItemMasterDataRow>(ItemMasterID, TEXT("LookUpItemMasterData"));
	if(MasterDataRow)
	{
		UE_LOG(LogTemp, Log, TEXT("ItemID : %d"), MasterDataRow->ItemID);
		UE_LOG(LogTemp, Log, TEXT("DisplayName : %s"), *MasterDataRow->DisplayName.ToString());
		UE_LOG(LogTemp, Log, TEXT("Description : %s"), *MasterDataRow->Description.ToString());
		UE_LOG(LogTemp, Log, TEXT("ItemType(intiger) : %d"), MasterDataRow->ItemType);
		UE_LOG(LogTemp, Log, TEXT("ItemWeight : %2lf"), MasterDataRow->ItemWeight);
	}

	FTrapDataRow* TrapDataRow = TrapData->FindRow<FTrapDataRow>(ItemTrapID, TEXT("LookUpItemTrapData"));
	if(TrapData)
	{
		UE_LOG(LogTemp, Log, TEXT("TrapName : %s"), *TrapDataRow->TrapName.ToString());
		UE_LOG(LogTemp, Log, TEXT("TrapDamage : %2lf"), TrapDataRow->TrapEffect);
		UE_LOG(LogTemp, Log, TEXT("MaxCoolTime : %2lf"), TrapDataRow->MaxCoolTime);
		UE_LOG(LogTemp, Log, TEXT("DamageType(intiger) : %d"), TrapDataRow->TrapType);		
	}

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ATrapItem::OnTrapOverlap);
}

void ATrapItem::OnTrapOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if(OtherActor)
	{
		FTransform WeaponTrans;
		WeaponTrans.SetLocation(SweepResult.ImpactPoint);
		Destroy();
	}
}

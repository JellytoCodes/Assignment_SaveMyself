// Fill out your copyright notice in the Description page of Project Settings.

#include "TrapItem.h"
#include "PlayerItem.h"
#include "ItemMasterTable.h"
#include "ItemSubsystem.h"
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

	Tags.Add(FName("Trap"));
}

void ATrapItem::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("Spawned TrapItem"));
	
	if (getItemName != NAME_None)
	{
		EnableItemData(getItemName);
	}

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ATrapItem::OnTrapOverlap);
}

void ATrapItem::EnableItemData(FName ItemID)
{
	if(const UItemSubsystem* ItemDB = GetGameInstance()->GetSubsystem<UItemSubsystem>())
	{
		const FTrapDataRow* Data = ItemDB->GetItemTrapData(ItemID);
		if(Data)
		{
			trapName = Data->TrapName;
			trapEffect = Data->TrapEffect;
			maxCoolTime = Data->MaxCoolTime;
			trapType = Data->TrapType;
		}
	}
}

void ATrapItem::OnTrapOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if(OtherActor)
	{
		FTransform WeaponTrans;
		WeaponTrans.SetLocation(SweepResult.ImpactPoint);
	}
}
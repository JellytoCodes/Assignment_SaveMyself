// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponItem.h"
#include "PlayerItem.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AWeaponItem::AWeaponItem()
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
	ItemMesh->SetRelativeLocationAndRotation(FVector(-40.f, 0.f, 0.f), FRotator(-90.f, 0.f, 0.f));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> WeaponMesh(TEXT(""));
	
	if(WeaponMesh.Succeeded())
	{
		ItemMesh->SetStaticMesh(WeaponMesh.Object);
	}

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->UpdatedComponent = SphereCollision;
	ProjectileMovement->ProjectileGravityScale = 0;
	ProjectileMovement->InitialSpeed = 3000;
	ProjectileMovement->MaxSpeed = 3000;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
}

void AWeaponItem::BeginPlay()
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

	FWeaponDataRow* WeaponDataRow = WeaponData->FindRow<FWeaponDataRow>(ItemWeaponID, TEXT("LookUpItemWeaponData"));
	if(WeaponDataRow)
	{
		UE_LOG(LogTemp, Log, TEXT("WeaponName : %s"), *WeaponDataRow->WeaponName.ToString());
		UE_LOG(LogTemp, Log, TEXT("WeaponDamage : %2lf"), WeaponDataRow->WeaponDamage);
		UE_LOG(LogTemp, Log, TEXT("MaxCoolTime : %2lf"), WeaponDataRow->MaxCoolTime);
		UE_LOG(LogTemp, Log, TEXT("DamageType(intiger) : %d"), WeaponDataRow->DamageType);		
	}

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AWeaponItem::OnWeaponOverlap);
	ProjectileMovement->Velocity = GetActorForwardVector() * ProjectileMovement->InitialSpeed;

	FTimerHandle deathTimer;
	GetWorld()->GetTimerManager().SetTimer(deathTimer, FTimerDelegate::CreateLambda([this]()->void
	{
		Destroy();
	}), 2.f, false);
}

void AWeaponItem::OnWeaponOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if(OtherActor)
	{
		FTransform WeaponTrans;
		WeaponTrans.SetLocation(SweepResult.ImpactPoint);
		Destroy();
	}
}

FVector AWeaponItem::GetLocalOffSet()
{
	return APlayerItem::LocalOffset;
}


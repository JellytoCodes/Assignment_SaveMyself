// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponItem.h"
#include "PlayerItem.h"
#include "ItemMasterTable.h"
#include "ItemSubsystem.h"
#include "Engine/DamageEvents.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AWeaponItem::AWeaponItem()
{
	SphereCollision = CreateDefaultSubobject<USphereComponent>("Collision");
	SphereCollision->SetGenerateOverlapEvents(true);
	SphereCollision->SetSphereRadius(10.f);
	SphereCollision->BodyInstance.SetCollisionProfileName("Projectile");
	RootComponent = SphereCollision;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	ItemMesh->SetupAttachment(RootComponent);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	ItemMesh->SetRelativeLocationAndRotation(FVector(-40.f, 0.f, 0.f), FRotator(-90.f, 0.f, 0.f));

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->UpdatedComponent = SphereCollision;
	ProjectileMovement->ProjectileGravityScale = 0;
	ProjectileMovement->InitialSpeed = 3000;
	ProjectileMovement->MaxSpeed = 3000;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	Tags.Add(FName("Weapon"));
}

void AWeaponItem::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("Spawned WeaponItem"));
	
	if (getItemName != NAME_None)
	{
		EnableItemData(getItemName);
	}

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AWeaponItem::OnWeaponOverlap);
	ProjectileMovement->Velocity = GetActorForwardVector() * ProjectileMovement->InitialSpeed;

	FTimerHandle deathTimer;
	GetWorld()->GetTimerManager().SetTimer(deathTimer, FTimerDelegate::CreateLambda([this]()->void
	{
		Destroy();
	}), 2.f, false);
}

void AWeaponItem::EnableItemData(FName ItemID)
{
	if(const UItemSubsystem* ItemDB = GetGameInstance()->GetSubsystem<UItemSubsystem>())
	{
		const FWeaponDataRow* Data = ItemDB->GetItemWeaponData(ItemID);
		if(Data)
		{
			weaponName = Data->WeaponName;
			weaponDamage = Data->WeaponDamage;
			maxCoolTime = Data->MaxCoolTime;
			damageType = Data->DamageType;

			UE_LOG(LogTemp, Log, TEXT("weaponName	: %s"), *weaponName.ToString());
			UE_LOG(LogTemp, Log, TEXT("weaponDamage	: %.2f"), weaponDamage);
			UE_LOG(LogTemp, Log, TEXT("maxCoolTime	: %.2f"), maxCoolTime);
			UE_LOG(LogTemp, Log, TEXT("DamageType	: %d"), damageType);
		}
	}
}

void AWeaponItem::OnWeaponOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		const FDamageEvent Event(UDamageType::StaticClass());
		OtherActor->TakeDamage(10, Event, GetInstigatorController(), this);
		UE_LOG(LogTemp, Log, TEXT("%s Take Damaged"), *OtherActor->GetName());
	}
}

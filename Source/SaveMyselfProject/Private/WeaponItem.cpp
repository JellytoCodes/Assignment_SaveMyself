// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponItem.h"
#include "PlayerItem.h"
#include "MonsterBase.h"
#include "Engine/OverlapResult.h"
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
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollision->SetCollisionObjectType(ECC_WorldDynamic);
	SphereCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
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

void AWeaponItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
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
		}
	}
}

TArray<AMonsterBase*> AWeaponItem::GetMonstersRadius(float Radius)
{
	TArray<AMonsterBase*> HitMonsters;
	TArray<FOverlapResult> Overlaps;

	FCollisionShape Sphere = FCollisionShape::MakeSphere(Radius);
	bool bHit = GetWorld()->OverlapMultiByChannel(Overlaps, GetActorLocation(), FQuat::Identity, ECC_Pawn, Sphere);

	if(bHit)
	{
		for(const FOverlapResult& MonsterResult : Overlaps)
		{
			AMonsterBase* Monster = Cast<AMonsterBase>(MonsterResult.GetActor());
			if(Monster)
			{
				HitMonsters.Add(Monster);
			}
		}
	}
	return HitMonsters;
}

void AWeaponItem::OnWeaponOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if(OtherActor)
	{
		if(auto TargetActor = Cast<AMonsterBase>(OtherActor))
		{	
			switch(damageType)
			{
				case EDamageType::Single :
					IDamagebleInterface::Execute_ReceiveDamage(TargetActor, weaponDamage);
				break;
				
				case EDamageType::Multiple :
					TArray<AMonsterBase*> Monsters = GetMonstersRadius(300.f);
					for(AMonsterBase* Monster : Monsters)
					{
						if(Monster->Implements<UDamagebleInterface>())
						{
							IDamagebleInterface::Execute_ReceiveDamage(Monster, weaponDamage);
						}
					}
				break;
			}
			Destroy();
		}
	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "TrapItem.h"
#include "PlayerItem.h"
#include "ItemMasterTable.h"
#include "Engine/OverlapResult.h"
#include "ItemSubsystem.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MonsterBase.h"
#include "Kismet/GameplayStatics.h"

ATrapItem::ATrapItem()
{
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	BoxCollision->SetGenerateOverlapEvents(true);
	BoxCollision->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	BoxCollision->BodyInstance.SetCollisionProfileName("OverlapAllDynamic");
	BoxCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = BoxCollision;

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

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ATrapItem::OnTrapOverlap);
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

TArray<AMonsterBase*> ATrapItem::GetMonstersRadius(float Radius)
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

void ATrapItem::HandleTrapTriggered()
{
	switch(trapType)
	{
		case ETrapType::Explosive :
			HandleExplosiveTrap();
		break;
				
		case ETrapType::Binding :
			HandleBindingTrap();
		break;

		default :
			DestroyTrap();
		break;
	}
}

void ATrapItem::HandleExplosiveTrap()
{
	EffectExplosiveTrap();

	FTimerHandle DestroyTimer;
	GetWorldTimerManager().SetTimer(DestroyTimer, this, &ATrapItem::DestroyTrap, .1f, false);
}

void ATrapItem::HandleBindingTrap()
{
	EffectBindingTrap();

	FTimerHandle DestroyTimer;
	GetWorldTimerManager().SetTimer(DestroyTimer, this, &ATrapItem::DestroyTrap, .1f, false);
}

void ATrapItem::EffectExplosiveTrap()
{
	TArray<AMonsterBase*> Monsters = GetMonstersRadius(300.f);
	for(AMonsterBase* Monster : Monsters)
	{
		if(Monster->Implements<UDamagebleInterface>())
		{
			IDamagebleInterface::Execute_ReceiveDamage(Monster, trapEffect);
		}
	}
}

void ATrapItem::EffectBindingTrap()
{
	TArray<AMonsterBase*> Monsters = GetMonstersRadius(300.f);
	for (AMonsterBase* Monster : Monsters)
	{
		if(!Monster) continue;

		Monster->GetCharacterMovement()->DisableMovement();
			
		FTimerHandle UnbindTimer;
		TWeakObjectPtr<AMonsterBase> WeakMonster(Monster);

		GetWorld()->GetTimerManager().SetTimer(UnbindTimer, FTimerDelegate::CreateLambda([WeakMonster]()
		{
			if (WeakMonster.IsValid())
			{
				if(auto MoveComp = WeakMonster->GetCharacterMovement()) MoveComp->SetMovementMode(MOVE_Walking);
			}
		}), trapEffect, false);
	}
}

void ATrapItem::DestroyTrap()
{
	Destroy();
}

void ATrapItem::OnTrapOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if(OtherActor && OtherActor->ActorHasTag("Monster"))
	{
		bIsTriggered = true;
		HandleTrapTriggered();
	}
}
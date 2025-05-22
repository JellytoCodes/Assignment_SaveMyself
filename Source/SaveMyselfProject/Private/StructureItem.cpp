// Fill out your copyright notice in the Description page of Project Settings.

#include "StructureItem.h"
#include "ItemMasterTable.h"
#include "ItemSubsystem.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionSystem.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

AStructureItem::AStructureItem()
{
	SetCanBeDamaged(true);
	SetActorEnableCollision(true);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	BoxCollision->SetGenerateOverlapEvents(true);
	BoxCollision->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	BoxCollision->SetRelativeLocation(FVector(0.f, 0.f, 40.f));
	BoxCollision->BodyInstance.SetCollisionProfileName("OverlapAllDynamic");
	BoxCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	RootComponent = BoxCollision;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	ItemMesh->SetupAttachment(RootComponent);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	ItemMesh->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));

	StimuliSourceComp = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("StimuliSourceComp"));
	StimuliSourceComp->RegisterForSense(UAISense_Sight::StaticClass());
	StimuliSourceComp->bAutoRegister = true;

	Tags.Add(FName("Structure"));
}

void AStructureItem::BeginPlay()
{
	Super::BeginPlay();

	

	UE_LOG(LogTemp, Log, TEXT("Spawned StructureItem"));
	
	if (StimuliSourceComp)
	{
		UAIPerceptionSystem::RegisterPerceptionStimuliSource(GetWorld(), UAISense_Sight::StaticClass(), this);
	}

	if (getItemName != NAME_None)
	{
		EnableItemData(getItemName);
	}

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AStructureItem::OnStructureOverlap);
}

void AStructureItem::ReceiveDamage_Implementation(float Damage)
{
	UE_LOG(LogTemp, Warning, TEXT("StructureDamaged!"))
	if(curHP > 0)
	{
		curHP -= Damage;
	}
	else
	{
		curHP = 0;
		Destroy();
	}
}

void AStructureItem::EnableItemData(FName ItemID)
{
	if(const UItemSubsystem* ItemDB = GetGameInstance()->GetSubsystem<UItemSubsystem>())
	{
		const FStructureDataRow* Data = ItemDB->GetItemStructureData(ItemID);
		if(Data)
		{
			structureName = Data->StructureName;
			structureHP = Data->StructureHP;
			structureDefense = Data->StructureDefense;
			maxCoolTime = Data->MaxCoolTime;
			curHP = structureHP;
		}
	}
}

void AStructureItem::OnStructureOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if(OtherActor && OtherActor != this && OtherActor->IsA<AStructureItem>())
	{
		UE_LOG(LogTemp, Log, TEXT("Do Not There Building"));
	}
}

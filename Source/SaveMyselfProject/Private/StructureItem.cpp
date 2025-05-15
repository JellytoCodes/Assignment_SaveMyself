// Fill out your copyright notice in the Description page of Project Settings.

#include "StructureItem.h"
#include "ItemMasterTable.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

AStructureItem::AStructureItem()
{
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	BoxCollision->SetGenerateOverlapEvents(true);
	BoxCollision->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	BoxCollision->BodyInstance.SetCollisionProfileName("BlockAll");
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Block);
	BoxCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	RootComponent = BoxCollision;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	ItemMesh->SetupAttachment(RootComponent);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	ItemMesh->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));
}

void AStructureItem::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("Spawned StructureItem"));
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "PlacementBlocker.h"
#include "Components/BoxComponent.h"

// Sets default values
APlacementBlocker::APlacementBlocker()
{
	PrimaryActorTick.bCanEverTick = false;

	BlockCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BlockCollision"));
	BlockCollision->SetGenerateOverlapEvents(true);
	BlockCollision->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	BlockCollision->BodyInstance.SetCollisionProfileName("OverlapAllDynamic");
	BlockCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	RootComponent = BlockCollision;

	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh"));
	BlockMesh->SetupAttachment(RootComponent);
	BlockMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	BlockMesh->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));
}


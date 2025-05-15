// Fill out your copyright notice in the Description page of Project Settings.

#include "Warehouse.h"
#include "Components/BoxComponent.h"
#include "StorageWidget.h"
#include "DefenseCharacter.h"

AWarehouse::AWarehouse()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	BoxCollision->SetGenerateOverlapEvents(true);
	BoxCollision->SetRelativeScale3D(FVector(9.f, 15.f, 1.f));
	BoxCollision->BodyInstance.SetCollisionProfileName("Trigger");
	RootComponent = BoxCollision;

	static ConstructorHelpers::FClassFinder<UUserWidget> storageWidgetBP(TEXT("/Game/WidgetBP/WBP_StorageWidget.WBP_StorageWidget_C"));
	if(storageWidgetBP.Succeeded())
	{
		StorageWidgetClass = storageWidgetBP.Class;
	}
}

// Called when the game starts or when spawned
void AWarehouse::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AWarehouse::OnWarehouseOverlap);

	StorageWidgetInstance = CreateWidget<UStorageWidget>(GetWorld(), StorageWidgetClass);

}

void AWarehouse::OnWarehouseOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	ADefenseCharacter* pPlayer = Cast<ADefenseCharacter>(OtherActor);
	if(pPlayer)
	{
		UE_LOG(LogTemp, Log, TEXT("Warehouse Open"));
		StorageWidgetInstance->AddToViewport();
		bIsStorageEntrance = true;
	}
}

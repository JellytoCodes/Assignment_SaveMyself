// Fill out your copyright notice in the Description page of Project Settings.

#include "Warehouse.h"
#include "Components/BoxComponent.h"
#include "StorageWidget.h"
#include "DefenseCharacter.h"
#include "ItemSubsystem.h"

AWarehouse::AWarehouse()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	BoxCollision->SetGenerateOverlapEvents(true);
	BoxCollision->SetRelativeScale3D(FVector(9.f, 15.f, 1.f));
	BoxCollision->BodyInstance.SetCollisionProfileName("Trigger");
	RootComponent = BoxCollision;

	static ConstructorHelpers::FClassFinder<UStorageWidget> storageWidgetBP(TEXT("/Game/WidgetBP/WBP_StorageWidget.WBP_StorageWidget_C"));
	if(storageWidgetBP.Succeeded())
	{
		StorageWidgetClass = storageWidgetBP.Class;
	}
}

// Called when the game starts or when spawned
void AWarehouse::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AWarehouse::OnWarehouseEntranceOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AWarehouse::OnWarehouseExitOverlap);

	StorageWidgetInstance = CreateWidget<UStorageWidget>(GetWorld(), StorageWidgetClass);
	if(StorageWidgetInstance)
	{
		StorageWidgetInstance->AddItemStorage(fInData);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("StorageWidgetInstance Nullptr!"));
	}
	StorageWidgetInstance->AddToViewport();
	StorageWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
}

void AWarehouse::OnWarehouseEntranceOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	ADefenseCharacter* pPlayer = Cast<ADefenseCharacter>(OtherActor);
	if(pPlayer)
	{		
		//Cast 체크용 Log
		UE_LOG(LogTemp, Log, TEXT("Warehouse Entrance"));

		//버튼 클릭을 위한 마우스 활성화
		pPlayer->bEntranceShowMouseCursor();

		FTimerHandle OpenTimer;
		//생성 오류 방지
		GetWorld()->GetTimerManager().SetTimer(OpenTimer, [&]
		{
			StorageWidgetInstance->SetVisibility(ESlateVisibility::Visible);
		}, 0.2f, false);		
	}
}

void AWarehouse::OnWarehouseExitOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
	ADefenseCharacter* pPlayer = Cast<ADefenseCharacter>(OtherActor);
	if(pPlayer)
	{
		//Cast 체크용 Log
		UE_LOG(LogTemp, Log, TEXT("Warehouse Exit"));

		FTimerHandle CloseTimer;
		//삭제 오류 방지
		GetWorld()->GetTimerManager().SetTimer(CloseTimer, [&]
		{
			StorageWidgetInstance->SetVisibility(ESlateVisibility::Collapsed);	
		}, 0.2f, false);

		//창고 나간 후 마우스 비활성화
		pPlayer->bExitHideMouseCursor();
	}
}

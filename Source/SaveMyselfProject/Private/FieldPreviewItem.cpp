
#include "FieldPreviewItem.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "ItemSubsystem.h"
#include "StructureItem.h"
#include "TrapItem.h"
#include "PlacementBlocker.h"

AFieldPreviewItem::AFieldPreviewItem()
{
	PrimaryActorTick.bCanEverTick = true;

	PlacementCheckBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PlacementCheckBox"));
	SetRootComponent(PlacementCheckBox);
	PlacementCheckBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PlacementCheckBox->SetCollisionResponseToAllChannels(ECR_Overlap);
	PlacementCheckBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	PlacementCheckBox->SetBoxExtent(FVector(80.f, 80.f, 120.f));
	PlacementCheckBox->SetGenerateOverlapEvents(true);

	PreviewMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PreviewMesh"));
	PreviewMesh->SetupAttachment(RootComponent);
	PreviewMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ConstructorHelpers::FObjectFinder<UMaterialInterface> CanPlaceMaterialBP
	(TEXT("/Game/Asset/KayKit/DungeonElements/MaterialInstances/MI_Green.MI_Green"));

	if(CanPlaceMaterialBP.Succeeded()) CanPlaceMaterial = CanPlaceMaterialBP.Object;

	ConstructorHelpers::FObjectFinder<UMaterialInterface> CannotPlaceMaterialBP
	(TEXT("/Game/Asset/KayKit/DungeonElements/MaterialInstances/MI_Red.MI_Red"));

	if(CannotPlaceMaterialBP.Succeeded()) CannotPlaceMaterial = CannotPlaceMaterialBP.Object;
}

void AFieldPreviewItem::BeginPlay()
{
	Super::BeginPlay();

	SetGhostMaterial(true); // 최초엔 설치 가능 상태로
}

void AFieldPreviewItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult Hit;
	if(TraceToGround(Hit))
	{
		//Z축 보정
		float ZOffset = PreviewMesh ? PreviewMesh->Bounds.BoxExtent.Z : 40.f;

		//GridSnap
		const float GridSize = 50.f;
		float SnappedX = FMath::GridSnap(Hit.ImpactPoint.X, GridSize);
		float SnappedY = FMath::GridSnap(Hit.ImpactPoint.Y, GridSize);
		
		FVector ConfirmLocation(SnappedX, SnappedY, Hit.ImpactPoint.Z + ZOffset);

		SetActorLocation(ConfirmLocation);
		SetActorRotation(FRotator::ZeroRotator);

		bIsCanPlace = CheckCanPlace();
		SetGhostMaterial(bIsCanPlace);
	}
}

void AFieldPreviewItem::SetPreviewData(FName InItemID, EItemTypes InItemType)
{
	PreviewItemID = InItemID;
	PreviewItemType = InItemType;

	if(UItemSubsystem* ItemDB = GetGameInstance()->GetSubsystem<UItemSubsystem>())
	{
		const FItemMasterDataRow* Data = ItemDB->GetItemMasterData(PreviewItemID);
		if(Data && Data->ItemMesh)
		{
			PreviewMesh->SetStaticMesh(Data->ItemMesh);
		}
	}
}

bool AFieldPreviewItem::CheckCanPlace() const
{
	TArray<AActor*> OverlappingActors;
	PlacementCheckBox->GetOverlappingActors(OverlappingActors);

	for(AActor* Other : OverlappingActors)
	{
		if(Other == this) continue;

		if(Other->IsA<APlacementBlocker>() || Other->IsA<APlayerItem>()) return false;
	}
	return true;
}

void AFieldPreviewItem::ConfirmPlacement()
{
	if (!CheckCanPlace()) return;

	UItemSubsystem* ItemDB = GetGameInstance()->GetSubsystem<UItemSubsystem>();
	if (!ItemDB) return;

	const FItemMasterDataRow* DataRow = ItemDB->GetItemMasterData(PreviewItemID);
	if (!DataRow || !DataRow->ItemClass) return;

	FActorSpawnParameters Params;
	Params.Owner = GetOwner();

	APlayerItem* Placed = GetWorld()->SpawnActor<APlayerItem>(DataRow->ItemClass, GetActorLocation(), GetActorRotation(), Params);

	Destroy();
}

bool AFieldPreviewItem::TraceToGround(FHitResult& HitResult) const
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PC) return false;

	float MouseX, MouseY;
	if (!PC->GetMousePosition(MouseX, MouseY)) return false;

	FVector WorldLoc, WorldDir;
	if (!PC->DeprojectScreenPositionToWorld(MouseX, MouseY, WorldLoc, WorldDir)) return false;

	FVector Start = WorldLoc;
	FVector End = Start + WorldDir * 10000.f;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	return GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);
}

void AFieldPreviewItem::SetGhostMaterial(bool bCanPlace)
{
	UMaterialInterface* SelectedMat = bCanPlace ? CanPlaceMaterial : CannotPlaceMaterial;

	if(PreviewMesh && SelectedMat)
	{
		PreviewMesh->SetMaterial(0, SelectedMat);
	}
}
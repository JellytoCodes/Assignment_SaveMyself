#include "FieldPreviewItem.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ItemSubsystem.h"
#include "StructureItem.h"
#include "TrapItem.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

AFieldPreviewItem::AFieldPreviewItem()
{
	PrimaryActorTick.bCanEverTick = true;

	PlacementCheckBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PlacementCheckBox"));
	SetRootComponent(PlacementCheckBox);
	PlacementCheckBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PlacementCheckBox->SetCollisionResponseToAllChannels(ECR_Overlap);
	PlacementCheckBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	PlacementCheckBox->SetGenerateOverlapEvents(true);

	PreviewMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PreviewMesh"));
	PreviewMesh->SetupAttachment(RootComponent);
	PreviewMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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
		SetActorLocation(Hit.Location);
		SetActorRotation(FRotator::ZeroRotator);
		const bool bCanPlace = CheckCanPlace();
		SetGhostMaterial(bCanPlace);
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
	PlacementCheckBox->GetOverlappingActors(OverlappingActors, APlayerItem::StaticClass());

	for(AActor* Other : OverlappingActors)
	{
		if (Other != this)
		{
			return false;
		}
	}
	return true;
}

void AFieldPreviewItem::ConfirmPlacement()
{
	UE_LOG(LogTemp, Log, TEXT("Called ConfirmPlacement"));
	if (!CheckCanPlace()) return;

	UItemSubsystem* ItemDB = GetGameInstance()->GetSubsystem<UItemSubsystem>();
	if (!ItemDB) return;

	const FItemMasterDataRow* DataRow = ItemDB->GetItemMasterData(PreviewItemID);
	if (!DataRow || !DataRow->ItemClass) return;

	FActorSpawnParameters Params;
	Params.Owner = GetOwner();

	APlayerItem* Placed = GetWorld()->SpawnActor<APlayerItem>(DataRow->ItemClass, GetActorLocation(), GetActorRotation(), Params);

	UE_LOG(LogTemp, Log, TEXT("Ended ConfirmPlacement"));
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
	// TODO: 프리뷰 머티리얼 교체 (초록/빨강)
	// 이 함수는 MaterialInstanceDynamic이나 CustomDepth로 교체 예정
}
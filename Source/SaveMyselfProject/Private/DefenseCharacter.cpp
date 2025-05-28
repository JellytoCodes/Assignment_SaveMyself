// Fill out your copyright notice in the Description page of Project Settings.

#include "DefenseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/DataTable.h"
#include "WeaponItem.h"
#include "StructureItem.h"
#include "TrapItem.h"
#include "DefenseGameModeBase.h"
#include "DefenseHUD.h"
#include "PlayerItem.h"
#include "StorageSlot.h"
#include "StorageWidget.h"
#include "QuickSlotWidget.h"
#include "FieldPreviewItem.h"
#include "PlayerHPWidget.h"
#include "SaveHelper.h"

// Sets default values
ADefenseCharacter::ADefenseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//카메라 시점 설정
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));
	FollowCamera->bUsePawnControlRotation = false;

	bUseControllerRotationPitch	= false;
	bUseControllerRotationRoll	= false;
	bUseControllerRotationYaw	= false;

	//플레이어 바디 설정
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> PlayerMesh(TEXT("/Game/Asset/KayKit/Characters/barbarian.barbarian"));
	if(PlayerMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(PlayerMesh.Object);
	}

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	Tags.Add(FName("Player"));
}

// Called when the game starts or when spawned
void ADefenseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if(APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if(UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			SubSystem->AddMappingContext(IMC_Default, 0);
		}
	}

	TArray<FName> RowNames = ItemMasterDataTable->GetRowNames();
	for(const FName& RowName : RowNames)
	{
		const FItemMasterDataRow* Row = ItemMasterDataTable->FindRow<FItemMasterDataRow>(RowName, "ItemInit");
		if(Row)
		{
			ItemMasterDataMap.Add(RowName, Row);
		}
	}
	
	ADefenseGameModeBase* DefenseMode = Cast<ADefenseGameModeBase>(UGameplayStatics::GetGameMode(this));
    if(DefenseMode)
    {
        StageManager = DefenseMode->GetStageManager();
    }

	ADefenseHUD* HUD = Cast<ADefenseHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if(HUD)
	{
		HUD->ShowPlayerHPWidget();
		HUD->ShowPlayerQuickSlotWidget();
	}
}

// Called every frame
void ADefenseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADefenseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//플레이어 키 바인드 액션 할당
	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ADefenseCharacter::Move);
		EnhancedInputComponent->BindAction(IA_LookNTurn, ETriggerEvent::Triggered, this, &ADefenseCharacter::LookNTurn);
		EnhancedInputComponent->BindAction(IA_Interact, ETriggerEvent::Triggered, this, &ADefenseCharacter::Interact);
		EnhancedInputComponent->BindAction(IA_Fire, ETriggerEvent::Started, this, &ADefenseCharacter::SpwanPlayerItem);

		//-----------------------아이템 키 바인드-----------------------//
		EnhancedInputComponent->BindAction(IA_QuickSlot01, ETriggerEvent::Started, this, &ADefenseCharacter::SelectQuickSlot01);
		EnhancedInputComponent->BindAction(IA_QuickSlot02, ETriggerEvent::Started, this, &ADefenseCharacter::SelectQuickSlot02);
		EnhancedInputComponent->BindAction(IA_QuickSlot03, ETriggerEvent::Started, this, &ADefenseCharacter::SelectQuickSlot03);
		EnhancedInputComponent->BindAction(IA_QuickSlot04, ETriggerEvent::Started, this, &ADefenseCharacter::SelectQuickSlot04);
		EnhancedInputComponent->BindAction(IA_QuickSlot05, ETriggerEvent::Started, this, &ADefenseCharacter::SelectQuickSlot05);
		EnhancedInputComponent->BindAction(IA_QuickSlot06, ETriggerEvent::Started, this, &ADefenseCharacter::SelectQuickSlot06);
		EnhancedInputComponent->BindAction(IA_QuickSlot07, ETriggerEvent::Started, this, &ADefenseCharacter::SelectQuickSlot07);
		EnhancedInputComponent->BindAction(IA_QuickSlot08, ETriggerEvent::Started, this, &ADefenseCharacter::SelectQuickSlot08);

		//플레이어 HP 감소 체크
		EnhancedInputComponent->BindAction(PlayerDamaged, ETriggerEvent::Started, this, &ADefenseCharacter::TestPlayerDamaged);
	}
}


void ADefenseCharacter::Move(const FInputActionValue &value)
{
	if(bIsDeath) return;
	
	const auto MovementVector = value.Get<FVector2D>();

	if(Controller != nullptr)
	{
		const auto Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const auto ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const auto RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ADefenseCharacter::LookNTurn(const FInputActionValue &value)
{
	//각 상태에 따른 기능 비활성화
	if(bMouseCursorUsed || bIsPreview || bIsDeath) return;

	const auto LookAxisVector = value.Get<FVector2D>();

	if(Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X * LookSensitivity);
		AddControllerPitchInput(-(LookAxisVector.Y * LookSensitivity));
	}
}

void ADefenseCharacter::Interact(const FInputActionValue &value)
{
	UE_LOG(LogTemp, Log, TEXT("Interact!"));
}

void ADefenseCharacter::SpwanPlayerItem()
{
	//각 상태에 따른 기능 비활성화
	if(bMouseCursorUsed || bIsDeath) return;

	ADefenseHUD* HUD = Cast<ADefenseHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if(!HUD) return;

	for(int32 i = 0; i < HUD->GetQuicklotWidget()->saveSlot.Num(); ++i)
	{
		//아이템 수량 소진 시 return
		if(HUD->GetQuicklotWidget()->saveSlot[i].Quantity < 1) return;

		if(HUD->GetQuicklotWidget()->saveSlot[i].ItemID == playerItemID)
		{
			if(PreviewInstance)
			{
				PreviewInstance->ConfirmPlacement();

				//설치 가능일 때만 수량 감소가 가능하도록 설정
				if(PreviewInstance->GetbCanPlace()) HUD->GetQuicklotWidget()->UseQuickSlotItem(i);
				bIsPreview = false;					
				return;	
			}

			else
			{
				ThrowWeapon();
				
				//무기를 던진 뒤 수량 감소 처리
				HUD->GetQuicklotWidget()->UseQuickSlotItem(i);
				return;	
			}			
		}		
	}
}

void ADefenseCharacter::RequestPreviewItem(FName ItemID, EItemTypes ItemType)
{
	if(PreviewInstance)
	{
		PreviewInstance->Destroy();
		PreviewInstance = nullptr;
		bIsPreview = false;
	}

	if (ItemType != EItemTypes::Structure && ItemType != EItemTypes::Trap) return;

	bIsPreview = true;

	FActorSpawnParameters Params;
	Params.Owner = this;

	FVector SpawnLoc = GetActorLocation();
	FRotator SpawnRot = GetActorRotation();

	PreviewInstance = GetWorld()->SpawnActor<AFieldPreviewItem>(PreviewClass, SpawnLoc, SpawnRot, Params);
	if (PreviewInstance)
	{
		PreviewInstance->SetPreviewData(ItemID, ItemType);
	}
}

void ADefenseCharacter::ThrowWeapon()
{
	const FItemMasterDataRow* ItemMasterDataRow = ItemMasterDataMap[playerItemID];
	if(!ItemMasterDataRow || !ItemMasterDataRow->ItemClass) return;

	const auto ItemSpawnLocation = GetActorTransform().TransformPosition(ItemMasterDataRow->LocalOffSet);
	const auto ItemSpawnRotation = GetMesh()->GetComponentRotation();
	auto ItemSpawnPrams = FActorSpawnParameters();

	ItemSpawnPrams.Owner = this;
	ItemSpawnPrams.Instigator = GetInstigator();

	APlayerItem* SpawnedItem = 
	GetWorld()->SpawnActor<APlayerItem>(ItemMasterDataRow->ItemClass, ItemSpawnLocation, ItemSpawnRotation, ItemSpawnPrams);
	UE_LOG(LogTemp, Warning, TEXT("ThrowWeapon"));
}

void ADefenseCharacter::TestPlayerDamaged()
{	
	ADefenseHUD* HUD = Cast<ADefenseHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if(!HUD) return;
	
	HUD->UpdatedPlayerHP(PlayerHP);
	PlayerHP--;
	
}

void ADefenseCharacter::ReceiveDamage_Implementation(float Damage)
{
	ADefenseHUD* HUD = Cast<ADefenseHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if(!HUD) return;

	HUD->UpdatedPlayerHP(PlayerHP);

	if(PlayerHP > 1)
	{
		PlayerHP -= Damage;
	}
	else 
	{
		bIsDeath = true;
		StageManager->CheckEndPhaseConditions(bIsDeath);
		PlayerHP = 0;
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		SetActorRotation(FRotator(90.f, 0.f, 0.f));
	}
}

void ADefenseCharacter::bEntranceShowMouseCursor()
{
	APlayerController* playerController = Cast<APlayerController>(GetController());
	if(playerController)
	{
		playerController->bShowMouseCursor = true;
		bMouseCursorUsed = true;
	}
}

void ADefenseCharacter::bExitHideMouseCursor()
{
	APlayerController* playerController = Cast<APlayerController>(GetController());
	if(playerController)
	{
		playerController->bShowMouseCursor = false;
		bMouseCursorUsed = false;
	}
}

void ADefenseCharacter::SelectQuickSlot(int32 index)
{
	ADefenseHUD* HUD = Cast<ADefenseHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if(!HUD) return;

	const FStorageArrRow* itemData = HUD->GetQuicklotWidget()->GetQuickSlotItem(index - 1);

	if (!itemData) 
	{
		playerItemID = NAME_None;

		// 기존 프리뷰 제거
		if (PreviewInstance)
		{
			PreviewInstance->Destroy();
			PreviewInstance = nullptr;
		}
		return;
	}

	playerItemID = itemData->ItemID;

	const FItemMasterDataRow* ItemDataRow = ItemMasterDataMap[playerItemID];
	if (!ItemDataRow) return;

	RequestPreviewItem(ItemDataRow->ItemID, ItemDataRow->ItemType);
}

void ADefenseCharacter::BindStorageSlot(UStorageSlot *StorageSlot)
{
	if(StorageSlot)
	{
		StorageSlot->ItemSlotDelegate.AddDynamic(this, &ADefenseCharacter::QuickSlotHandling);
	}
}

void ADefenseCharacter::QuickSlotHandling(UStorageSlot *ClickedSlot)
{
	ADefenseHUD* HUD = Cast<ADefenseHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if(!HUD) return;

	if(HUD->GetQuicklotWidget())
	{
		HUD->GetQuicklotWidget()->AddItemQuickSlot(ClickedSlot);
	}
}
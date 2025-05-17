// Fill out your copyright notice in the Description page of Project Settings.

#include "DefenseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/DataTable.h"
#include "WeaponItem.h"
#include "StructureItem.h"
#include "TrapItem.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerItem.h"
#include "StorageSlot.h"
#include "StorageWidget.h"
#include "QuickSlotWidget.h"

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

	//플레이어 퀵슬롯 설정
	static ConstructorHelpers::FClassFinder<UQuickSlotWidget> quickSlotWidgetBP(TEXT("/Game/WidgetBP/WBP_QuickSlotWidget.WBP_QuickSlotWidget_C"));
	if(quickSlotWidgetBP.Succeeded())
	{
		quickSlotWidgetClass = quickSlotWidgetBP.Class;
	}
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

	quickSlotWidgetInstance = CreateWidget<UQuickSlotWidget>(GetWorld(), quickSlotWidgetClass);
	if(quickSlotWidgetInstance) quickSlotWidgetInstance->AddToViewport();
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
		EnhancedInputComponent->BindAction(IA_QuickSlot09, ETriggerEvent::Started, this, &ADefenseCharacter::SelectQuickSlot09);
		EnhancedInputComponent->BindAction(IA_QuickSlot10, ETriggerEvent::Started, this, &ADefenseCharacter::SelectQuickSlot10);
	}
}


void ADefenseCharacter::Move(const FInputActionValue &value)
{
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
	if(bMouseCursorUsed) return;
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
	if(bMouseCursorUsed) return;

	//크래시 방지
	if(playerItemID == NAME_None)
	{
		UE_LOG(LogTemp, Log, TEXT("None Item"));
		return;
	}
	const FItemMasterDataRow* ItemMasterDataRow = ItemMasterDataMap[playerItemID];

	//Weapon Item일 경우 무기 발사
	if(ItemMasterDataRow->ItemType == EItemTypes::Weapon)
	{
		UE_LOG(LogTemp, Log, TEXT("Fire"));
		
		const auto WeaponSpawnLocation = GetActorTransform().TransformPosition(ItemMasterDataRow->LocalOffSet);
		const auto WeaponSpawnRotation = GetMesh()->GetComponentRotation();
		auto WeaponSpawnPrams = FActorSpawnParameters();

		WeaponSpawnPrams.Owner = this;
		WeaponSpawnPrams.Instigator = GetInstigator();
		GetWorld()->SpawnActor<AWeaponItem>(ItemMasterDataRow->ItemClass, WeaponSpawnLocation, WeaponSpawnRotation, WeaponSpawnPrams);
	}

	//Structure Item일 경우 플레이어 전방 기준으로 구조물 설치
	else if(ItemMasterDataRow->ItemType == EItemTypes::Structure)
	{
		UE_LOG(LogTemp, Log, TEXT("Structure"));
		
		const auto StructureSpawnLocation = GetActorTransform().TransformPosition(ItemMasterDataRow->LocalOffSet);
		const auto StructureSpawnRotation = GetMesh()->GetComponentRotation();
		auto StructureSpawnPrams = FActorSpawnParameters();

		StructureSpawnPrams.Owner = this;
		StructureSpawnPrams.Instigator = GetInstigator();
		GetWorld()->SpawnActor<AStructureItem>(ItemMasterDataRow->ItemClass, StructureSpawnLocation, StructureSpawnRotation, StructureSpawnPrams);
	}

	//Trap Item일 경우 플레이어 전방 기준으로 구조물 설치
	else if(ItemMasterDataRow->ItemType == EItemTypes::Trap)
	{
		UE_LOG(LogTemp, Log, TEXT("Trap"));
		
		const auto TrapSpawnLocation = GetActorTransform().TransformPosition(ItemMasterDataRow->LocalOffSet);
		const auto TrapSpawnRotation = GetMesh()->GetComponentRotation();
		auto TrapSpawnPrams = FActorSpawnParameters();

		TrapSpawnPrams.Owner = this;
		TrapSpawnPrams.Instigator = GetInstigator();
		GetWorld()->SpawnActor<ATrapItem>(ItemMasterDataRow->ItemClass, TrapSpawnLocation, TrapSpawnRotation, TrapSpawnPrams);
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

void ADefenseCharacter::BindStorageSlot(UStorageSlot *StorageSlot)
{
	if(StorageSlot)
	{
		StorageSlot->ItemSlotDelegate.AddDynamic(this, &ADefenseCharacter::QuickSlotHandling);
	}
}

void ADefenseCharacter::QuickSlotHandling(UStorageSlot *ClickedSlot)
{
	if(quickSlotWidgetInstance)
	{
		quickSlotWidgetInstance->AddItemQuickSlot(ClickedSlot);
	}
}

void ADefenseCharacter::SelectQuickSlot(int32 Index)
{
	UE_LOG(LogTemp, Log, TEXT("Quick Slot : %d"), Index);
	//스폰 테스트용
	if(Index == 1)
	{
		playerItemID = "Weapon001";
		UE_LOG(LogTemp, Log, TEXT("Item Type : %d"),ItemMasterDataMap[playerItemID]->ItemType);
	}
	else if(Index == 2)
	{
		playerItemID = "Structure001";
		UE_LOG(LogTemp, Log, TEXT("Item Type : %d"),ItemMasterDataMap[playerItemID]->ItemType);
	}
	else if(Index == 3)
	{
		playerItemID = "Trap001";
		UE_LOG(LogTemp, Log, TEXT("Item Type : %d"),ItemMasterDataMap[playerItemID]->ItemType);
	}
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "DefenseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/DataTable.h"
#include "WeaponItem.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerItem.h"

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
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> PlayerMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/KayKit/Characters/barbarian.barbarian'"));
	if(PlayerMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(PlayerMesh.Object);
	}

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
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
		EnhancedInputComponent->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &ADefenseCharacter::Fire);
		EnhancedInputComponent->BindAction(IA_Inventory, ETriggerEvent::Triggered, this, &ADefenseCharacter::Inventory);
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

void ADefenseCharacter::Fire(const FInputActionValue &value)
{
	//무기 스폰 테스트용
	FName WeaponID = "Weapon001";
	const FItemMasterDataRow* ItemMasterDataRow = ItemMasterDataMap[WeaponID];

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
}

void ADefenseCharacter::Inventory(const FInputActionValue &value)
{
	if(!bIsInventory)
	{
		UE_LOG(LogTemp, Log, TEXT("Inventory Open"));
		bIsInventory = !bIsInventory;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Inventory Close"));
		bIsInventory = !bIsInventory;
	}
}


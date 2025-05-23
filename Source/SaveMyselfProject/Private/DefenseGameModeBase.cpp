// Fill out your copyright notice in the Description page of Project Settings.

#include "DefenseGameModeBase.h"
#include "DefenseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "DefenseHUD.h"

ADefenseGameModeBase::ADefenseGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn>PlayerPawnBPClass(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_DefenseCharacter'"));
	if(PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	HUDClass = ADefenseHUD::StaticClass();
	StageManager = CreateDefaultSubobject<UStageManagerComponent>(TEXT("StageManager"));
}

void ADefenseGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Set BeginPlay"));

	if(StageManager)
	{
		StageManager->OnStageStateChanged.AddDynamic(this, &ADefenseGameModeBase::HandleStageState);
		StageManager->StartStage();
	}
}

void ADefenseGameModeBase::HandleStageState(EStageState NewState)
{
	UE_LOG(LogTemp, Log, TEXT("Called HandleStageState"));
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if(!PC)
	{
		UE_LOG(LogTemp, Log, TEXT("Failed GetPlayerController"));
		return;
	}
	ADefenseHUD* HUD = Cast<ADefenseHUD>(PC->GetHUD());
	if(!HUD)
	{
		UE_LOG(LogTemp, Log, TEXT("Failed GetHUD"));
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("Set NewState"));
	HUD->ShowStageWidget(NewState);
}

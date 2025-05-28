// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialManagerBase.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "SaveMyselfGameInstance.h"

void ATutorialManagerBase::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if(PC)
	{
		PC->bShowMouseCursor = true;
	}

	auto gInstance = Cast<USaveMyselfGameInstance>(GetGameInstance());
	if(gInstance)
	{
		gInstance->LoadStageDataByLevelName();
	}
}

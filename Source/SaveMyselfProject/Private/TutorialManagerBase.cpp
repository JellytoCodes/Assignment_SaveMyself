// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialManagerBase.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "SaveMyselfGameInstance.h"

void ATutorialManagerBase::BeginPlay()
{
	Super::BeginPlay();

	auto gInstance = Cast<USaveMyselfGameInstance>(GetGameInstance());
	if(gInstance)
	{
		gInstance->LoadStageDataByLevelName();
	}
}

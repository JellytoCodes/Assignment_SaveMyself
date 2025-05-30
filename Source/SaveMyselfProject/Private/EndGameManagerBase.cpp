// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGameManagerBase.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

void AEndGameManagerBase::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if(PC)
	{
		PC->bShowMouseCursor = true;
	}
}

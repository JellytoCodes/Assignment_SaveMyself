// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveHelper.h"
#include "Kismet/GameplayStatics.h"
#include "DefenseSaveGame.h"

void USaveHelper::SaveRoundData(int32 InRoundNum)
{
	UDefenseSaveGame* SaveGameInstance = Cast<UDefenseSaveGame>
	(UGameplayStatics::CreateSaveGameObject(UDefenseSaveGame::StaticClass()));

	if(!SaveGameInstance) return;

	SaveGameInstance->SetSavedRoundNum(InRoundNum);

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("DefenseSaveSlot"), 0);
	UE_LOG(LogTemp, Log, TEXT("Saved RoundNum : %d"), InRoundNum);
}

int32 USaveHelper::LoadRoundData()
{
	UDefenseSaveGame* LoadedInstance = Cast<UDefenseSaveGame>
	(UGameplayStatics::LoadGameFromSlot(TEXT("DefenseSaveSlot"), 0));

	if(!LoadedInstance) 
	{
		UE_LOG(LogTemp, Warning, TEXT("No SaveGame found. Defaulting to Round 1."));
		return 1;
	}

	int32 LoadedRound = LoadedInstance->GetSavedRoundNum();
	return LoadedRound;
}

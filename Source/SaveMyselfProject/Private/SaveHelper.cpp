// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveHelper.h"
#include "Kismet/GameplayStatics.h"
#include "DefenseSaveGame.h"

void USaveHelper::SaveStageData(FName inStageID)
{
	UDefenseSaveGame* SaveGameInstance = Cast<UDefenseSaveGame>
	(UGameplayStatics::CreateSaveGameObject(UDefenseSaveGame::StaticClass()));

	if(!SaveGameInstance) return;

	SaveGameInstance->SetSavedStage(inStageID);

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("DefenseSaveSlot"), 0);
	UE_LOG(LogTemp, Log, TEXT("SaveStageData : %s"), *inStageID.ToString());
}

FName USaveHelper::LoadStageData()
{
	UDefenseSaveGame* LoadedInstance = Cast<UDefenseSaveGame>
	(UGameplayStatics::LoadGameFromSlot(TEXT("DefenseSaveSlot"), 0));

	if(!LoadedInstance) 
	{
		UE_LOG(LogTemp, Warning, TEXT("No SaveGame found"));
		return NAME_None;
	}

	FName LoadedRound = LoadedInstance->GetSavedStage();
	return LoadedRound;
}

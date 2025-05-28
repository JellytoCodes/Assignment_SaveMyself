// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveMyselfGameInstance.h"
#include "Kismet/GameplayStatics.h"

void USaveMyselfGameInstance::LoadStageDataByLevelName()
{
	FString LevelName = UGameplayStatics::GetCurrentLevelName(this, true);
	FString AssetPath = FString::Printf(TEXT("/Game/DataAsset/DA_%s.DA_%s"), *LevelName, *LevelName);

	FSoftObjectPath SoftPath(*AssetPath);
	UObject* LoadedAsset = SoftPath.TryLoad();

	if(LoadedAsset)
	{
		currentStageData = Cast<UStageDataAsset>(LoadedAsset);
		if(currentStageData) curStageID = currentStageData->NextStageID;
	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "StageDataAsset.h"
#include "SaveMyselfGameInstance.generated.h"

UCLASS()
class SAVEMYSELFPROJECT_API USaveMyselfGameInstance : public UGameInstance
{
	GENERATED_BODY()

public :
	UPROPERTY(BlueprintReadOnly)
	UStageDataAsset* currentStageData;

	UFUNCTION(BlueprintCallable)
	void LoadStageDataByLevelName();

//-----------------------StageDataAsset Getter & Setter-----------------------//
public : 
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FName GetStageID() const { return currentStageData ? currentStageData->StageID : NAME_None; }
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FName GetNextStageID() const { return currentStageData ? currentStageData->NextStageID : NAME_None; }
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetMaxBagWeight() const { return currentStageData ? currentStageData->MaxBagWeight : 0; }
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetPrepareTime() const { return currentStageData ? currentStageData->PrepareTime : 0; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetBattleTime() const { return currentStageData ? currentStageData->BattleTime : 0; }
};

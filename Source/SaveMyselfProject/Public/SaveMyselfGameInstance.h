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

protected : 
	//캐릭터 배낭 무게 설정
	int32 maxBagWeight = 20;
	int32 curBagWeight = 0;

	bool BagAmount = true;

public :	
	const int32 GetCurBagWeight() { return curBagWeight; }
	void SetBagWeight(int32 curWeight) { curBagWeight += curWeight; }
	
	const bool GetBagAmount() { return BagAmount; }
	void SetBagAmount(bool setAmount) { BagAmount = setAmount; }

//-----------------------StageDataAsset Getter-----------------------//
public : 
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetMaxBagWeight() const { return currentStageData ? currentStageData->MaxBagWeight : 0; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetPrepareTime() const { return currentStageData ? currentStageData->PrepareTime : 0; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetBattleTime() const { return currentStageData ? currentStageData->BattleTime : 0; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsEliteMonsterEnabled() const { return currentStageData ? currentStageData->bAllowElite : 0; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	const TArray<FMonsterSpawnInfo>& GetMonsterList() const 
	{ 
		static TArray<FMonsterSpawnInfo> EmptyList;
		return currentStageData ? currentStageData->MonsterList : EmptyList; 
	}

};

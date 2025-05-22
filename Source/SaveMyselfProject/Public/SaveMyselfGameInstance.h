// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SaveMyselfGameInstance.generated.h"

UCLASS()
class SAVEMYSELFPROJECT_API USaveMyselfGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
protected : 
	//캐릭터 배낭 무게 설정
	int32 maxBagWeight = 20;
	int32 curBagWeight = 0;

	bool BagAmount = true;

public :
	const int32 GetCurBagWeight() { return curBagWeight; }
	const int32 GetMaxBagWeight() { return maxBagWeight; }
	void SetBagWeight(int32 curWeight) { curBagWeight += curWeight; }
	const bool GetBagAmount() { return BagAmount; }
	void SetBagAmount(bool setAmount) { BagAmount = setAmount; }
};

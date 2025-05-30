// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StageManagerComponent.h"
#include "DefenseGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SAVEMYSELFPROJECT_API ADefenseGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public :
	ADefenseGameModeBase();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	UFUNCTION()
	void HandleStageState(EStageState NewState);

private :
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStageManagerComponent* StageManager;

protected : 
	int32 curBagWeight = 0;

	bool BagAmount = true;

public :	
	const int32 GetCurBagWeight() { return curBagWeight; }
	void SetBagWeight(int32 curWeight) { curBagWeight += curWeight; }
	
	const bool GetBagAmount() { return BagAmount; }
	void SetBagAmount(bool setAmount) { BagAmount = setAmount; }

public :
	FORCEINLINE class UStageManagerComponent* GetStageManager() const { return StageManager; }
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StageManagerComponent.generated.h"

UENUM(BlueprintType)
enum class EStageState : uint8
{
	Prepare,
	Battle,
	End,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStageStateChanged, EStageState, NewState);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SAVEMYSELFPROJECT_API UStageManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStageManagerComponent();

protected:
	virtual void BeginPlay() override;

public :
	void StartStage();
	void CheckEndPhaseConditions();

	UPROPERTY(BlueprintAssignable)
	FOnStageStateChanged OnStageStateChanged;

private :
	void PreparePhase();
	void BattlePhase();
	void EndPhase();

	EStageState CurrentStageState;

	FTimerHandle PrepareTimerHandle;
	FTimerHandle BattleTimerHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Timer", meta = (AllowPrivateAccess = "true"))
	float PrepareTime = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "Timer", meta = (AllowPrivateAccess = "true"))
	float BattleTime = 15.f;

	bool bHasEnded = false;

	UPROPERTY()
	class AMonsterSpawner* MonsterSpawner;
};

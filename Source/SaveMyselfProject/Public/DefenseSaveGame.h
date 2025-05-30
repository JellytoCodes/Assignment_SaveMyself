// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "DefenseSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class SAVEMYSELFPROJECT_API UDefenseSaveGame : public USaveGame
{
	GENERATED_BODY()

public :
	UDefenseSaveGame();

private :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveData", meta = (AllowPrivateAccess = "true"))
	FName LastClearedStage;

public : //Getter & Setter 관리
	FName GetSavedStage() const { return LastClearedStage; }
	void SetSavedStage(FName setClearedStage) { LastClearedStage = setClearedStage; }
};

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
	int32 SavedRoundNum;

public : //Getter & Setter °ü¸®
	FORCEINLINE int32 GetSavedRoundNum() const { return SavedRoundNum; }
	FORCEINLINE void SetSavedRoundNum(int32 SetRoundNum) { SavedRoundNum = SetRoundNum; }
};

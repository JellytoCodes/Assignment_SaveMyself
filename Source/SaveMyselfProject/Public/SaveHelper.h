// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SaveHelper.generated.h"

/**
 * 
 */
UCLASS()
class SAVEMYSELFPROJECT_API USaveHelper : public UObject
{
	GENERATED_BODY()

public :
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	static void SaveRoundData(int32 InRoundNum);

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	static int32 LoadRoundData();

};

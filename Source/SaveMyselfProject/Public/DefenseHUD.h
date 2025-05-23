// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "StageManagerComponent.h"
#include "DefenseHUD.generated.h"

class UStageWidget;


UCLASS()
class SAVEMYSELFPROJECT_API ADefenseHUD : public AHUD
{
	GENERATED_BODY()

public :
	ADefenseHUD();

	void ShowStageWidget(EStageState NewState);

protected :
	
private :
	//Stage Widget
	UPROPERTY(EditDefaultsOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UStageWidget> StageWidgetClass;

	UStageWidget* StageWidgetInstance;

};

// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenseGameModeBase.h"
#include "DefenseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ADefenseGameModeBase::ADefenseGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn>PlayerPawnBPClass(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_DefenseCharacter'"));
	if(PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

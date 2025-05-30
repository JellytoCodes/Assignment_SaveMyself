// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlacementBlocker.generated.h"

UCLASS()
class SAVEMYSELFPROJECT_API APlacementBlocker : public AActor
{
	GENERATED_BODY()
	
public:	
	APlacementBlocker();

private :
	UPROPERTY(EditDefaultsOnly, Category = "Blocker", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BlockMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Blocker", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BlockCollision;
};

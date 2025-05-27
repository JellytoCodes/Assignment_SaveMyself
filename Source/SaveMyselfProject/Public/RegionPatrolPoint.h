// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RegionPatrolPoint.generated.h"

UCLASS()
class SAVEMYSELFPROJECT_API ARegionPatrolPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	ARegionPatrolPoint();

protected:
	virtual void BeginPlay() override;

private :
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Region", meta = (AllowPrivateAccess = "true"))
	FName RegionName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Region", meta = (AllowPrivateAccess = "true"))
	float RegionRadius = 100.f;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "PlayerItem.generated.h"

struct FItemDataRow;

UCLASS()
class SAVEMYSELFPROJECT_API APlayerItem : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	APlayerItem();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	class USphereComponent* SphereCollision;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* BoxCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	class UProjectileMovementComponent* ProjectileMovement;

public :
	virtual void EnableItemData(FName ItemID) PURE_VIRTUAL(APlayerItem::EnableItemData, );
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerItem.h"
#include "ItemMasterTable.h"
#include "WeaponItemTable.h"
#include "WeaponItem.generated.h"

UCLASS()
class SAVEMYSELFPROJECT_API AWeaponItem : public APlayerItem
{
	GENERATED_BODY()

public :
	AWeaponItem();

protected :
	virtual void BeginPlay() override;

	//ItemMasterDataTable 식별 ID
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ItemData")
	FName ItemMasterID = NAME_None;

	//ItemWeaponDataTable 식별 ID
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ItemData")
	FName ItemWeaponID = NAME_None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ItemData")
	UDataTable* WeaponData;

public :
	UFUNCTION()
	void OnWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual FVector GetLocalOffSet() override;
};

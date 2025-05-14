// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerItem.h"
#include "TrapItemTable.h"
#include "TrapItem.generated.h"

/**
 * 
 */
UCLASS()
class SAVEMYSELFPROJECT_API ATrapItem : public APlayerItem
{
	GENERATED_BODY()

public :
	ATrapItem();

protected :
	virtual void BeginPlay() override;

	//ItemMasterDataTable 식별 ID
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ItemData")
	FName ItemMasterID = NAME_None;

	//ItemTrapDataTable 식별 ID
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ItemData")
	FName ItemTrapID = NAME_None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ItemData")
	UDataTable* TrapData;

public :
	//적이 트랩 밟을 시 처리하기 위한 Overlap
	UFUNCTION()
	void OnTrapOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};

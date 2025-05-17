// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerItem.h"
#include "StructureItemTable.h"
#include "StructureItem.generated.h"

UCLASS()
class SAVEMYSELFPROJECT_API AStructureItem : public APlayerItem
{
	GENERATED_BODY()

public :
	AStructureItem();

	UFUNCTION()
	void OnStructureOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

protected :
	virtual void BeginPlay() override;

	//ItemMasterDataTable 식별 ID
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ItemData")
	FName ItemMasterID = NAME_None;

	//ItemTrapDataTable 식별 ID
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ItemData")
	FName ItemStructureID = NAME_None;
};

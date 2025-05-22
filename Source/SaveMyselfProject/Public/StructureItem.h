// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerItem.h"
#include "StructureItemTable.h"
#include "DamagebleInterface.h"
#include "StructureItem.generated.h"

UCLASS()
class SAVEMYSELFPROJECT_API AStructureItem : public APlayerItem, public IDamagebleInterface
{
	GENERATED_BODY()

public :
	AStructureItem();

protected :
	virtual void BeginPlay() override;

	virtual void ReceiveDamage_Implementation(float Damage) override;

public :

	UFUNCTION()
	void OnStructureOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	
	//아이템 정보 삽입
	virtual void EnableItemData(FName ItemID) override;

private : 
	//BP에서 아이템 ID 관리
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ItemID", meta = (AllowPrivateAccess = "true"))
	FName getItemName;

	//데이터 테이블 기반 아이템 정보
	FName structureName;
	float structureHP;
	float structureDefense;
	float maxCoolTime;
	float curHP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ItemID", meta = (AllowPrivateAccess = "true"))
	class UAIPerceptionStimuliSourceComponent* StimuliSourceComp;
};

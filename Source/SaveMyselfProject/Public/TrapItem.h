// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerItem.h"
#include "DamagebleInterface.h"
#include "TrapItemTable.h"
#include "TrapItem.generated.h"

class AMonsterBase;

UCLASS()
class SAVEMYSELFPROJECT_API ATrapItem : public APlayerItem, public IDamagebleInterface
{
	GENERATED_BODY()

public :
	ATrapItem();

protected :
	virtual void BeginPlay() override;

public :
	UFUNCTION()
	void OnTrapOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	//아이템 정보 삽입
	virtual void EnableItemData(FName ItemID) override;

private :
	//BP에서 아이템 ID 관리
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ItemID", meta = (AllowPrivateAccess = "true"))
	FName getItemName;

	//데이터 테이블 기반 아이템 정보
	FName trapName;
	float trapEffect;
	float maxCoolTime;
	ETrapType trapType;

	bool bIsTriggered = false;

	TArray<AMonsterBase*> GetMonstersRadius(float Radius);

	void TriggerExplosiveEffect();
	void TriggerBindingEffect();
};

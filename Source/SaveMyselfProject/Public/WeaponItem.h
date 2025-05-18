// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerItem.h"
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

public :
	UFUNCTION()
	void OnWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	//아이템 정보 삽입
	virtual void EnableItemData(FName ItemID) override;

private : 	
	//BP에서 아이템 ID 관리
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ItemID", meta = (AllowPrivateAccess = "true"))
	FName getItemName;

	//데이터 테이블 기반 아이템 정보
	FName weaponName;
	float weaponDamage;
	float maxCoolTime;
	EDamageType damageType;

};

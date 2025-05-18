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
	
	//������ ���� ����
	virtual void EnableItemData(FName ItemID) override;

private : 	
	//BP���� ������ ID ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ItemID", meta = (AllowPrivateAccess = "true"))
	FName getItemName;

	//������ ���̺� ��� ������ ����
	FName weaponName;
	float weaponDamage;
	float maxCoolTime;
	EDamageType damageType;

};

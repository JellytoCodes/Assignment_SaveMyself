// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ItemMasterTable.h"
#include "WeaponItemTable.h"
#include "DefenseCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
struct FItemMasterDataRow;
struct FWeaponDataRow;

UCLASS()
class SAVEMYSELFPROJECT_API ADefenseCharacter : public ACharacter
{
	GENERATED_BODY()

//-----------------------Defaults 셋업-----------------------//
public:
	ADefenseCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	virtual void BeginPlay() override;

//-----------------------무빙 기능 셋업-----------------------//
private :
	//시점 설정
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "ture"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "ture"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "ture"))
	UInputMappingContext* IMC_Default;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "ture"))
	UInputAction* IA_Move;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "ture"))
	UInputAction* IA_LookNTurn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "ture"))
	UInputAction* IA_Interact;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "ture"))
	UInputAction* IA_Fire;

	//카메라 뷰 속도 조정
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "ture"))
	float LookSensitivity = .5f;

protected :
	//플레이어 키 바인드 액션
	void Move(const FInputActionValue& value);
	void LookNTurn(const FInputActionValue& value);
	void Interact(const FInputActionValue& value);

	//아이템 스폰을 위한 기능 (상세설명 정의 부분 참조)
	void SpwanPlayerItem(const FInputActionValue& value);

//-----------------------아이템 기능 셋업-----------------------//
protected : 
	//퀵슬롯 키 할당
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "ture"))
	UInputAction* IA_QuickSlot01;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "ture"))
	UInputAction* IA_QuickSlot02;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "ture"))
	UInputAction* IA_QuickSlot03;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "ture"))
	UInputAction* IA_QuickSlot04;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "ture"))
	UInputAction* IA_QuickSlot05;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "ture"))
	UInputAction* IA_QuickSlot06;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "ture"))
	UInputAction* IA_QuickSlot07;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "ture"))
	UInputAction* IA_QuickSlot08;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "ture"))
	UInputAction* IA_QuickSlot09;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "ture"))
	UInputAction* IA_QuickSlot10;

	//퀵슬롯 키 바인드 액션
	void SelectQuickSlot01() { SelectQuickSlot(1); }
	void SelectQuickSlot02() { SelectQuickSlot(2); }
	void SelectQuickSlot03() { SelectQuickSlot(3); }
	void SelectQuickSlot04() { SelectQuickSlot(4); }
	void SelectQuickSlot05() { SelectQuickSlot(5); }
	void SelectQuickSlot06() { SelectQuickSlot(6); }
	void SelectQuickSlot07() { SelectQuickSlot(7); }
	void SelectQuickSlot08() { SelectQuickSlot(8); }
	void SelectQuickSlot09() { SelectQuickSlot(9); }
	void SelectQuickSlot10() { SelectQuickSlot(10); }

	//퀵슬롯 키 바인드 마스터
	void SelectQuickSlot(int32 Index);

	FName PlayerItemID = NAME_None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DataTable")
	class UDataTable*	ItemMasterDataTable;	

	TMap<FName, const FItemMasterDataRow*> ItemMasterDataMap;
};

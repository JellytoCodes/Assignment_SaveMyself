// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ItemMasterTable.h"
#include "WeaponItemTable.h"
#include "ItemSubsystem.h"
#include "DamagebleInterface.h"
#include "DefenseCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class UQuickSlotWidget;
class UStorageSlot;
struct FInputActionValue;
struct FItemMasterDataRow;
struct FWeaponDataRow;

UCLASS()
class SAVEMYSELFPROJECT_API ADefenseCharacter : public ACharacter, public IDamagebleInterface
{
	GENERATED_BODY()

//-----------------------Defaults 셋업-----------------------//
public:
	ADefenseCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

//-----------------------캐릭터 디폴트 셋업-----------------------//
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

//-----------------------아이템 기능 셋업-----------------------//
private : 
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

	//퀵슬롯 키 바인드 액션
	void SelectQuickSlot01() { SelectQuickSlot(1); }
	void SelectQuickSlot02() { SelectQuickSlot(2); }
	void SelectQuickSlot03() { SelectQuickSlot(3); }
	void SelectQuickSlot04() { SelectQuickSlot(4); }
	void SelectQuickSlot05() { SelectQuickSlot(5); }
	void SelectQuickSlot06() { SelectQuickSlot(6); }
	void SelectQuickSlot07() { SelectQuickSlot(7); }
	void SelectQuickSlot08() { SelectQuickSlot(8); }

	//퀵슬롯 키 바인드 마스터
	void SelectQuickSlot(int32 index);

	//아이템 스폰 (상세설명 정의 부분 참조)
	void SpwanPlayerItem();

	FName playerItemID = NAME_None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DataTable", meta = (AllowPrivateAccess = "ture"))
	class UDataTable*	ItemMasterDataTable;

	TMap<FName, const FItemMasterDataRow*> ItemMasterDataMap;

	UPROPERTY()
	class AFieldPreviewItem* PreviewInstance = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Preview")
	TSubclassOf<AFieldPreviewItem> PreviewClass;

	void RequestPreviewItem(FName ItemID, EItemTypes ItemType);
	void ThrowWeapon();

public :
	void bEntranceShowMouseCursor();
	void bExitHideMouseCursor();

	bool bMouseCursorUsed = false;
	bool bIsPreview = false;

	//퀵슬롯 Widget
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget")
	TSubclassOf<UQuickSlotWidget> quickSlotWidgetClass;

	UFUNCTION()
	void BindStorageSlot(UStorageSlot* StorageSlot);
	
	UFUNCTION()
	void QuickSlotHandling(UStorageSlot* ClickedSlot);

	UQuickSlotWidget* quickSlotWidgetInstance;

//-----------------------체력 기능 셋업-----------------------//
private :
	int32 PlayerHP = 5;
	int32 GetPlayerHP() { return PlayerHP; }

	bool bIsDeath = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "ture"))
	UInputAction* PlayerDamaged;

	void TestPlayerDamaged();
	virtual void ReceiveDamage_Implementation(float Damage) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "ture"))
	class UStageManagerComponent* StageManager;

public :

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Widget")
	TSubclassOf<class UPlayerHPWidget> HPWidgetClass;

	UPlayerHPWidget* HPWidgetInstance;

};
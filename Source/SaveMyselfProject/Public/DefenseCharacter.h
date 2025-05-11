// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DefenseCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class SAVEMYSELFPROJECT_API ADefenseCharacter : public ACharacter
{
	GENERATED_BODY()

	//시점 설정
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "ture"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "ture"))
	class UCameraComponent* FollowCamera;

	//플레이어 키 할당
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "ture"))
	UInputAction* IA_Inventory;

	//변수 세팅
	//인벤토리 열기/닫기 설정
	bool bIsInventory = false;

	//카메라 뷰 속도 조정
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "ture"))
	float LookSensitivity = .5f;

public:
	// Sets default values for this character's properties
	ADefenseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//플레이어 키 바인드 액션
	void Move(const FInputActionValue& value);
	void LookNTurn(const FInputActionValue& value);
	void Interact(const FInputActionValue& value);
	void Fire(const FInputActionValue& value);
	void Inventory(const FInputActionValue& value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

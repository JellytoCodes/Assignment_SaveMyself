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

	//���� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "ture"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "ture"))
	class UCameraComponent* FollowCamera;

	//�÷��̾� Ű �Ҵ�
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

public:
	// Sets default values for this character's properties
	ADefenseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//�÷��̾� Ű ���ε� �׼�
	void Move(const FInputActionValue& value);
	void LookNTurn(const FInputActionValue& value);
	void Interact(const FInputActionValue& value);
	void Fire(const FInputActionValue& value);
	void Inventory(const FInputActionValue& value);

	//�κ��丮 ����/�ݱ� ����
	bool bIsInventory = false;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

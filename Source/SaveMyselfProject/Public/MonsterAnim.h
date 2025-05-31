// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnim.generated.h"

/**
 * 
 */
UCLASS()
class SAVEMYSELFPROJECT_API UMonsterAnim : public UAnimInstance
{
	GENERATED_BODY()

private :
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State", meta = (AllowPrivateAccess = "true"))
	float hDirectionSpeed = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State", meta = (AllowPrivateAccess = "true"))
	float vDirectionSpeed = 0;

	/* Anim Montage 할당은 BP에서만 관리하므로 nullptr 발생 주의 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Montage", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* deadMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Montage", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* attackMontage;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Montage", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* damageMontage;

public :
	void PlayDeadMontage();
	void PlayAttackMontage();
	void PlayDamageMontage();
};

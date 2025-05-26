// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerItem.h"
#include "ItemMasterTable.h"
#include "FieldPreviewItem.generated.h"

/**
 * 
 */
UCLASS()
class SAVEMYSELFPROJECT_API AFieldPreviewItem : public APlayerItem
{
	GENERATED_BODY()

public :
	AFieldPreviewItem();

	virtual void Tick(float DeltaTime) override;

	void SetPreviewData(FName InItemID, EItemTypes InItemType);

	bool CheckCanPlace() const;

	void ConfirmPlacement();

protected :
	virtual void BeginPlay() override;

	/** 마우스 아래 지면을 Trace하여 이동 */
	bool TraceToGround(FHitResult& HitResult) const;

	/** 프리뷰용 머티리얼 적용 */
	void SetGhostMaterial(bool bCanPlace);

private :
	UPROPERTY(EditDefaultsOnly, Category = "Preview", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* PlacementCheckBox;

	UPROPERTY(EditDefaultsOnly, Category = "Preview", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PreviewMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Preview", meta = (AllowPrivateAccess = "true"))
	class UMaterialInterface* CanPlaceMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "Preview", meta = (AllowPrivateAccess = "true"))
	class UMaterialInterface* CannotPlaceMaterial;

	UPROPERTY()
	EItemTypes PreviewItemType;

	UPROPERTY()
	FName PreviewItemID;

	bool bIsCanPlace = false;

public : //Getter & Setter 설정
	const bool GetbCanPlace() { return bIsCanPlace; }
	
};

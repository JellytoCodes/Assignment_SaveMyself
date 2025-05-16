// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSubsystem.h"
#include "Warehouse.generated.h"

class UStorageWidget;

UCLASS()
class SAVEMYSELFPROJECT_API AWarehouse : public AActor
{
	GENERATED_BODY()
	
public:	
	AWarehouse();
protected:
	virtual void BeginPlay() override;

protected :
	//â�� ���� ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Componentes")
	class UBoxComponent* BoxCollision;

	bool bIsStorageEntrance = false;

public :

	//â�� ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Storage")
	TSubclassOf<UStorageWidget> StorageWidgetClass;

	UStorageWidget* StorageWidgetInstance;

	//â�� ����
	UFUNCTION()
	void OnWarehouseEntranceOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//â�� ������
	UFUNCTION()
	void OnWarehouseExitOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//â�� ���� ���� üũ (Ű ���ε� ��Ȱ��ȭ �뵵)
	bool GetStorageEntrance() { return bIsStorageEntrance; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DataTable")
	TArray<FStorageArray> fInData;
};

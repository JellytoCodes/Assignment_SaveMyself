// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Storage")
	TSubclassOf<UStorageWidget> StorageWidgetClass;

	UStorageWidget* StorageWidgetInstance;

	bool bIsStorageEntrance = false;

public :
	UFUNCTION()
	void OnWarehouseOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//â�� ���� ���� üũ
	bool GetStorageEntrance() { return bIsStorageEntrance; }
};

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
	//창고 구역 설정
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Componentes")
	class UBoxComponent* BoxCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Storage")
	TSubclassOf<UStorageWidget> StorageWidgetClass;

	UStorageWidget* StorageWidgetInstance;

	bool bIsStorageEntrance = false;

public :
	UFUNCTION()
	void OnWarehouseOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//창고 진입 여부 체크
	bool GetStorageEntrance() { return bIsStorageEntrance; }
};

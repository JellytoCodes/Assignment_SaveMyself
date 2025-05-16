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
	//창고 구역 설정
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Componentes")
	class UBoxComponent* BoxCollision;

	bool bIsStorageEntrance = false;

public :

	//창고 위젯
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Storage")
	TSubclassOf<UStorageWidget> StorageWidgetClass;

	UStorageWidget* StorageWidgetInstance;

	//창고 들어가기
	UFUNCTION()
	void OnWarehouseEntranceOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//창고 나가기
	UFUNCTION()
	void OnWarehouseExitOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//창고 진입 여부 체크 (키 바인딩 비활성화 용도)
	bool GetStorageEntrance() { return bIsStorageEntrance; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DataTable")
	TArray<FStorageArray> fInData;
};

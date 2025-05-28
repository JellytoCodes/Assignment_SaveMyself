// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TutorialManagerWidget.generated.h"

/**
 * 
 */
UCLASS()
class SAVEMYSELFPROJECT_API UTutorialManagerWidget : public UUserWidget
{
	GENERATED_BODY()

private :
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnCloseClicked();

public :
	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonClose;
};

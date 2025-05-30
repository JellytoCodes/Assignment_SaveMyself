// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGameManagerHUD.h"
#include "EndGameManagerWidget.h"

AEndGameManagerHUD::AEndGameManagerHUD()
{
	static ConstructorHelpers::FClassFinder<UEndGameManagerWidget> EndGameWidgetBP(TEXT("/Game/WidgetBP/WBP_EndGameWidget.WBP_EndGameWidget_C"));
	if(EndGameWidgetBP.Succeeded())
	{
		EndGameWidgetClass = EndGameWidgetBP.Class;
	}
}

void AEndGameManagerHUD::BeginPlay()
{
	Super::BeginPlay();

	if(EndGameWidgetClass)
	{
		auto PC = GetOwningPlayerController();

		auto PlayerWidgetInstance = CreateWidget<UEndGameManagerWidget>(PC, EndGameWidgetClass);	
		if(!PlayerWidgetInstance) return;

		PlayerWidgetInstance->AddToViewport();
	}
}

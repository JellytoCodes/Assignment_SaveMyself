// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleManagerHUD.h"
#include "TitleManagerWidget.h"

ATitleManagerHUD::ATitleManagerHUD()
{
	static ConstructorHelpers::FClassFinder<UTitleManagerWidget> titleWidgetBP(TEXT("/Game/WidgetBP/WBP_TitleWidget.WBP_TitleWidget_C"));
	if(titleWidgetBP.Succeeded())
	{
		titleWidgetClass = titleWidgetBP.Class;
	}
}

void ATitleManagerHUD::BeginPlay()
{
	Super::BeginPlay();

	if(titleWidgetClass)
	{
		auto PC = GetOwningPlayerController();

		auto PlayerWidgetInstance = CreateWidget<UTitleManagerWidget>(PC, titleWidgetClass);	
		if(!PlayerWidgetInstance) return;

		PlayerWidgetInstance->AddToViewport();
	}
}

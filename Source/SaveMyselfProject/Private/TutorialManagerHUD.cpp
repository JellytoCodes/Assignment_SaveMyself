// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialManagerHUD.h"
#include "TutorialManagerWidget.h"

ATutorialManagerHUD::ATutorialManagerHUD()
{
	static ConstructorHelpers::FClassFinder<UTutorialManagerWidget> tutorialWidgetBP(TEXT("/Game/WidgetBP/WBP_TutorialWidget.WBP_TutorialWidget_C"));
	if(tutorialWidgetBP.Succeeded())
	{
		tutorialWidgetClass = tutorialWidgetBP.Class;
	}
}

void ATutorialManagerHUD::BeginPlay()
{
	Super::BeginPlay();

	if(tutorialWidgetClass)
	{
		auto PC = GetOwningPlayerController();

		auto PlayerWidgetInstance = CreateWidget<UTutorialManagerWidget>(PC, tutorialWidgetClass);	
		if(!PlayerWidgetInstance) return;

		PlayerWidgetInstance->AddToViewport();
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHPWidget.h"
#include "Components/Image.h"

void UPlayerHPWidget::UpdatedPlayerHPWidget(int32 index)
{
	switch(index)
	{
		case 1 :
			HP_1->SetVisibility(ESlateVisibility::Hidden);
		break;
		
		case 2 :
			HP_2->SetVisibility(ESlateVisibility::Hidden);
		break;

		case 3 :
			HP_3->SetVisibility(ESlateVisibility::Hidden);
		break;

		case 4 :
			HP_4->SetVisibility(ESlateVisibility::Hidden);
		break;

		case 5 :
			HP_5->SetVisibility(ESlateVisibility::Hidden);
		break;
	}
}

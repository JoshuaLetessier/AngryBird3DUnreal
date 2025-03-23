// Fill out your copyright notice in the Description page of Project Settings.

#include "AB3D_GameUI.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "Blueprint/WidgetTree.h"

UAB3D_GameUI::UAB3D_GameUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UAB3D_GameUI::NativeConstruct()
{
    Super::NativeConstruct();
}


void UAB3D_GameUI::SetScore(int NewScore)
{
	Score += NewScore;
	if (ScoreTextValue)
	{
		ScoreTextValue->SetText(FText::FromString(FString::FromInt(Score)));
	}
}

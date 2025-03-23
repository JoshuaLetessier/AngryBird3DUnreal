// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AB3D_GameUI.generated.h"

/**
 *
 */
UCLASS()
class ANGRYBIRDS3D_API UAB3D_GameUI : public UUserWidget
{
	GENERATED_BODY()

public:

	UAB3D_GameUI(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI", meta = (BindWidget))
	class UTextBlock* ScoreText;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI", meta = (BindWidget))
	class UTextBlock* ScoreTextValue;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI", meta = (BindWidget))
	class UCanvasPanel* Canvas;


	int Score = 0;

	void SetScore(int NewScore);
};

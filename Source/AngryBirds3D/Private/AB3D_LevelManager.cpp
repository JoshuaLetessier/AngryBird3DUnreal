// Fill out your copyright notice in the Description page of Project Settings.


#include "AB3D_LevelManager.h"
#include <Kismet/GameplayStatics.h>
#include "Enemy.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>


// Sets default values
AAB3D_LevelManager::AAB3D_LevelManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAB3D_LevelManager::BeginPlay()
{
	Super::BeginPlay();

	//Recuperer le nombre d'ennemis dans la scnenes
	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), Enemies);

	EnemiesLeft = Enemies.Num();
	ProjectilesLeft = Projectiles.Num();

}

// Called every frame
void AAB3D_LevelManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckWinCondition();
}

void AAB3D_LevelManager::CheckWinCondition()
{
	if (EnemiesLeft == 0)
	{
		OnWin();
	}
	else if (ProjectilesLeft == 0)
	{
		OnLose();
	}
}

void AAB3D_LevelManager::OnWin()
{
	//Open the UI
	//if (WinWidgetClass)
	//{
	//	UUserWidget* WinWidget = CreateWidget<UUserWidget>(GetWorld(), WinWidgetClass);
	//	if (WinWidget)
	//	{

	//		APlayerController* PC = GetWorld()->GetFirstPlayerController();
	//		if (PC)
	//		{
	//			PC->SetShowMouseCursor(true);

	//			FInputModeUIOnly InputMode;
	//			InputMode.SetWidgetToFocus(WinWidget->TakeWidget());
	//			PC->SetInputMode(InputMode);

	//			WinWidget->AddToViewport();
	//		}
	//	}
	//}

	//UGameplayStatics::OpenLevel(this, FName("StartMap"));
}

void AAB3D_LevelManager::OnLose()
{
	//Open the UI
	/*if (LoseWidgetClass)
	{
		UUserWidget* LoseWidget = CreateWidget<UUserWidget>(GetWorld(), LoseWidgetClass);
		if (LoseWidget)
		{
			LoseWidget->AddToViewport();
			APlayerController* PC = GetWorld()->GetFirstPlayerController();
			if (PC)
			{
				PC->SetShowMouseCursor(true);
				PC->SetInputMode(FInputModeUIOnly());
			}
		}
	}*/

	//UGameplayStatics::OpenLevel(this, FName("StartMap"));
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "AB3D_ScoreManager.h"
#include "EngineUtils.h"
#include "Enemy.h"
#include "AB3D_GameUI.h"
#include <Blueprint/WidgetBlueprintLibrary.h>
#include <Blueprint/UserWidget.h>
#include "Chaos/ChaosGameplayEventDispatcher.h"
#include "Kismet/GameplayStatics.h"
#include "GeometryCollection/GeometryCollectionComponent.h"




// Sets default values
AAB3D_ScoreManager::AAB3D_ScoreManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AAB3D_ScoreManager::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		//Récupérer le Widget affiché à l'écran
		TArray<UUserWidget*> FoundWidgets;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, FoundWidgets, UAB3D_GameUI::StaticClass(), false);

		if (FoundWidgets.Num() > 0)
		{
			GameUI = Cast<UAB3D_GameUI>(FoundWidgets[0]);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Impossible de récupérer le GameUI !"));
		}
	}

	UWorld* World = GetWorld();

	if (World)
	{
		// On récupère tous les ennemis de la scène
		for (TActorIterator<AEnemy> It(World); It; ++It)
		{
			AEnemy* Enemy = *It;
			if (Enemy && IsValid(Enemy))
			{
				// On bind la fonction OnEnemyDestroyed à l'événement OnDestroyed de l'ennemi
				Enemy->OnDestroyed.AddUniqueDynamic(this, &AAB3D_ScoreManager::OnEnemyDestroyed);
			}
		}
	}

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FoundActors);

	if (FoundActors.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No actors found!"));
	}

	for (AActor* Actor : FoundActors)
	{
		if (UGeometryCollectionComponent* Destructible = Actor->FindComponentByClass<UGeometryCollectionComponent>())
		{
			UE_LOG(LogTemp, Warning, TEXT("Listening to: %s"), *Actor->GetName());
			Destructible->SetNotifyBreaks(true);
			Destructible->OnChaosBreakEvent.AddDynamic(this, &AAB3D_ScoreManager::OnFracture);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No destructible found in: %s"), *Actor->GetName());
		}
	}
}

void AAB3D_ScoreManager::OnEnemyDestroyed(AActor* DestroyedActor)
{
	if (GameUI)
		GameUI->SetScore(100);

}

void AAB3D_ScoreManager::OnFracture(const FChaosBreakEvent& BreakEvent)
{
	UE_LOG(LogTemp, Warning, TEXT("Fracture detected! Analyzing event..."));

	int SmallPieces = 0;
	int MediumPieces = 0;
	int LargePieces = 0;

	if (BreakEvent.Mass < 5.0f)
	{
		SmallPieces++;
	}
	else if (BreakEvent.Mass < 20.0f)
	{
		MediumPieces++;
	}
	else
	{
		LargePieces++;
	}

	// Définir un type de fracture basé sur les morceaux cassés
	FString FractureType;
	if (LargePieces > 0)
	{
		GameUI->SetScore(LargePieces * 50);
	}
	else if (MediumPieces > SmallPieces)
	{
		GameUI->SetScore(MediumPieces * 20);
	}
	else
	{
		GameUI->SetScore(SmallPieces * 10);
	}
}


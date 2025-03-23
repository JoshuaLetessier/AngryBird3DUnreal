// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AB3D_Projectile.h"
#include "AB3D_LevelManager.generated.h"

UCLASS()
class ANGRYBIRDS3D_API AAB3D_LevelManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAB3D_LevelManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int EnemiesLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ProjectilesLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AAB3D_Projectile>> Projectiles;

	
	//Win UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> WinWidgetClass;

	//Lose UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> LoseWidgetClass;

	void CheckWinCondition();
	void OnWin();
	void OnLose();
};

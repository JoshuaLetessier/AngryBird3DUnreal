// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.h"
#include "AB3D_GameUI.h"
#include "Chaos/ChaosGameplayEventDispatcher.h"
#include <ChaosBlueprint.h>
#include "AB3D_ScoreManager.generated.h"



UCLASS()
class ANGRYBIRDS3D_API AAB3D_ScoreManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAB3D_ScoreManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	UFUNCTION()
	void OnEnemyDestroyed(AActor* DestroyedActor);
	
	UFUNCTION()
	void OnFracture(const FChaosBreakEvent& BreakEvent);

	UAB3D_GameUI* GameUI;
};
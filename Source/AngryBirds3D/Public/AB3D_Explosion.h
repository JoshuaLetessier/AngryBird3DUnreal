// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "AB3D_Explosion.generated.h"

UCLASS()
class ANGRYBIRDS3D_API AAB3D_Explosion : public AActor
{
	GENERATED_BODY()
	
public:
    AAB3D_Explosion();

protected:
    virtual void BeginPlay() override;

    // Détection de collision
    UFUNCTION()
    void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);

    // Fonction d'explosion
    void Explode();


    UPROPERTY(VisibleAnywhere, Category = "Explosion")
    USphereComponent* ExplosionSphere;

    // Collision
    UPROPERTY(VisibleAnywhere, Category = "Explosion")
    class USphereComponent* CollisionComponent;

    // Taille de l'explosion
    UPROPERTY(EditDefaultsOnly, Category = "Explosion")
    float ExplosionRadius = 300.0f;

    float ExplosionDamage = 50.0f;   // Dégâts infligés
    float ExplosionForce = 1000.0f;  // Force physique appliquée

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AB3D_Projectile.generated.h"

UCLASS(Abstract)
class ANGRYBIRDS3D_API AAB3D_Projectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAB3D_Projectile();

	virtual void LaunchProjectile(FVector LaunchDirection, float Speed);
	virtual inline void Action() {};

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere)
	float LifeTime;

	UPROPERTY(VisibleAnywhere)
	float Damage;

	bool bHasBoosted = false; // Emp�che plusieurs action

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		const FHitResult& Hit);

	UFUNCTION()
	void DestroyProjectile();


	bool isMovable = false;

private:

	FTimerHandle TimerHandle;



};
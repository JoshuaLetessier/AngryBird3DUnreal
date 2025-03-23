// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AB3D_Projectile.h"
#include "AB3D_Explosion.h"
#include "AB3D_ProjectilePumpkin.generated.h"

/**
 * 
 */
UCLASS()
class ANGRYBIRDS3D_API AAB3D_ProjectilePumpkin : public AAB3D_Projectile
{
	GENERATED_BODY()
	
	
public:
    AAB3D_ProjectilePumpkin();


    // Fonction pour larguer une bombe
    virtual void Action() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
	TSubclassOf<class AAB3D_Explosion> ExplosionClass;

};

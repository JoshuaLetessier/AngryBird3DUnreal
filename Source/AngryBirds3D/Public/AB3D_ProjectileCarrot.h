// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AB3D_Projectile.h"
#include "AB3D_ProjectileCarrot.generated.h"

/**
 * 
 */
UCLASS()
class ANGRYBIRDS3D_API AAB3D_ProjectileCarrot : public AAB3D_Projectile
{
	GENERATED_BODY()

public:
    AAB3D_ProjectileCarrot();

    // Fonction pour se diviser en 3 morceaux
    virtual void Action() override;
	
};

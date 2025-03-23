#pragma once

#include "CoreMinimal.h"
#include "AB3D_Projectile.h"
#include "AAB3D_ProjectileYellowPepper.generated.h"

UCLASS()
class ANGRYBIRDS3D_API AAB3D_ProjectileYellowPepper : public AAB3D_Projectile
{
    GENERATED_BODY()

public:
    AAB3D_ProjectileYellowPepper();

    // Fonction pour booster la vitesse en plein vol
    virtual void Action() override;

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Custom")
    float BoostMultiplier = 500.0f;
};

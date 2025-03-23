#include "AAB3D_ProjectileYellowPepper.h"
#include "GameFramework/ProjectileMovementComponent.h"


AAB3D_ProjectileYellowPepper::AAB3D_ProjectileYellowPepper()
{
}

void AAB3D_ProjectileYellowPepper::BeginPlay()
{
    Super::BeginPlay();
}

void AAB3D_ProjectileYellowPepper::Action()
{
    if (bHasBoosted || !ProjectileMesh || !isMovable) return; // �vite plusieurs boosts

    FVector BoostDirection = ProjectileMesh->GetPhysicsLinearVelocity().GetSafeNormal(); // R�cup�re la direction actuelle

    ProjectileMesh->AddImpulse(BoostDirection * BoostMultiplier, NAME_None, true); // Applique un boost en physique

    UE_LOG(LogTemp, Warning, TEXT("Boost activ� ! Nouvelle vitesse : %s"), *ProjectileMesh->GetPhysicsLinearVelocity().ToString());

    bHasBoosted = true;
}




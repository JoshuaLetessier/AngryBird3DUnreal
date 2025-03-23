
#include "AB3D_ProjectileCarrot.h"
#include "Kismet/GameplayStatics.h"

AAB3D_ProjectileCarrot::AAB3D_ProjectileCarrot()
{
}

void AAB3D_ProjectileCarrot::Action()
{
    UE_LOG(LogTemp, Warning, TEXT("Action() appelée : Duplication en cours..."));

    if (bHasBoosted || !ProjectileMesh) return;

    FVector Velocity = GetVelocity();
    if (Velocity.SizeSquared() < KINDA_SMALL_NUMBER) return;

    FVector BaseDirection = Velocity.GetSafeNormal();
    FVector LeftDirection = BaseDirection.RotateAngleAxis(-15.f, FVector::UpVector);
    FVector RightDirection = BaseDirection.RotateAngleAxis(15.f, FVector::UpVector);

    UWorld* World = GetWorld();
    if (!World) return;

    FVector SpawnLocation = GetActorLocation();
    FRotator SpawnRotation = GetActorRotation();

    AAB3D_ProjectileCarrot* LeftCarrot = World->SpawnActor<AAB3D_ProjectileCarrot>(GetClass(), SpawnLocation, SpawnRotation);
    AAB3D_ProjectileCarrot* RightCarrot = World->SpawnActor<AAB3D_ProjectileCarrot>(GetClass(), SpawnLocation, SpawnRotation);

    if (LeftCarrot && RightCarrot)
    {
        LeftCarrot->SetActorScale3D(GetActorScale3D());
        RightCarrot->SetActorScale3D(GetActorScale3D());

        float FragmentSpeed = Velocity.Size();

        // Appliquer la vitesse via SetPhysicsLinearVelocity
        if (LeftCarrot->ProjectileMesh && LeftCarrot->ProjectileMesh->IsSimulatingPhysics())
        {
            LeftCarrot->ProjectileMesh->SetPhysicsLinearVelocity(LeftDirection * FragmentSpeed);
        }

        if (RightCarrot->ProjectileMesh && RightCarrot->ProjectileMesh->IsSimulatingPhysics())
        {
            RightCarrot->ProjectileMesh->SetPhysicsLinearVelocity(RightDirection * FragmentSpeed);
        }
    }

    bHasBoosted = true;
}

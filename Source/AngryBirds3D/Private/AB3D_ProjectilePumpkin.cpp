#include "AB3D_ProjectilePumpkin.h"

AAB3D_ProjectilePumpkin::AAB3D_ProjectilePumpkin()
{
}

void AAB3D_ProjectilePumpkin::Action()
{
    if (ExplosionClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("Largage de la bombe citrouille !"));

        // Position de spawn (juste en dessous du projectile)
        FVector SpawnLocation = GetActorLocation() - FVector(0, 0, 50.0f);
        FRotator SpawnRotation = GetActorRotation();

        // Spawn de la bombe
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        AAB3D_Explosion* SpawnedBomb = GetWorld()->SpawnActor<AAB3D_Explosion>(ExplosionClass, SpawnLocation, SpawnRotation, SpawnParams);

        if (SpawnedBomb)
        {
            // Appliquer une force vers le bas pour que la bombe tombe naturellement
            UStaticMeshComponent* BombMesh = Cast<UStaticMeshComponent>(SpawnedBomb->GetComponentByClass(UStaticMeshComponent::StaticClass()));
            if (BombMesh)
            {
                BombMesh->AddImpulse(FVector(0, 0, -500.0f), NAME_None, true);
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("EXP NOT SET"));

    }
}



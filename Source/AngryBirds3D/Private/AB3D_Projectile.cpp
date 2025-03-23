// Fill out your copyright notice in the Description page of Project Settings.


#include "AB3D_Projectile.h"
#include "Enemy.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AAB3D_Projectile::AAB3D_Projectile()
{
    PrimaryActorTick.bCanEverTick = false;
    // Mesh du projectile
    ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
    RootComponent = ProjectileMesh;

    // Auto-destruction apr�s LifeTime secondes
    InitialLifeSpan = LifeTime;

    ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    ProjectileMesh->SetCollisionObjectType(ECC_PhysicsBody);

	ProjectileMesh->SetEnableGravity(false);

    ProjectileMesh->OnComponentHit.AddDynamic(this, &AAB3D_Projectile::OnHit);

}

void AAB3D_Projectile::LaunchProjectile(FVector LaunchDirection, float Speed)
{
    if (ProjectileMesh)
    {
        ProjectileMesh->SetEnableGravity(true);
        ProjectileMesh->AddImpulse(LaunchDirection * -Speed, NAME_None, true);

        isMovable = true;
    }
    GetWorldTimerManager().SetTimer(TimerHandle, this, &AAB3D_Projectile::DestroyProjectile, 15.0f, false);
}



void AAB3D_Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, FVector NormalImpulse,
    const FHitResult& Hit)
{
    if (OtherActor && OtherActor != this && OtherComp)
    {
        float ImpactForce = ProjectileMesh->GetComponentVelocity().Size();

        AEnemy* Enemy = Cast<AEnemy>(OtherActor);
        if (Enemy)
        {
            Enemy->TakeImpactForce(ImpactForce);
        }
    }

    GetWorldTimerManager().SetTimer(TimerHandle, this, &AAB3D_Projectile::DestroyProjectile, 1.0f, false);
}



void AAB3D_Projectile::DestroyProjectile()
{
    Destroy();
}




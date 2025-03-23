#include "AB3D_Explosion.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


AAB3D_Explosion::AAB3D_Explosion()
{
    PrimaryActorTick.bCanEverTick = false;
    // Mesh du projectile
    ExplosionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionSphere"));
    RootComponent = ExplosionSphere;


    ExplosionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    ExplosionSphere->SetCollisionObjectType(ECC_PhysicsBody);

    ExplosionSphere->SetEnableGravity(false);
}



void AAB3D_Explosion::BeginPlay()
{
    Super::BeginPlay();

    // Assurez-vous que la sphère de collision est bien configurée
    if (ExplosionSphere)
    {
        ExplosionSphere->OnComponentBeginOverlap.AddDynamic(this, &AAB3D_Explosion::OnOverlap);
    }
}

void AAB3D_Explosion::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this)
    {
        UE_LOG(LogTemp, Warning, TEXT(" Collision détectée ! L'explosion va être déclenchée."));
        Explode();
    }
}

void AAB3D_Explosion::Explode()
{
    UE_LOG(LogTemp, Warning, TEXT(" Explosion déclenchée !"));

    // Ajoute ici ton code d'explosion (dégâts, effets visuels, destruction, etc.)

    Destroy();
}

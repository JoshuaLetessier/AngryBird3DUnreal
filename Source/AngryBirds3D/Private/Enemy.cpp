#include "Enemy.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GeometryCollection/GeometryCollectionActor.h"
#include "Kismet/GameplayStatics.h"

AEnemy::AEnemy()
{
    PrimaryActorTick.bCanEverTick = true;

    // Activer la détection des collisions sur le Capsule Component
    GetCapsuleComponent()->SetNotifyRigidBodyCollision(true);
    GetCapsuleComponent()->SetCollisionProfileName(TEXT("PhysicsActor"));
    GetCapsuleComponent()->SetGenerateOverlapEvents(true);
    GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Block);

    GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AEnemy::OnHit);

}

void AEnemy::BeginPlay()
{
    Super::BeginPlay();

}

void AEnemy::TakeImpactForce(float ImpactForce)
{
    UE_LOG(LogTemp, Warning, TEXT("Impact reçu: %f"), ImpactForce);

    if ((ImpactForce) >= DestructionThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Ennemi détruit !"));
        Destroy();


    }
}

void AEnemy::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (!OtherActor || !OtherComp) return;

    if (OtherActor->IsA(AGeometryCollectionActor::StaticClass()))
    {
        UE_LOG(LogTemp, Warning, TEXT("Impact de débris détecté !"));

        float RawImpactForce = NormalImpulse.Size();

        // Appliquer une échelle logarithmique pour atténuer les très gros impacts
        float ScaledImpactForce = FMath::LogX(10, RawImpactForce + 1) * 100.0f;

        TakeImpactForce(ScaledImpactForce);

        UE_LOG(LogTemp, Warning, TEXT("Impact reçu (log) : %f (brut : %f)"), ScaledImpactForce, RawImpactForce);
    }
}


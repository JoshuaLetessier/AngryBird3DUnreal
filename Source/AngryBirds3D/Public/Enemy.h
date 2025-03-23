#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"


UCLASS()
class ANGRYBIRDS3D_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemy();

protected:
	virtual void BeginPlay() override;

public:
	// Fonction appel�e lorsqu'une force est appliqu�e � l'ennemi
	void TakeImpactForce(float ImpactForce);

private:

	UPROPERTY(EditAnywhere, Category = "Destruction")
	float DestructionThreshold = 50.0f; // Force minimale pour d�truire l'ennemi

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};

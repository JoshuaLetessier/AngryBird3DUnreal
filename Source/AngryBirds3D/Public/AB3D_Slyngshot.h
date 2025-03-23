// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <EnhancedInputLibrary.h>
#include "AB3D_Projectile.h"
#include <AB3D_GameUI.h>

#include "CableComponent.h"
#include <Components/SplineMeshComponent.h>
#include <Components/SplineComponent.h>
#include <DrawDebugHelpers.h>
#include "AB3D_Slyngshot.generated.h"



UCLASS()
class ANGRYBIRDS3D_API AAB3D_Slyngshot : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAB3D_Slyngshot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	class UInputMappingContext* InputMappingComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	class UInputAction* LoadAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	class UInputAction* FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	class UInputAction* AimAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	class UInputAction* Action;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	class UInputAction* NextProjectileAction;

	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	float LoadPower = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	float MaxLoadPower = 10;


	//Camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TArray<TSubclassOf<AAB3D_Projectile>> ProjectileClasses;

	int CurrentProjectileIndex = 0;

	UPROPERTY(EditAnywhere, Category = "Sling")
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(VisibleAnywhere, Category = "Sling")
	AAB3D_Projectile* CurrentProjectile;

	//Slingshot root
	UPROPERTY(VisibleAnywhere, Category = "Sling")
	USceneComponent* SlyngshotRoot;



protected:

	void OnLoad(const FInputActionValue& Value);
	void OnFire(const FInputActionValue& Value);
	void OnAim(const FInputActionValue& Value);
	void ActivateAction();
	void OnNextProjectile();

private:
	void DrawProjectileTrajectory();

	void UpdateSplineMeshes();


protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> HUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	UAB3D_GameUI* HUDWidget;
   

	UPROPERTY(VisibleAnywhere, Category = "Sling")
	USplineComponent* SplineComponent;

	UPROPERTY(EditAnywhere, Category = "Sling")
	UStaticMesh* SplineMesh;

	UPROPERTY(VisibleAnywhere, Category = "Sling")
	TArray<USplineMeshComponent*> SplineMeshes;


public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slingshot")
	UCableComponent* LeftCable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slingshot")
	UCableComponent* RightCable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slingshot")
	USceneComponent* CenterAttachPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slingshot")
	USceneComponent* LeftAttachPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slingshot")
	USceneComponent* RightAttachPoint;

};

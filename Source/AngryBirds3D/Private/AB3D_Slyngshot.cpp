// Fill out your copyright notice in the Description page of Project Settings.

#include "AB3D_Slyngshot.h"
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include "Camera/CameraComponent.h"
#include <Kismet/GameplayStaticsTypes.h>
#include <Kismet/GameplayStatics.h>
#include <LandscapeSplineSegment.h>



// Sets default values
AAB3D_Slyngshot::AAB3D_Slyngshot()
{
    PrimaryActorTick.bCanEverTick = true;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(RootComponent);

    SlyngshotRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SlyngshotRoot"));
    SlyngshotRoot->SetupAttachment(RootComponent);


    ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
    ProjectileSpawnPoint->SetupAttachment(SlyngshotRoot);

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
    SplineComponent->SetupAttachment(SlyngshotRoot);


    // Point central où les câbles sont attachés (suivra le projectile)
    CenterAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("CenterAttachPoint"));
    CenterAttachPoint->SetupAttachment(SlyngshotRoot);

    // Point d'attache gauche
    LeftAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("LeftAttachPoint"));
    LeftAttachPoint->SetupAttachment(SlyngshotRoot);

    // Point d'attache droit
    RightAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("RightAttachPoint"));
    RightAttachPoint->SetupAttachment(SlyngshotRoot);


	// Créer les câbles
    LeftCable = CreateDefaultSubobject<UCableComponent>(TEXT("LeftCable"));
    LeftCable->SetupAttachment(LeftAttachPoint);

    RightCable = CreateDefaultSubobject<UCableComponent>(TEXT("RightCable"));
    RightCable->SetupAttachment(RightAttachPoint);

}

// Called when the game starts or when spawned
void AAB3D_Slyngshot::BeginPlay()
{
    Super::BeginPlay();

	//Get the LevelManager in the scene
	//SetTimer if the level manager is not found

	// V�rifier si le PlayerController est valide
    APlayerController* PC = Cast<APlayerController>(GetController());
    if (PC)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController found"));

        // V�rifier et ajouter le Input Mapping Context
        UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
        if (Subsystem)
        {
            UE_LOG(LogTemp, Warning, TEXT("Adding IMC_Slingshot to Input System"));
            Subsystem->AddMappingContext(InputMappingComponent, 0);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("EnhancedInputLocalPlayerSubsystem not found!"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("PlayerController is NULL!"));
    }

    //UI
    if (HUDWidgetClass)
    {
        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (PlayerController)
        {
            HUDWidget = CreateWidget<UAB3D_GameUI>(PlayerController, HUDWidgetClass);
            if (HUDWidget)
            {
                HUDWidget->AddToViewport();
            }
        }
    }
}


// Called every frame
void AAB3D_Slyngshot::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //DrawElastic();
    DrawProjectileTrajectory();
}

// Called to bind functionality to input
void AAB3D_Slyngshot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    UE_LOG(LogTemp, Warning, TEXT("SetupPlayerInputComponent"));

    UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

    // V�rification pour �viter un crash si le cast �choue
    if (!Input) return;

    // Bind les actions
    Input->BindAction(LoadAction, ETriggerEvent::Triggered, this, &AAB3D_Slyngshot::OnLoad);
    Input->BindAction(FireAction, ETriggerEvent::Triggered, this, &AAB3D_Slyngshot::OnFire);
    Input->BindAction(AimAction, ETriggerEvent::Triggered, this, &AAB3D_Slyngshot::OnAim);
    Input->BindAction(NextProjectileAction, ETriggerEvent::Triggered, this, &AAB3D_Slyngshot::OnNextProjectile);
    Input->BindAction(Action, ETriggerEvent::Triggered, this, &AAB3D_Slyngshot::ActivateAction);
}

void AAB3D_Slyngshot::OnLoad(const FInputActionValue& Value)
{
    float InputStrength = Value.Get<float>();
    float NewLoadPower = FMath::Lerp(0.f, MaxLoadPower, InputStrength);

    // V�rifie si la valeur de charge a chang� avant de recalculer la trajectoire
    if (FMath::Abs(NewLoadPower - LoadPower) > KINDA_SMALL_NUMBER)
    {
        LoadPower = NewLoadPower;
    }
}

void AAB3D_Slyngshot::OnFire(const FInputActionValue& Value)
{
    if (LoadPower == 0) return;

    FVector LaunchDirection = SlyngshotRoot->GetForwardVector();

    // Lancer directement le projectile 
    //LOG LoadPower


    if (ProjectileClasses.Num() > 0)
    {
        CurrentProjectile = GetWorld()->SpawnActor<AAB3D_Projectile>(
            ProjectileClasses[0],
            ProjectileSpawnPoint->GetComponentTransform()
        );

        CurrentProjectile->LaunchProjectile(LaunchDirection, LoadPower);

        LoadPower = 0.f; // Reset la charge
        ProjectileClasses.RemoveAt(CurrentProjectileIndex);
    }
}

void AAB3D_Slyngshot::OnAim(const FInputActionValue& Value)
{
    FVector2D Input = Value.Get<FVector2D>();

    if (!SlyngshotRoot) return;

    FRotator CurrentRotation = SlyngshotRoot->GetRelativeRotation();
    float NewPitch = FMath::Clamp(CurrentRotation.Pitch + GetWorld()->GetFirstPlayerController()->GetInputAnalogKeyState(EKeys::Gamepad_LeftY) , -30.f, 30.f);
    float NewYaw = FMath::Clamp(CurrentRotation.Yaw + Input.X, -60.f, 60.f);

    SlyngshotRoot->SetRelativeRotation(FRotator(NewPitch, NewYaw, 0));
}

void AAB3D_Slyngshot::ActivateAction()
{
    if (CurrentProjectile)
    {
        CurrentProjectile->Action();
    }
}

void AAB3D_Slyngshot::OnNextProjectile()
{
    if (ProjectileClasses.Num() == 0) return;

    CurrentProjectileIndex = (CurrentProjectileIndex + 1) % ProjectileClasses.Num();
}

void AAB3D_Slyngshot::DrawProjectileTrajectory()
{
    if (LoadPower < 1) return;

    FVector SimulatedVelocity = -SlyngshotRoot->GetForwardVector() * LoadPower;

    FPredictProjectilePathParams Params;
    Params.StartLocation = ProjectileSpawnPoint->GetComponentLocation();
    Params.LaunchVelocity = SimulatedVelocity;
    Params.bTraceWithCollision = true;
    Params.ProjectileRadius = 10.f;
    Params.MaxSimTime = 2.f;
    Params.bTraceWithChannel = true;
    Params.TraceChannel = ECollisionChannel::ECC_Visibility;
    Params.ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery1);
    Params.ActorsToIgnore.Add(CurrentProjectile);
    Params.SimFrequency = 20.f;
    Params.OverrideGravityZ = 0.f;
    Params.bTraceComplex = false;

    FPredictProjectilePathResult Result;
    bool bSuccess = UGameplayStatics::PredictProjectilePath(this, Params, Result);

    if (!bSuccess || Result.PathData.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Échec de la prédiction de trajectoire ou aucun point généré."));
        return;
    }

    if (!SplineComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("SplineComponent est NULL !"));
        return;
    }

    SplineComponent->ClearSplinePoints(true);
    SplineComponent->UpdateSpline();

    for (const FPredictProjectilePathPointData& Point : Result.PathData)
    {
        SplineComponent->AddSplinePoint(Point.Location, ESplineCoordinateSpace::World);
    }

    SplineComponent->UpdateSpline();

    UpdateSplineMeshes();
}

void AAB3D_Slyngshot::UpdateSplineMeshes()
{
    if (!SplineComponent || !SplineMesh)
    {
        UE_LOG(LogTemp, Error, TEXT("SplineComponent ou SplineMesh est NULL !"));
        return;
    }

    int32 NeededMeshCount = SplineComponent->GetNumberOfSplinePoints() - 1;

    for (USplineMeshComponent* Mesh : SplineMeshes)
    {
        if (Mesh)
        {
            Mesh->DestroyComponent();
        }
    }
    SplineMeshes.Empty();

    for (int i = 0; i < NeededMeshCount; i++)
    {
        USplineMeshComponent* NewMesh = NewObject<USplineMeshComponent>(this);
        if (!NewMesh) continue;

        NewMesh->AttachToComponent(SplineComponent, FAttachmentTransformRules::KeepRelativeTransform);
        NewMesh->SetMobility(EComponentMobility::Movable);
        NewMesh->SetStaticMesh(SplineMesh);
        NewMesh->RegisterComponent();
        NewMesh->SetForwardAxis(ESplineMeshAxis::X);

        SplineMeshes.Add(NewMesh);
    }

    // Mettre à jour chaque SplineMeshComponent
    for (int i = 0; i < NeededMeshCount; i++)
    {
        FVector StartPos = SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
        FVector EndPos = SplineComponent->GetLocationAtSplinePoint(i + 1, ESplineCoordinateSpace::World);
        FVector StartTangent = SplineComponent->GetTangentAtSplinePoint(i, ESplineCoordinateSpace::World);
        FVector EndTangent = SplineComponent->GetTangentAtSplinePoint(i + 1, ESplineCoordinateSpace::World);

        if (SplineMeshes[i])
        {
            SplineMeshes[i]->SetStartAndEnd(StartPos, StartTangent, EndPos, EndTangent);
        }
    }
}
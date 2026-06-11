// Copyright Epic Games, Inc. All Rights Reserved.

#include "Train/TrainController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Sound/SoundBase.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/AudioComponent.h"

ATrainController::ATrainController()
{
    PrimaryActorTick.TickInterval = 0.016f; // 60 FPS

    // 禁用默認 Pawn 移動
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // 創建碰撞盒
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    CollisionBox->SetCollisionEnabled(ECC_WorldDynamic);
    RootComponent = CollisionBox;

    // 創建網格組件
    TrainMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TrainMesh"));
    TrainMesh->SetupAttachment(RootComponent);

    // 創建音頻組件
    AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
    AudioComponent->SetupAttachment(RootComponent);
}

void ATrainController::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("Train Controller Started"));
    StartMovement();
}

void ATrainController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsMoving && CurrentSpeed < MaxSpeed)
    {
        CurrentSpeed += Acceleration * DeltaTime;
        CurrentSpeed = FMath::Min(CurrentSpeed, MaxSpeed);
    }

    // 更新位置
    FVector NewLocation = GetActorLocation();
    NewLocation.X += (CurrentSpeed / 3.6f) * DeltaTime; // 轉換 km/h 到 m/s
    SetActorLocation(NewLocation);

    UpdateCrowdingLevel();
}

void ATrainController::StartMovement()
{
    bIsMoving = true;
    PlaySound(AccelerationSound);
    UE_LOG(LogTemp, Warning, TEXT("Train Starting Movement"));
}

void ATrainController::StopMovement()
{
    bIsMoving = false;
    CurrentSpeed = 0.0f;
    PlaySound(BrakingSound);
    UE_LOG(LogTemp, Warning, TEXT("Train Stopping"));
}

void ATrainController::OpenDoors()
{
    if (!bDoorsOpen)
    {
        bDoorsOpen = true;
        PlaySound(DoorOpenSound);
        SimulatePassengerExchange();
        UE_LOG(LogTemp, Warning, TEXT("Doors Opened"));
    }
}

void ATrainController::CloseDoors()
{
    if (bDoorsOpen)
    {
        bDoorsOpen = false;
        PlaySound(DoorCloseSound);
        UE_LOG(LogTemp, Warning, TEXT("Doors Closed"));
    }
}

void ATrainController::SimulatePassengerExchange()
{
    int32 Boarding = FMath::RandRange(10, 50);
    int32 Alighting = FMath::RandRange(5, CurrentPassengers / 2);

    CurrentPassengers -= Alighting;
    CurrentPassengers += Boarding;
    CurrentPassengers = FMath::Clamp(CurrentPassengers, 0, MaxCapacity);

    UE_LOG(LogTemp, Warning, TEXT("Passengers - Alighting: %d, Boarding: %d, Total: %d"),
        Alighting, Boarding, CurrentPassengers);
}

void ATrainController::UpdateCrowdingLevel()
{
    CrowdingLevel = static_cast<float>(CurrentPassengers) / static_cast<float>(MaxCapacity);
}

FString ATrainController::GetCrowdingDescription() const
{
    if (CrowdingLevel < 0.3f) return TEXT("空車");
    if (CrowdingLevel < 0.7f) return TEXT("正常");
    return TEXT("滿員");
}

void ATrainController::PlaySound(USoundBase* Sound)
{
    if (AudioComponent && Sound)
    {
        AudioComponent->PlaySound2D(Sound);
    }
}

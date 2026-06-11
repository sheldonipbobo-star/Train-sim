// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TrainController.generated.h"

/**
 * 列車控制器 (Train Controller)
 * 管理列車的物理運動、速度、加速度和車站停靠
 */
UCLASS()
class TRAINSIM_API ATrainController : public APawn
{
    GENERATED_BODY()

public:
    ATrainController();

    // ===== 列車參數 =====
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Train|Physics")
    float MaxSpeed = 80.0f; // km/h

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Train|Physics")
    float Acceleration = 1.5f; // m/s²

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Train|Physics")
    float Deceleration = 2.0f; // m/s²

    UPROPERTY(BlueprintReadOnly, Category = "Train|State")
    float CurrentSpeed = 0.0f; // km/h

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Train|Station")
    float StopDuration = 15.0f; // 停靠時間（秒）

    // ===== 乘客系統 =====
    UPROPERTY(BlueprintReadOnly, Category = "Train|Passenger")
    int32 CurrentPassengers = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Train|Passenger")
    int32 MaxCapacity = 200;

    UPROPERTY(BlueprintReadOnly, Category = "Train|Passenger")
    float CrowdingLevel = 0.0f; // 0-1 擁擠度

    // ===== 門系統 =====
    UPROPERTY(BlueprintReadOnly, Category = "Train|Door")
    bool bDoorsOpen = false;

    // ===== 聲音系統 =====
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Train|Audio")
    class USoundBase* AccelerationSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Train|Audio")
    class USoundBase* BrakingSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Train|Audio")
    class USoundBase* DoorOpenSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Train|Audio")
    class USoundBase* DoorCloseSound;

    // ===== 組件 =====
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class USkeletalMeshComponent* TrainMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UBoxComponent* CollisionBox;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UAudioComponent* AudioComponent;

public:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    // ===== 列車控制函數 =====
    UFUNCTION(BlueprintCallable, Category = "Train|Control")
    void StartMovement();

    UFUNCTION(BlueprintCallable, Category = "Train|Control")
    void StopMovement();

    UFUNCTION(BlueprintCallable, Category = "Train|Control")
    void OpenDoors();

    UFUNCTION(BlueprintCallable, Category = "Train|Control")
    void CloseDoors();

    // ===== 乘客管理 =====
    UFUNCTION(BlueprintCallable, Category = "Train|Passenger")
    void SimulatePassengerExchange();

    UFUNCTION(BlueprintCallable, Category = "Train|Passenger")
    float GetCrowdingLevel() const { return CrowdingLevel; }

    UFUNCTION(BlueprintCallable, Category = "Train|Passenger")
    FString GetCrowdingDescription() const;

    // ===== 查詢函數 =====
    UFUNCTION(BlueprintCallable, Category = "Train|Query")
    float GetCurrentSpeed() const { return CurrentSpeed; }

    UFUNCTION(BlueprintCallable, Category = "Train|Query")
    int32 GetCurrentPassengers() const { return CurrentPassengers; }

    UFUNCTION(BlueprintCallable, Category = "Train|Query")
    bool AreDoorsOpen() const { return bDoorsOpen; }

protected:
    void UpdateCrowdingLevel();
    void PlaySound(USoundBase* Sound);

    float ElapsedTime = 0.0f;
    bool bIsMoving = false;
};

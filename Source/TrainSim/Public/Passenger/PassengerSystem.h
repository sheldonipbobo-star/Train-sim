// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PassengerSystem.generated.h"

/**
 * 乘客行為結構
 */
USTRUCT(BlueprintType)
struct FPassengerBehavior
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString BehaviorType; // "Standing", "Sitting", "Phone", "Sleeping"

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Frequency; // 出現頻率

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Count; // 執行此行為的乘客數
};

/**
 * 乘客系統 (Passenger System)
 * 模擬動態乘客行為和擁擠度
 */
UCLASS()
class TRAINSIM_API APassengerSystem : public AActor
{
    GENERATED_BODY()

public:
    APassengerSystem();

    // ===== 乘客參數 =====
    UPROPERTY(BlueprintReadOnly, Category = "Passenger")
    int32 CurrentPassengers = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Passenger")
    int32 MaxCapacity = 200;

    UPROPERTY(BlueprintReadOnly, Category = "Passenger")
    float CrowdingLevel = 0.0f; // 0-1

    // ===== 時間設置 =====
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Passenger|Time")
    float PeakHourStartMorning = 7.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Passenger|Time")
    float PeakHourEndMorning = 9.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Passenger|Time")
    float PeakHourStartEvening = 17.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Passenger|Time")
    float PeakHourEndEvening = 19.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Passenger|Time")
    float OffPeakHourStart = 14.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Passenger|Time")
    float OffPeakHourEnd = 16.0f;

    // ===== 乘客行為 =====
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Passenger|Behavior")
    TArray<FPassengerBehavior> PassengerBehaviors;

public:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    // ===== 乘客管理函數 =====
    UFUNCTION(BlueprintCallable, Category = "Passenger|Management")
    void InitializePassengers(float TimeOfDay);

    UFUNCTION(BlueprintCallable, Category = "Passenger|Management")
    void HandlePassengerExchange(float BoardingRate, float AlightingRate);

    // ===== 查詢函數 =====
    UFUNCTION(BlueprintCallable, Category = "Passenger|Query")
    float GetCrowdingLevel() const { return CrowdingLevel; }

    UFUNCTION(BlueprintCallable, Category = "Passenger|Query")
    int32 GetCurrentPassengers() const { return CurrentPassengers; }

    UFUNCTION(BlueprintCallable, Category = "Passenger|Query")
    FString GetCrowdingDescription() const;

protected:
    void UpdateCrowdingLevel();
    int32 GetRandomPassengerCount(float TimeOfDay) const;
    bool IsInPeakHour(float TimeOfDay) const;
    bool IsInOffPeakHour(float TimeOfDay) const;

    float CurrentTimeOfDay = 8.0f;
};

// Copyright Epic Games, Inc. All Rights Reserved.

#include "Passenger/PassengerSystem.h"

APassengerSystem::APassengerSystem()
{
    PrimaryActorTick.TickInterval = 1.0f; // 更新頻率 1 秒
}

void APassengerSystem::BeginPlay()
{
    Super::BeginPlay();
    InitializePassengers(CurrentTimeOfDay);
}

void APassengerSystem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    UpdateCrowdingLevel();
}

void APassengerSystem::InitializePassengers(float TimeOfDay)
{
    CurrentPassengers = GetRandomPassengerCount(TimeOfDay);
    UpdateCrowdingLevel();
    UE_LOG(LogTemp, Warning, TEXT("Passengers Initialized: %d"), CurrentPassengers);
}

void APassengerSystem::HandlePassengerExchange(float BoardingRate, float AlightingRate)
{
    int32 Alighting = FMath::RoundToInt(CurrentPassengers * AlightingRate);
    int32 Boarding = FMath::RoundToInt((MaxCapacity - CurrentPassengers) * BoardingRate);

    CurrentPassengers -= Alighting;
    CurrentPassengers += Boarding;
    CurrentPassengers = FMath::Clamp(CurrentPassengers, 0, MaxCapacity);

    UE_LOG(LogTemp, Warning, TEXT("Passenger Exchange - Alighting: %d, Boarding: %d, Total: %d"),
        Alighting, Boarding, CurrentPassengers);
}

int32 APassengerSystem::GetRandomPassengerCount(float TimeOfDay) const
{
    int32 BasePassengers = MaxCapacity / 2;

    if (IsInPeakHour(TimeOfDay))
    {
        return FMath::RoundToInt(BasePassengers * FMath::RandRange(1.5f, 2.0f));
    }
    else if (IsInOffPeakHour(TimeOfDay))
    {
        return FMath::RoundToInt(BasePassengers * FMath::RandRange(0.3f, 0.5f));
    }
    else
    {
        return BasePassengers + FMath::RandRange(-20, 20);
    }
}

bool APassengerSystem::IsInPeakHour(float TimeOfDay) const
{
    return (TimeOfDay >= PeakHourStartMorning && TimeOfDay <= PeakHourEndMorning) ||
           (TimeOfDay >= PeakHourStartEvening && TimeOfDay <= PeakHourEndEvening);
}

bool APassengerSystem::IsInOffPeakHour(float TimeOfDay) const
{
    return TimeOfDay >= OffPeakHourStart && TimeOfDay <= OffPeakHourEnd;
}

void APassengerSystem::UpdateCrowdingLevel()
{
    CrowdingLevel = static_cast<float>(CurrentPassengers) / static_cast<float>(MaxCapacity);
}

FString APassengerSystem::GetCrowdingDescription() const
{
    if (CrowdingLevel < 0.3f) return TEXT("空車");
    if (CrowdingLevel < 0.7f) return TEXT("正常");
    return TEXT("滿員");
}

// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StationManager.generated.h"

/**
 * 車站數據結構
 */
USTRUCT(BlueprintType)
struct FStationData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Id;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Name; // 中文名稱

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString NameEn; // 英文名稱

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString NameJa; // 日文名稱

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Order; // 順序

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Latitude;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Longitude;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString PlatformType; // "terminal", "major", "standard"

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> Connections; // 連接線路
};

/**
 * 車站管理器 (Station Manager)
 * 管理所有 29 個山手線車站的信息
 */
UCLASS()
class TRAINSIM_API AStationManager : public AActor
{
    GENERATED_BODY()

public:
    AStationManager();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Station")
    TArray<FStationData> Stations;

    UPROPERTY(BlueprintReadOnly, Category = "Station")
    int32 CurrentStationIndex = 0;

    UPROPERTY(BlueprintReadOnly, Category = "Station")
    int32 TotalStations = 29;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Station")
    float CircleTimeMinutes = 60.0f;

public:
    virtual void BeginPlay() override;

    // ===== 車站查詢函數 =====
    UFUNCTION(BlueprintCallable, Category = "Station|Query")
    FStationData GetStation(int32 Index) const;

    UFUNCTION(BlueprintCallable, Category = "Station|Query")
    FStationData GetStationByName(const FString& StationName) const;

    UFUNCTION(BlueprintCallable, Category = "Station|Query")
    int32 GetStationCount() const { return Stations.Num(); }

    UFUNCTION(BlueprintCallable, Category = "Station|Query")
    FVector GetStationPosition(int32 Index) const;

    // ===== 車站管理函數 =====
    UFUNCTION(BlueprintCallable, Category = "Station|Management")
    void InitializeStations();

    UFUNCTION(BlueprintCallable, Category = "Station|Management")
    void LoadStationsFromJSON(const FString& JsonFilePath);

protected:
    void SetupDefaultStations();
};

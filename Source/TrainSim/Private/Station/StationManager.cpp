// Copyright Epic Games, Inc. All Rights Reserved.

#include "Station/StationManager.h"
#include "JsonUtilities.h"

AStationManager::AStationManager()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AStationManager::BeginPlay()
{
    Super::BeginPlay();
    InitializeStations();
}

void AStationManager::InitializeStations()
{
    if (Stations.Num() == 0)
    {
        SetupDefaultStations();
    }
    UE_LOG(LogTemp, Warning, TEXT("Initialized %d Stations"), Stations.Num());
}

FStationData AStationManager::GetStation(int32 Index) const
{
    if (Index < 0 || Index >= Stations.Num())
    {
        FStationData EmptyStation;
        return EmptyStation;
    }
    return Stations[Index % Stations.Num()];
}

FStationData AStationManager::GetStationByName(const FString& StationName) const
{
    for (const FStationData& Station : Stations)
    {
        if (Station.Name == StationName || Station.NameEn == StationName)
        {
            return Station;
        }
    }
    FStationData EmptyStation;
    return EmptyStation;
}

FVector AStationManager::GetStationPosition(int32 Index) const
{
    FStationData Station = GetStation(Index);
    // 將經緯度轉換為遊戲坐標
    return FVector(Station.Longitude * 1000.0f, 0.0f, Station.Latitude * 1000.0f);
}

void AStationManager::SetupDefaultStations()
{
    // 山手線 29 個車站
    Stations = {
        {1, TEXT("東京"), TEXT("Tokyo"), TEXT("東京"), 1, 35.6762f, 139.7674f, TEXT("terminal"), {TEXT("Marunouchi"), TEXT("Chiyoda")}},
        {2, TEXT("有樂町"), TEXT("Yurakucho"), TEXT("有楽町"), 2, 35.6756f, 139.7635f, TEXT("standard"), {TEXT("Chiyoda"), TEXT("Hibiya")}},
        {3, TEXT("新橋"), TEXT("Shimbashi"), TEXT("新橋"), 3, 35.6654f, 139.7587f, TEXT("standard"), {TEXT("Ginza"), TEXT("Asakusa")}},
        {4, TEXT("濱松町"), TEXT("Hamamatsucho"), TEXT("浜松町"), 4, 35.6552f, 139.7572f, TEXT("standard"), {TEXT("Oedo")}},
        {5, TEXT("田町"), TEXT("Tamachi"), TEXT("田町"), 5, 35.6454f, 139.7476f, TEXT("standard"), {TEXT("Oedo")}},
        {6, TEXT("品川"), TEXT("Shinagawa"), TEXT("品川"), 6, 35.6283f, 139.7397f, TEXT("major"), {TEXT("Keihin"), TEXT("Yokosuka")}},
        {7, TEXT("大崎"), TEXT("Osaki"), TEXT("大崎"), 7, 35.6197f, 139.7280f, TEXT("major"), {TEXT("Saikyo"), TEXT("Rinkai")}},
        {8, TEXT("五反田"), TEXT("Gotanda"), TEXT("五反田"), 8, 35.6249f, 139.7220f, TEXT("standard"), {TEXT("Asakusa")}},
        {9, TEXT("目黑"), TEXT("Meguro"), TEXT("目黒"), 9, 35.6334f, 139.7159f, TEXT("standard"), {TEXT("Meguro"), TEXT("Namboku")}},
        {10, TEXT("惠比壽"), TEXT("Ebisu"), TEXT("恵比寿"), 10, 35.6454f, 139.7108f, TEXT("major"), {TEXT("Hibiya")}},
        {11, TEXT("澀谷"), TEXT("Shibuya"), TEXT("渋谷"), 11, 35.6595f, 139.7004f, TEXT("major"), {TEXT("Ginza"), TEXT("Hanzomon")}},
        {12, TEXT("原宿"), TEXT("Harajuku"), TEXT("原宿"), 12, 35.6714f, 139.7027f, TEXT("major"), {}},
        {13, TEXT("新宿"), TEXT("Shinjuku"), TEXT("新宿"), 13, 35.6895f, 139.7006f, TEXT("major"), {TEXT("Marunouchi"), TEXT("Shinjuku")}},
        {14, TEXT("新大久保"), TEXT("Shin-Okubo"), TEXT("新大久保"), 14, 35.7008f, 139.7036f, TEXT("standard"), {}},
        {15, TEXT("高田馬場"), TEXT("Takadanobaba"), TEXT("高田馬場"), 15, 35.7125f, 139.7020f, TEXT("major"), {TEXT("Toden")}},
        {16, TEXT("目白"), TEXT("Mejiro"), TEXT("目白"), 16, 35.7243f, 139.6969f, TEXT("standard"), {}},
        {17, TEXT("池袋"), TEXT("Ikebukuro"), TEXT("池袋"), 17, 35.7307f, 139.7101f, TEXT("major"), {TEXT("Marunouchi"), TEXT("Seibu")}},
        {18, TEXT("雜司谷"), TEXT("Zoshigaya"), TEXT("雑司ヶ谷"), 18, 35.7245f, 139.7231f, TEXT("standard"), {}},
        {19, TEXT("鶯谷"), TEXT("Uguisudani"), TEXT("鶯谷"), 19, 35.7169f, 139.7524f, TEXT("standard"), {}},
        {20, TEXT("上野"), TEXT("Ueno"), TEXT("上野"), 20, 35.7146f, 139.7749f, TEXT("major"), {TEXT("Ginza"), TEXT("Hibiya")}},
        {21, TEXT("御徒町"), TEXT("Okachimachi"), TEXT("御徒町"), 21, 35.7076f, 139.7746f, TEXT("standard"), {TEXT("Oedo")}},
        {22, TEXT("秋葉原"), TEXT("Akihabara"), TEXT("秋葉原"), 22, 35.6981f, 139.7711f, TEXT("major"), {TEXT("Chiyoda"), TEXT("Sobu")}},
        {23, TEXT("神田"), TEXT("Kanda"), TEXT("神田"), 23, 35.6910f, 139.7712f, TEXT("standard"), {TEXT("Asakusa")}},
        {24, TEXT("東京"), TEXT("Tokyo"), TEXT("東京"), 24, 35.6762f, 139.7674f, TEXT("terminal"), {TEXT("Marunouchi")}},
        {25, TEXT("日本橋"), TEXT("Nihombashi"), TEXT("日本橋"), 25, 35.6683f, 139.7739f, TEXT("standard"), {TEXT("Ginza"), TEXT("Asakusa")}},
        {26, TEXT("京橋"), TEXT("Kyobashi"), TEXT("京橋"), 26, 35.6713f, 139.7718f, TEXT("standard"), {TEXT("Ginza")}},
        {27, TEXT("銀座"), TEXT("Ginza"), TEXT("銀座"), 27, 35.6728f, 139.7690f, TEXT("major"), {TEXT("Ginza"), TEXT("Hibiya")}},
        {28, TEXT("有樂町"), TEXT("Yurakucho"), TEXT("有楽町"), 28, 35.6756f, 139.7635f, TEXT("standard"), {TEXT("Chiyoda")}},
        {29, TEXT("東京"), TEXT("Tokyo"), TEXT("東京"), 29, 35.6762f, 139.7674f, TEXT("terminal"), {TEXT("Marunouchi")}}
    };
}

void AStationManager::LoadStationsFromJSON(const FString& JsonFilePath)
{
    // TODO: 實現 JSON 加載功能
    UE_LOG(LogTemp, Warning, TEXT("Loading stations from JSON: %s"), *JsonFilePath);
}

using UnityEngine;
using System.Collections.Generic;

public class StationManager : MonoBehaviour
{
    [SerializeField] private List<Station> stations = new List<Station>();
    [SerializeField] private TextAsset stationDataJSON;
    
    private void Start()
    {
        LoadStationsFromJSON();
    }

    private void LoadStationsFromJSON()
    {
        // 從 JSON 文件加載車站數據
        if (stationDataJSON != null)
        {
            var stationData = JsonUtility.FromJson<StationDataWrapper>(stationDataJSON.text);
            foreach (var data in stationData.stations)
            {
                Station station = CreateStation(data);
                stations.Add(station);
            }
        }
    }

    private Station CreateStation(StationData data)
    {
        Station station = new Station
        {
            Id = data.id,
            Name = data.name,
            NameEn = data.nameEn,
            NameJa = data.nameJa,
            Order = data.order,
            Latitude = data.latitude,
            Longitude = data.longitude,
            PlatformType = data.platformType,
            Connections = data.connections
        };
        return station;
    }

    public Station GetStation(int index)
    {
        if (index < 0 || index >= stations.Count)
            return null;
        return stations[index % stations.Count];
    }

    public int GetStationCount() => stations.Count;

    public Station GetStationByName(string name)
    {
        return stations.Find(s => s.Name == name || s.NameEn == name);
    }
}

[System.Serializable]
public class Station
{
    public int Id;
    public string Name;
    public string NameEn;
    public string NameJa;
    public int Order;
    public float Latitude;
    public float Longitude;
    public string PlatformType;
    public List<string> Connections;

    public Vector3 GetPosition()
    {
        // 將經緯度轉換為遊戲坐標
        return new Vector3(Longitude * 1000f, 0f, Latitude * 1000f);
    }
}

[System.Serializable]
public class StationData
{
    public int id;
    public string name;
    public string nameEn;
    public string nameJa;
    public int order;
    public float latitude;
    public float longitude;
    public string platformType;
    public List<string> connections;
}

[System.Serializable]
public class StationDataWrapper
{
    public string line;
    public int totalStations;
    public int circleTimeMinutes;
    public List<StationData> stations;
}

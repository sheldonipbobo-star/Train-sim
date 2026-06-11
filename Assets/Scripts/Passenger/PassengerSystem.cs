using UnityEngine;
using System.Collections.Generic;

public class PassengerSystem : MonoBehaviour
{
    [Header("乘客參數")]
    [SerializeField] private int maxCapacity = 200;
    [SerializeField] private int currentPassengers = 0;
    [SerializeField] private float crowdingLevel = 0f;
    
    [Header("時間設置")]
    [SerializeField] private float peakHourStart = 7f; // 早上7點
    [SerializeField] private float peakHourEnd = 9f; // 早上9點
    [SerializeField] private float offPeakHourStart = 14f; // 下午2點
    [SerializeField] private float offPeakHourEnd = 16f; // 下午4點
    
    [Header("乘客行為")]
    [SerializeField] private List<PassengerBehavior> passengerBehaviors = new List<PassengerBehavior>();
    
    private float currentTimeOfDay = 8f;
    private System.Random random = new System.Random();

    private void Start()
    {
        InitializePassengers();
    }

    private void Update()
    {
        UpdateTimeOfDay();
        UpdatePassengerBehavior();
    }

    private void InitializePassengers()
    {
        // 根據時間初始化乘客
        currentPassengers = GetRandomPassengerCount(currentTimeOfDay);
    }

    private void UpdateTimeOfDay()
    {
        // 模擬時間推進
        currentTimeOfDay += Time.deltaTime / 60f; // 1秒遊戲時間 = 1分鐘真實時間
        if (currentTimeOfDay >= 24f)
            currentTimeOfDay = 0f;
    }

    private void UpdatePassengerBehavior()
    {
        // 根據擁擠程度更新乘客行為
        crowdingLevel = (float)currentPassengers / maxCapacity;
    }

    public void HandlePassengerExchange(float boardingRate, float alightingRate)
    {
        // 計算上下車乘客
        int alighting = Mathf.RoundToInt(currentPassengers * alightingRate);
        int boarding = Mathf.RoundToInt((maxCapacity - currentPassengers) * boardingRate);
        
        currentPassengers -= alighting;
        currentPassengers += boarding;
        currentPassengers = Mathf.Clamp(currentPassengers, 0, maxCapacity);
    }

    private int GetRandomPassengerCount(float timeOfDay)
    {
        // 根據時間計算乘客數
        int basePassengers = maxCapacity / 2; // 基礎乘客數
        
        if (IsInPeakHour(timeOfDay))
        {
            // 高峰時段：更多乘客
            return Mathf.RoundToInt(basePassengers * Random.Range(1.5f, 2f));
        }
        else if (IsInOffPeakHour(timeOfDay))
        {
            // 離峰時段：較少乘客
            return Mathf.RoundToInt(basePassengers * Random.Range(0.3f, 0.5f));
        }
        else
        {
            // 正常時段
            return basePassengers + Random.Range(-20, 20);
        }
    }

    private bool IsInPeakHour(float timeOfDay)
    {
        return (timeOfDay >= peakHourStart && timeOfDay <= peakHourEnd);
    }

    private bool IsInOffPeakHour(float timeOfDay)
    {
        return (timeOfDay >= offPeakHourStart && timeOfDay <= offPeakHourEnd);
    }

    public float GetCrowdingLevel() => crowdingLevel;
    public int GetCurrentPassengers() => currentPassengers;
    public int GetMaxCapacity() => maxCapacity;
    public string GetCrowdingDescription()
    {
        if (crowdingLevel < 0.3f) return "空車";
        if (crowdingLevel < 0.7f) return "正常";
        return "滿員";
    }
}

[System.Serializable]
public class PassengerBehavior
{
    public string BehaviorType; // "Standing", "Sitting", "ReadingPhone", "Sleeping"
    public float Frequency; // 出現頻率
    public int Count; // 執行此行為的乘客數
}

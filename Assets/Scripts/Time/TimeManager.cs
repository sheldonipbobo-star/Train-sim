using UnityEngine;

public class TimeManager : MonoBehaviour
{
    [SerializeField] private float gameSpeedMultiplier = 60f; // 1秒遊戲時間 = 1分鐘真實時間
    [SerializeField] private float currentHour = 8f;
    [SerializeField] private float currentMinute = 0f;
    
    [Header("日夜循環")]
    [SerializeField] private Light sunLight;
    [SerializeField] private AnimationCurve dayNightCycle;
    [SerializeField] private float cycleDuration = 1200f; // 20分鐘 = 1天

    private float elapsedTime = 0f;

    private void Update()
    {
        UpdateGameTime();
        UpdateDayNightCycle();
    }

    private void UpdateGameTime()
    {
        elapsedTime += Time.deltaTime * gameSpeedMultiplier;
        
        currentMinute += Time.deltaTime * gameSpeedMultiplier;
        if (currentMinute >= 60f)
        {
            currentMinute -= 60f;
            currentHour += 1f;
            if (currentHour >= 24f)
            {
                currentHour = 0f;
            }
        }
    }

    private void UpdateDayNightCycle()
    {
        // 計算日夜循環進度 (0-1)
        float cycleProgress = (elapsedTime % cycleDuration) / cycleDuration;
        
        // 使用動畫曲線計算太陽光強度
        if (sunLight != null)
        {
            sunLight.intensity = dayNightCycle.Evaluate(cycleProgress);
            
            // 計算太陽旋轉角度
            float sunRotation = cycleProgress * 360f;
            sunLight.transform.rotation = Quaternion.Euler(sunRotation - 90f, 0, 0);
        }
    }

    public float GetCurrentHour() => currentHour;
    public float GetCurrentMinute() => currentMinute;
    public string GetTimeString() => $"{(int)currentHour:D2}:{(int)currentMinute:D2}";
    public bool IsNightTime() => currentHour >= 22f || currentHour < 6f;
}

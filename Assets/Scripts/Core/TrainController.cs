using UnityEngine;
using System.Collections;

public class TrainController : MonoBehaviour
{
    [Header("列車參數")]
    [SerializeField] private float maxSpeed = 80f; // km/h
    [SerializeField] private float acceleration = 1.5f; // m/s²
    [SerializeField] private float deceleration = 2f; // m/s²
    [SerializeField] private float currentSpeed = 0f;
    
    [Header("車站系統")]
    [SerializeField] private StationManager stationManager;
    [SerializeField] private int currentStationIndex = 0;
    [SerializeField] private bool isStoppingAtStation = false;
    [SerializeField] private float stopDuration = 15f; // 停靠時間（秒）
    
    [Header("乘客系統")]
    [SerializeField] private int currentPassengers = 0;
    [SerializeField] private int maxCapacity = 200;
    [SerializeField] private float crowdingLevel = 0f; // 0-1 擁擠度
    
    [Header("音頻系統")]
    [SerializeField] private AudioSource trainAudioSource;
    [SerializeField] private AudioClip accelerationSound;
    [SerializeField] private AudioClip brakingSound;
    [SerializeField] private AudioClip doorOpenSound;
    [SerializeField] private AudioClip doorCloseSound;
    [SerializeField] private AudioClip stationAnnouncementSound;
    
    private Rigidbody trainRigidbody;
    private float nextStationDistance = 0f;
    private bool doorsOpen = false;

    private void Start()
    {
        trainRigidbody = GetComponent<Rigidbody>();
        if (stationManager == null)
        {
            stationManager = FindObjectOfType<StationManager>();
        }
        StartCoroutine(TrainMovementLoop());
    }

    private void Update()
    {
        UpdateCrowdingLevel();
        UpdateTrainDisplay();
    }

    private IEnumerator TrainMovementLoop()
    {
        while (true)
        {
            if (!isStoppingAtStation)
            {
                yield return MoveToNextStation();
            }
            else
            {
                yield return StopAtStation();
            }
        }
    }

    private IEnumerator MoveToNextStation()
    {
        // 加速階段
        while (currentSpeed < maxSpeed)
        {
            currentSpeed += acceleration * Time.deltaTime;
            currentSpeed = Mathf.Min(currentSpeed, maxSpeed);
            
            // 更新列車位置
            transform.Translate(Vector3.forward * currentSpeed * Time.deltaTime);
            
            yield return null;
        }

        // 計算下一車站距離
        Station nextStation = stationManager.GetStation(currentStationIndex + 1);
        nextStationDistance = Vector3.Distance(transform.position, nextStation.GetPosition());

        // 當接近車站時開始減速
        while (nextStationDistance > 5f)
        {
            nextStationDistance = Vector3.Distance(transform.position, nextStation.GetPosition());
            yield return null;
        }

        // 減速階段
        while (currentSpeed > 0.5f)
        {
            currentSpeed -= deceleration * Time.deltaTime;
            transform.Translate(Vector3.forward * currentSpeed * Time.deltaTime);
            yield return null;
        }

        currentSpeed = 0f;
        isStoppingAtStation = true;
    }

    private IEnumerator StopAtStation()
    {
        // 開門
        OpenDoors();
        
        // 乘客上下車
        yield return new WaitForSeconds(stopDuration);
        
        // 關門
        CloseDoors();
        
        // 移動到下一車站
        currentStationIndex = (currentStationIndex + 1) % stationManager.GetStationCount();
        isStoppingAtStation = false;
        
        yield return new WaitForSeconds(1f);
    }

    private void OpenDoors()
    {
        if (!doorsOpen)
        {
            doorsOpen = true;
            PlaySound(doorOpenSound);
            // 觸發乘客上下車邏輯
            SimulatePassengerExchange();
        }
    }

    private void CloseDoors()
    {
        if (doorsOpen)
        {
            doorsOpen = false;
            PlaySound(doorCloseSound);
        }
    }

    private void SimulatePassengerExchange()
    {
        // 簡單的乘客模擬
        int boardingPassengers = Random.Range(10, 50);
        int alightingPassengers = Random.Range(5, currentPassengers / 2);
        
        currentPassengers -= alightingPassengers;
        currentPassengers += boardingPassengers;
        currentPassengers = Mathf.Clamp(currentPassengers, 0, maxCapacity);
    }

    private void UpdateCrowdingLevel()
    {
        crowdingLevel = (float)currentPassengers / maxCapacity;
    }

    private void UpdateTrainDisplay()
    {
        // 更新UI顯示列車狀態
        Station currentStation = stationManager.GetStation(currentStationIndex);
        // 更新速度、乘客數、車站信息等
    }

    private void PlaySound(AudioClip clip)
    {
        if (trainAudioSource != null && clip != null)
        {
            trainAudioSource.PlayOneShot(clip);
        }
    }

    public float GetCurrentSpeed() => currentSpeed;
    public int GetCurrentPassengers() => currentPassengers;
    public float GetCrowdingLevel() => crowdingLevel;
    public Station GetCurrentStation() => stationManager.GetStation(currentStationIndex);
    public bool AreDoorsOpen() => doorsOpen;
}

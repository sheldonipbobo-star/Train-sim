using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class GameUIManager : MonoBehaviour
{
    [Header("列車信息")]
    [SerializeField] private TextMeshProUGUI speedDisplay;
    [SerializeField] private TextMeshProUGUI stationDisplay;
    [SerializeField] private TextMeshProUGUI passengerDisplay;
    [SerializeField] private Slider crowdingSlider;
    
    [Header("時刻表")]
    [SerializeField] private TextMeshProUGUI timetableDisplay;
    [SerializeField] private TextMeshProUGUI nextStationDisplay;
    
    [Header("模式選擇")]
    [SerializeField] private Button touristModeButton;
    [SerializeField] private Button commuterModeButton;
    [SerializeField] private Button freeExploreButton;
    [SerializeField] private Button challengeModeButton;
    
    [Header("互動元素")]
    [SerializeField] private Button seatSelectionButton;
    [SerializeField] private Button mapButton;
    [SerializeField] private Toggle languageToggle; // 日語/英語
    
    [Header("參考")]
    [SerializeField] private TrainController trainController;
    [SerializeField] private StationManager stationManager;
    
    private GameMode currentMode = GameMode.FreeExplore;
    private bool japaneseLanguage = true;

    private void Start()
    {
        SetupButtons();
        InvokeRepeating("UpdateDisplay", 0f, 0.5f);
    }

    private void SetupButtons()
    {
        touristModeButton.onClick.AddListener(() => SetGameMode(GameMode.Tourist));
        commuterModeButton.onClick.AddListener(() => SetGameMode(GameMode.Commuter));
        freeExploreButton.onClick.AddListener(() => SetGameMode(GameMode.FreeExplore));
        challengeModeButton.onClick.AddListener(() => SetGameMode(GameMode.Challenge));
        
        seatSelectionButton.onClick.AddListener(OpenSeatSelection);
        mapButton.onClick.AddListener(OpenMap);
        languageToggle.onValueChanged.AddListener(ToggleLanguage);
    }

    private void UpdateDisplay()
    {
        if (trainController == null) return;

        // 更新速度顯示
        float speedKmh = trainController.GetCurrentSpeed();
        speedDisplay.text = $"速度: {speedKmh:F1} km/h";

        // 更新車站信息
        Station currentStation = trainController.GetCurrentStation();
        if (currentStation != null)
        {
            string stationName = japaneseLanguage ? currentStation.NameJa : currentStation.NameEn;
            stationDisplay.text = $"現在位置: {stationName}";
        }

        // 更新乘客信息
        int passengers = trainController.GetCurrentPassengers();
        passengerDisplay.text = $"乘客: {passengers}人";
        
        // 更新擁擠度
        float crowding = trainController.GetCrowdingLevel();
        crowdingSlider.value = crowding;
    }

    private void SetGameMode(GameMode mode)
    {
        currentMode = mode;
        switch (mode)
        {
            case GameMode.Tourist:
                // 啟用車站信息和教育內容
                ShowEducationalContent();
                break;
            case GameMode.Commuter:
                // 逼真的通勤體驗
                EnableCommuterMode();
                break;
            case GameMode.FreeExplore:
                // 自由探索
                EnableFreeExplore();
                break;
            case GameMode.Challenge:
                // 挑戰模式
                EnableChallengeMode();
                break;
        }
    }

    private void ShowEducationalContent()
    {
        Debug.Log("遊客模式：顯示車站信息和景點介紹");
    }

    private void EnableCommuterMode()
    {
        Debug.Log("通勤者模式：逼真的日常通勤模擬");
    }

    private void EnableFreeExplore()
    {
        Debug.Log("自由探索模式：可在任何車站上下車");
    }

    private void EnableChallengeMode()
    {
        Debug.Log("挑戰模式：完成特定目標任務");
    }

    private void OpenSeatSelection()
    {
        Debug.Log("打開座位選擇界面");
    }

    private void OpenMap()
    {
        Debug.Log("打開山手線地圖");
    }

    private void ToggleLanguage(bool useJapanese)
    {
        japaneseLanguage = useJapanese;
    }
}

public enum GameMode
{
    Tourist,
    Commuter,
    FreeExplore,
    Challenge
}

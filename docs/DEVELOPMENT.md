# 開發指南

## 專案設置

### 環境要求
- Unity 2022 LTS 或更新版本
- C# 8.0 或更新版本
- TextMeshPro（Unity 內置）

### 快速開始

1. **克隆儲存庫**
```bash
git clone https://github.com/sheldonipbobo-star/Train-sim.git
cd Train-sim
```

2. **用 Unity 開啟專案**
- 打開 Unity Hub
- 選擇 Unity 2022 LTS
- 打開此資料夾

3. **導入必要套件**
- TextMeshPro：已包含在 Unity 中

## 核心系統架構

### 1. 列車系統（TrainController）
- **職責**：管理列車的物理運動、速度、加速度
- **主要方法**：
  - `MoveToNextStation()`：移動到下一個車站
  - `StopAtStation()`：在車站停靠
  - `SimulatePassengerExchange()`：模擬上下車

### 2. 車站系統（StationManager）
- **職責**：管理所有 29 個山手線車站的信息
- **數據來源**：`docs/station_data.json`
- **主要方法**：
  - `GetStation(int index)`：獲取特定車站
  - `GetStationByName(string name)`：按名稱查詢車站

### 3. UI 系統（GameUIManager）
- **職責**：管理遊戲界面和用戶交互
- **主要功能**：
  - 顯示列車速度、乘客、擁擠度
  - 遊戲模式選擇
  - 語言切換

### 4. 音頻系統（AudioManager）
- **職責**：管理所有音效和播報
- **主要方法**：
  - `PlayStationAnnouncement()`：播放車站播報
  - `PlayTrainAccelerationSound()`：加速音效
  - `PlayTrainBrakingSound()`：制動音效

### 5. 乘客系統（PassengerSystem）
- **職責**：模擬動態乘客行為
- **時間系統**：
  - 高峰時段（7:00-9:00、17:00-19:00）
  - 離峰時段（14:00-16:00）
  - 夜間時段（22:00-06:00）

## 遊戲流程

```
遊戲開始
    ↓
選擇遊戲模式（遊客/通勤者/自由探索/挑戰）
    ↓
列車開始運行
    ↓
列車加速 → 行駛 → 減速 → 停靠
    ↓
乘客上下車（播放動畫和音效）
    ↓
重複運行
```

## 文件結構說明

```
Assets/
├── Scripts/
│   ├── Core/
│   │   ├── TrainController.cs      # 列車控制
│   │   └── StationManager.cs       # 車站管理
│   ├── UI/
│   │   └── GameUIManager.cs        # UI 界面
│   ├── Audio/
│   │   └── AudioManager.cs         # 音頻系統
│   └── Passenger/
│       └── PassengerSystem.cs      # 乘客系統
├── Scenes/
│   └── MainGame.unity              # 主遊戲場景
├── Prefabs/
│   ├── Train.prefab               # 列車預設
│   └── Passenger.prefab           # 乘客預設
└── Resources/
    ├── Audio/
    │   ├── Train/
    │   ├── Announcements/
    │   └── Ambient/
    └── Data/
        └── station_data.json      # 車站數據
```

## 開發流程

### 添加新功能的步驟

1. **創建功能分支**
```bash
git checkout -b feature/your-feature-name
```

2. **編寫代碼**
- 遵循 C# 命名規範
- 使用有意義的變量名稱
- 添加必要的注釋

3. **測試功能**
- 在 Unity 編輯器中運行
- 使用 Play Mode 測試

4. **提交變更**
```bash
git add .
git commit -m "Add: 功能描述"
git push origin feature/your-feature-name
```

5. **發起 Pull Request**
- 描述你的改變
- 添加截圖或視頻演示

## 常見任務

### 添加新的音效

1. 將音頻文件放在 `Assets/Resources/Audio/` 中
2. 在 `AudioManager.cs` 中註冊音頻
3. 在需要的地方調用 `PlaySound()` 方法

### 添加新的遊戲模式

1. 在 `GameMode` 枚舉中添加新模式
2. 在 `GameUIManager.cs` 中實現模式邏輯
3. 添加相應的 UI 按鈕

### 修改列車速度參數

1. 編輯 `TrainController.cs` 中的速度參數
2. 調整 `maxSpeed`、`acceleration`、`deceleration` 值
3. 在編輯器中測試

## 調試技巧

### 啟用控制台日誌
```csharp
Debug.Log("訊息");
Debug.LogWarning("警告");
Debug.LogError("錯誤");
```

### 使用 Inspector 調試
- 在 Inspector 中修改 SerializeField 值
- 實時觀察遊戲行為變化

### 暫停遊戲
- Press Space 暫停
- 檢查當前狀態

## 性能優化建議

1. **減少物理計算**：使用 Fixed Time Step
2. **優化渲染**：使用 LOD（Level of Detail）系統
3. **音頻管理**：限制同時播放的音效數量
4. **乘客渲染**：使用對象池（Object Pool）

## 單位標準

- **距離**：米（m）
- **速度**：公里/小時（km/h）轉換為 m/s
- **時間**：秒（s）
- **音量**：0-1（0 = 靜音，1 = 最大）

## 常見問題

### Q: 如何修改車站信息？
A: 編輯 `docs/station_data.json` 文件，然後重新加載場景。

### Q: 如何添加新的乘客模型？
A: 在 `Assets/Prefabs/Passenger.prefab` 中創建新的預設。

### Q: 如何改變遊戲難度？
A: 調整 `PassengerSystem.cs` 和 `TrainController.cs` 中的參數。

## 貢獻指南

歡迎提交 Bug 報告和功能建議！

1. 檢查是否已有相似的 Issue
2. 提供詳細的描述和截圖
3. 遵循代碼風格指南

---

最後更新：2026-06-11

# 遊戲設置指南

## Unity 專案設置步驟

### 1. 初始化 Unity 專案

```bash
# 在 Unity Hub 中建立新專案
- 版本：Unity 2022 LTS
- 範本：3D (URP)
```

### 2. 導入必要套件

在 Unity 中，進入 **Window > TextMeshPro > Import TMP Essential Resources**

### 3. 配置場景

#### 建立主場景 (MainGame.unity)

1. **建立空物體**：GameObject > Create Empty
   - 命名為 "GameManager"
   - 添加 `GameUIManager` 腳本

2. **建立列車物體**
   - GameObject > 3D Object > Cube
   - 命名為 "Train"
   - 調整比例：Scale (2, 2.5, 5)
   - 添加 `TrainController` 腳本
   - 添加 `Rigidbody` 組件

3. **建立相機**
   - GameObject > Create Empty
   - 命名為 "PlayerCamera"
   - 拖入 Main Camera
   - 添加 `CameraController` 腳本

4. **建立光照**
   - GameObject > Light > Directional Light
   - 命名為 "SunLight"
   - 用於日夜循環

5. **建立 UI Canvas**
   - GameObject > UI > Panel (Canvas)
   - 添加以下元素：
     - Text (速度顯示)
     - Text (車站信息)
     - Text (乘客數)
     - Slider (擁擠度)

### 4. 配置腳本參考

在 Inspector 中設置：

- **TrainController**
  - Station Manager：將 StationManager 物體拖入
  - Audio Source：添加 Audio Source 組件
  - Max Speed：80
  - Acceleration：1.5
  - Deceleration：2

- **StationManager**
  - Station Data JSON：Assets/Resources/Data/station_data.json

- **GameUIManager**
  - Train Controller：Train 物體
  - Station Manager：StationManager 物體
  - 速度顯示：Text 元素
  - 車站顯示：Text 元素
  - 乘客顯示：Text 元素
  - 擁擠度滑塊：Slider 元素

### 5. 測試遊戲

按 Play 按鈕執行遊戲，檢查：
- ✅ 列車是否移動
- ✅ UI 是否更新
- ✅ 車站是否正確
- ✅ 乘客數是否變化

## 常見問題解決

### 問題：列車不動
**解決**：檢查 Rigidbody 的 Constraints，確保 "Freeze Rotation" 已勾選

### 問題：找不到 Station Data JSON
**解決**：確保文件位於 `Assets/Resources/Data/station_data.json`

### 問題：音效不播放
**解決**：檢查 AudioSource 是否有指定 clip，檢查音量是否為 0

## 下一步

1. 導入 3D 模型（列車、車站、乘客）
2. 添加景觀和地標
3. 實現音效和音樂
4. 完善 UI 設計
5. 優化性能

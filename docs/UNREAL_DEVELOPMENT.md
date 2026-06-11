# 🚂 Unreal Engine 5 山手線列車模擬器 - 開發指南

## 專案結構

```
Train-sim/
├── Source/
│   ├── TrainSim/
│   │   ├── Public/
│   │   │   ├── Train/
│   │   │   │   └── TrainController.h        # 列車控制器
│   │   │   ├── Station/
│   │   │   │   └── StationManager.h         # 車站管理器
│   │   │   ├── Passenger/
│   │   │   │   └── PassengerSystem.h        # 乘客系統
│   │   │   └── TrainSimModule.h             # 模組入口
│   │   ├── Private/
│   │   │   ├── Train/
│   │   │   │   └── TrainController.cpp
│   │   │   ├── Station/
│   │   │   │   └── StationManager.cpp
│   │   │   ├── Passenger/
│   │   │   │   └── PassengerSystem.cpp
│   │   │   └── TrainSimModule.cpp
│   │   └── TrainSim.Build.cs
│   ├── TrainSim.Target.cs
│   └── TrainSimEditor.Target.cs
├── Content/
│   ├── Maps/
│   │   └── MainGame.umap                    # 主遊戲級別
│   ├── Blueprints/
│   │   ├── BP_TrainController.uasset
│   │   ├── BP_StationManager.uasset
│   │   └── BP_PassengerSystem.uasset
│   ├── Meshes/
│   │   ├── Train/
│   │   ├── Stations/
│   │   └── Environment/
│   ├── Materials/
│   ├── Sounds/
│   └── Textures/
├── docs/
├── TrainSim.uproject
└── README.md
```

## 核心系統架構

### 1. TrainController（列車控制器）

**職責**：
- 管理列車的物理運動（加速、減速、速度）
- 控制列車門的開關
- 與乘客系統交互

**主要函數**：
```cpp
void StartMovement();           // 開始移動
void StopMovement();            // 停止移動
void OpenDoors();               // 打開車門
void CloseDoors();              // 關閉車門
void SimulatePassengerExchange(); // 模擬乘客上下車
```

### 2. StationManager（車站管理器）

**職責**：
- 存儲和管理 29 個山手線車站的數據
- 提供車站信息查詢
- 處理列車停靠邏輯

**主要函數**：
```cpp
FStationData GetStation(int32 Index);
FStationData GetStationByName(const FString& Name);
FVector GetStationPosition(int32 Index);
int32 GetStationCount();
```

### 3. PassengerSystem（乘客系統）

**職責**：
- 模擬乘客行為（隨時間變化）
- 計算列車擁擠程度
- 處理高峰時段邏輯

**主要函數**：
```cpp
void InitializePassengers(float TimeOfDay);
void HandlePassengerExchange(float BoardingRate, float AlightingRate);
FString GetCrowdingDescription();
```

## 開發工作流程

### 添加新功能的步驟

1. **創建頭文件** (Public/)
   ```cpp
   #pragma once
   #include "CoreMinimal.h"
   #include "GameFramework/Actor.h"
   #include "MyNewSystem.generated.h"
   
   UCLASS()
   class TRAINSIM_API AMyNewSystem : public AActor
   {
       GENERATED_BODY()
       // ...
   };
   ```

2. **實現源文件** (Private/)
   ```cpp
   #include "MyNewSystem/MyNewSystem.h"
   // 實現函數
   ```

3. **添加到 Build.cs**
   ```cpp
   PublicDependencyModuleNames.AddRange(new string[] { 
       // 依賴模組
   });
   ```

4. **編譯和測試**
   ```
   Visual Studio: Ctrl+Shift+B
   或 Unreal Editor: Compile
   ```

5. **創建 Blueprint 包裝**
   ```
   Content Browser → Create Blueprint Based On... → MyNewSystem
   ```

### 編碼規範

**命名規範**（Unreal 標準）：
- Classes: `AClassName` (Actor)
- Components: `UComponentName` (UObject)
- Interfaces: `IInterfaceName`
- Enums: `EEnumName`
- Structs: `FStructName`
- Variables: `bIsVariable` (bool), `MyVariable` (其他)
- Functions: `GetValue()`, `SetValue()`

**代碼風格**：
```cpp
// 文件頭部註釋
// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class TRAINSIM_API AMyActor : public AActor
{
    GENERATED_BODY()

public:
    AMyActor();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCategory")
    float MyVariable = 0.0f;

    UFUNCTION(BlueprintCallable, Category = "MyCategory")
    void MyFunction();

private:
    void PrivateFunction();
};
```

## 常用命令

### Visual Studio

```bash
# 編譯
Ctrl+Shift+B

# 編譯並運行
F5

# 清理
Build → Clean Solution
```

### Unreal Editor

```
# 編譯 C++ 代碼
Tools → Refresh Visual Studio Project
Tools → Compile

# 運行遊戲
Alt+P (獨立窗口)
Ctrl+P (在 Editor 中)

# 打開輸出日誌
Window → Developer Tools → Output Log

# 打開 Class Viewer
Window → Developer Tools → Class Viewer
```

## 除錯技巧

### 添加日誌

```cpp
UE_LOG(LogTemp, Warning, TEXT("訊息: %d"), MyValue);
UE_LOG(LogTemp, Error, TEXT("錯誤訊息"));
```

### 設置斷點

1. Visual Studio 中在代碼行前點擊設置斷點
2. 按 F5 以除錯模式運行
3. 遊戲會在斷點處暫停
4. 使用 F10（逐步執行）、F11（單步執行）

### 檢查變量值

在 Editor 中選擇 Actor：
- Details 面板顯示所有 UPROPERTY 值
- 可以在運行時修改值

## 性能優化

### Profiling

```
Window → Developer Tools → Profiler
```

### 性能目標

- **幀率**：60 FPS
- **CPU 時間**：< 16.67 ms
- **Memory**：< 2 GB

### 優化技巧

1. 使用對象池而不是頻繁創建/銷毀
2. 使用藍圖代替 C++ 進行非關鍵邏輯
3. 利用 Unreal 的線程系統進行並行處理
4. 使用 Nanite（自動細節 LOD）進行網格
5. 啟用 Lumen（實時全局光照）

## 版本控制最佳實踐

### .gitignore

`.gitignore` 已配置以排除：
- Binaries/
- Intermediate/
- Saved/
- .vs/
- *.sln

### 提交工作流程

```bash
# 檢查狀態
git status

# 添加文件
git add Source/ Content/

# 提交
git commit -m "[功能名稱] 簡短描述"

# 推送
git push origin main
```

## 資源導入

### 導入 3D 模型

1. **準備模型**：FBX、GLTF 格式
2. **拖入 Content Browser**：Content/Meshes/
3. **配置設置**：
   - Skeletal Mesh (如果有骨骼)
   - Static Mesh (靜態模型)
   - 導入法線和切線
   - 配置材質槽

### 導入音頻

1. **支持格式**：WAV、MP3、FLAC
2. **拖入 Content Browser**：Content/Sounds/
3. **配置**：
   - 選擇合適的聲音波類型
   - 設置音量
   - 配置空間化

## 故障排除

### 藍圖找不到 C++ 類

```
1. 刷新 Visual Studio 項目
2. 重新編譯 C++ 代碼
3. 重新啟動 Editor
```

### "Missing Module" 錯誤

```
檢查 TrainSim.Build.cs 中的依賴模組
確保已添加所有必要的 PublicDependencyModuleNames
```

### 遊戲崩潰

```
1. 查看 Crash Reporter
2. 檢查 Output Log 中的錯誤
3. 在 Visual Studio 中設置斷點重現問題
```

## 相關資源

- [Unreal Engine 官方文檔](https://docs.unrealengine.com/)
- [Unreal Engine C++ API](https://docs.unrealengine.com/5_4/en-US/API/)
- [Unreal Engine 論壇](https://forums.unrealengine.com/)
- [Unreal Slackers Discord](https://www.unrealslackers.org/)


# 🚂 Unreal Engine 5 山手線列車模擬器 - 安裝和運行指南

## 前置要求

### 系統要求
- **操作系統**：Windows 10/11 或 macOS 12+
- **RAM**：至少 16GB（推薦 32GB）
- **硬碟**：至少 200GB 可用空間
- **GPU**：NVIDIA RTX 3060 或更高（或 AMD 等效）
- **CPU**：Intel i7/i9 或 AMD Ryzen 7/9

### 軟體要求
- **Unreal Engine 5.4** 或更新版本
- **Visual Studio 2022** 社群版（含 C++ 工作負載）
- **Git** 已安裝

## 步驟 1：安裝必要軟體

### 1.1 安裝 Unreal Engine 5

```bash
# 方式 A：使用 Epic Games Launcher
1. 下載 Epic Games Launcher
2. 登錄或創建 Epic Games 帳戶
3. 點擊 "Unreal Engine" → "版本" → 安裝 "5.4" 或最新版本
4. 等待安裝完成（約 50-100GB）
```

### 1.2 安裝 Visual Studio 2022

```bash
# 下載: https://visualstudio.microsoft.com/vs/

# 安裝時選擇以下工作負載：
✅ C++ 桌面開發
✅ Windows 10 SDK
✅ CMake 工具
```

### 1.3 安裝 Git

```bash
# Windows: https://git-scm.com/download/win
# macOS: brew install git
```

## 步驟 2：克隆專案

```bash
# 打開命令提示符或 PowerShell
cd C:\Projects  # 或任何你想放置的目錄
git clone https://github.com/sheldonipbobo-star/Train-sim.git
cd Train-sim
```

## 步驟 3：生成 Unreal Engine 專案文件

### Windows

```bash
# 在 Train-sim 目錄中

# 方式 1：使用右鍵菜單（推薦）
1. 右鍵點擊 TrainSim.uproject
2. 選擇 "Generate Visual Studio project files"
3. 等待完成

# 方式 2：使用命令行
C:\Program Files\Epic Games\UE_5.4\Engine\Build\BatchFiles\GenerateProjectFiles.bat TrainSim.uproject -projectfiles -project="%cd%\TrainSim.uproject" -game -engine
```

### macOS

```bash
# 在 Train-sim 目錄中
/Volumes/Epic\ Games/UE_5.4/Engine/Build/BatchFiles/GenerateProjectFiles.sh -project="$(pwd)/TrainSim.uproject" -game -engine
```

## 步驟 4：編譯專案

### Windows（推薦方式）

```bash
# 方式 1：使用 Visual Studio（最簡單）
1. 打開生成的 TrainSim.sln
2. 在 Solution Explorer 中找到 TrainSim (Games)
3. 右鍵 → Build
4. 等待編譯完成（首次需要 5-15 分鐘）

# 方式 2：使用命令行
C:\Program Files\Epic Games\UE_5.4\Engine\Build\BatchFiles\Build.bat TrainSimEditor Win64 Development TrainSim.sln -WaitMutex
```

### macOS

```bash
/Volumes/Epic\ Games/UE_5.4/Engine/Build/BatchFiles/Mac/Build.sh TrainSimEditor Mac Development
```

## 步驟 5：用 Unreal Editor 打開專案

### 方式 A：使用 Unreal Editor GUI（推薦）

```bash
# Windows
C:\Program Files\Epic Games\UE_5.4\Engine\Binaries\Win64\UE4Editor.exe C:\Projects\Train-sim\TrainSim.uproject

# macOS
/Volumes/Epic\ Games/UE_5.4/Engine/Binaries/Mac/UE4Editor.app/Contents/MacOS/UE4Editor /Users/你的用戶名/Projects/Train-sim/TrainSim.uproject
```

### 方式 B：雙擊 .uproject 文件

1. 打開文件管理器
2. 導航到 Train-sim 文件夾
3. 雙擊 `TrainSim.uproject`
4. 選擇「Generate」和「Open」

## 步驟 6：Unreal Editor 首次啟動

當 Unreal Editor 首次打開時：

1. ✅ 等待 C++ 代碼編譯（約 5-10 分鐘）
2. ✅ Editor 會自動掃描所有源文件
3. ✅ 檢查 Output Log（Window → Developer Tools → Output Log）
4. ✅ 確認沒有紅色錯誤訊息

## 步驟 7：創建主遊戲級別

### 7.1 創建新級別

```
File → New Level → Empty Level
```

### 7.2 保存級別

```
Ctrl+S → Content/Maps/MainGame
```

### 7.3 放置核心 Actor

**在 Level 中放置 TrainController**

1. 在 Content Browser 中搜索 "ATrainController"
2. 拖入 Viewport
3. 在 Details 面板中配置參數：
   - Max Speed: 80
   - Acceleration: 1.5
   - Deceleration: 2

**放置 StationManager**

1. 搜索 "AStationManager"
2. 拖入 Viewport
3. 它會自動初始化 29 個車站

**放置 PassengerSystem**

1. 搜索 "APassengerSystem"
2. 拖入 Viewport
3. 配置時間段參數

### 7.4 設置相機

1. 在 Viewport 中放置 Camera Actor
2. 設置其位置為列車上方（Z = 250）
3. 指向列車（Y rotation = 90 度）

## 步驟 8：運行遊戲

### 在 Editor 中運行

```
點擊 Play 按鈕 (Ctrl+P)
或
Alt+P（独立窗口）
```

### 打包為可執行文件

```
File → Package Project → Windows (64-bit)
選擇輸出目錄
等待打包完成（約 10-20 分鐘）
運行 TrainSim/Binaries/Win64/TrainSimEditor.exe
```

## 常見問題解決

### ❌ 錯誤：找不到 Visual Studio

**解決**：
```
1. 安裝 Visual Studio 2022 Community
2. 確保選擇 C++ 工作負載
3. 重新啟動 Unreal Editor
```

### ❌ 錯誤：C++ 代碼編譯失敗

**解決**：
```
1. 刪除 Binaries、Intermediate、Saved 文件夾
2. 重新生成 Visual Studio 項目文件
3. 在 Visual Studio 中清理並重建
4. 重新打開 Unreal Editor
```

### ❌ 錯誤：內存不足

**解決**：
```
- 關閉其他應用程序
- 增加虛擬內存
- 升級系統 RAM
```

### ❌ 列車 Actor 不顯示

**解決**：
```
1. 檢查 Content Browser 中是否有該 Actor 類
2. 確保 C++ 代碼已成功編譯（無紅色錯誤）
3. 重新啟動 Editor
```

## 快速檢查清單

- [ ] Unreal Engine 5.4+ 已安裝
- [ ] Visual Studio 2022 已安裝（含 C++）
- [ ] Git 已安裝
- [ ] 專案已克隆
- [ ] .sln 文件已生成
- [ ] 項目已編譯無誤
- [ ] Unreal Editor 可以打開
- [ ] TrainController、StationManager、PassengerSystem 已放入 Level
- [ ] 可以按 Play 運行遊戲

## 性能優化

### 編譯速度

```ini
# Engine/Saved/Config/Windows/Engine.ini
[/Script/Engine.Engine]
GPUCrashDebugging=False
UseFixedFrameRate=True
FixedFrameRate=60.0
```

### 內存管理

```cpp
// 在 TrainSimModule.cpp
FPlatformMemory::SetupMemoryPools();
```

## 下一步

1. 📚 查看 `docs/DESIGN_SPEC.md` 了解詳細設計
2. 🎨 導入 3D 模型（列車、車站、乘客）
3. 🔊 添加音頻資源
4. 🎮 實現玩家交互系統
5. 🧪 進行測試和優化

---

**需要幫助？檢查 Unreal Engine 官方文檔：** https://docs.unrealengine.com/

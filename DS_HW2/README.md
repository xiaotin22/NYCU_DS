# Data Structure Fall 2025 - HW2 Linked List 🔗
## Overview 📖
這次作業主要是使用 C++ 實作了兩種不同的鏈結串列：SingleList 和 XORList。

## 檔案說明 📁
- `113511266_hw2.h`: 標頭檔，包含類別宣告
- `113511266_hw2.cpp`: 實作檔，包含所有方法和測試函數
- `Makefile`: 建置設定檔，支援 `make all` 指令
- `README.md`: 本說明文件

## 實作的類別 🏗️

### Node 類別 (統一節點設計) 🎯
- **統一節點類別**：同時支援單向鏈結串列和 XOR 鏈結串列
- 包含整數鍵值 `k` 作為唯一識別碼
- `next` 指標：用於單向鏈結串列
- `npx` 欄位：用於 XOR 鏈結串列，儲存相鄰節點的 XOR 值
- **設計優勢**：統一的節點結構讓代碼更精簡，避免重複定義 ✨

### SingleList 類別 
傳統的單向鏈結串列，提供以下方法：
- `list_walk()`: 依序印出所有鍵值
- `list_prepend(Node* x)`: 在頭部插入新節點
- `list_insert(Node* x, Node* y)`: 將節點 x 插入到節點 y 之後  
- `list_search(int k)`: 搜尋鍵值並印出結果
- `list_delete(Node* n)`: 刪除指定節點
- `list_ins_del(int k)`: 不存在則插入，存在則刪除
- `list_reverse()`: 反轉整個串列 🔄

### XORList 類別
XOR 鏈結串列實作，提供記憶體效率高的雙向遍歷：
- 所有方法與 SingleList 相同，但針對 XOR 結構最佳化
- 使用指標運算和 XOR 操作進行導覽  
- 由於 XOR 指標相依性，刪除處理更加複雜 🧩

## 實作細節 🔍

1. **統一節點設計優勢**: 
   - 使用同一個 Node 類別同時支援兩種串列類型
   - SingleList 使用 `next` 指標，忽略 `npx` 欄位
   - XORList 使用 `npx` 欄位，忽略 `next` 指標
   - 代碼更精簡，避免重複的類別定義 🎯

2. **XOR 鏈結串列邏輯**: 
   - 每個節點儲存前一個和下一個節點位址的 XOR 值
   - 遍歷時需要記住前一個節點來計算下一個節點
   - 刪除操作複雜，需要更新相鄰節點的 XOR 值

3. **記憶體管理**: 
   - 適當的解構函式防止記憶體洩漏 🛡️
   - 使用 `uintptr_t` 進行安全的 XOR 操作指標處理

4. **隨機數生成**: 
   - 使用 `std::random_device` 和 `std::mt19937` 產生高品質隨機數 🎲
   - 在插入階段確保鍵值的唯一性
   - 在 [1, 1,000,000] 範圍內均勻分佈

4. **效能測量**:
   - 使用 `std::chrono::high_resolution_clock` 進行精確計時 ⏱️
   - 分別測量每個操作的執行時間：
     - Insert 操作時間（20萬次 prepend）
     - Insert-delete 操作時間（20萬次 ins_del）
     - Walk 操作時間（遍歷整個串列）
     - Reverse 操作時間（反轉串列）
     - Walk after reverse 時間（反轉後再次遍歷）

5. **測試函數**:
   - `slist_test()`: 測試 SingleList，包含 20萬次插入和 20萬次插入或刪除操作
   - `xlist_test()`: 測試 XORList，執行相同操作
   - 兩個函數都包含計時測量和輸出格式化 📊
   - 測試函數會返回 `TestResults` 結構，包含各項操作的執行時間
   - 主程式統一顯示兩種串列的效能比較結果

## 編譯與執行 ⚙️
```bash
make all        # 編譯程式
./113511266_hw2 # 執行程式
make clean      # 移除執行檔
```

## 輸出格式 📝
程式會輸出：
1. 測試期間的插入確認訊息（每次 prepend 和 ins_del 操作）
2. 操作後的最終串列內容
3. 反轉後的串列內容  
4. 詳細的效能比較結果，包含每個操作的微秒級時間測量

## 效能考量 ⚡
- XOR 鏈結串列節省記憶體（每個節點一個指標 vs 兩個）
- 但是，XOR 操作增加了計算開銷
- XOR 串列中的刪除需要更複雜的指標操作
- 兩種實作都能處理大型資料集（總共 40萬次操作）💪

# 📊 SingleList vs XORList 時間複雜度比較

| 操作 (Operation)         | SingleList 時間複雜度 | XORList 時間複雜度 | 備註 |
|---------------------------|-----------------------|--------------------|------|
| **Insert operations**     | O(1)                 | O(1)               | 頭插入皆為常數時間 |
| **Insert-delete**         | Insert: O(1)<br>Delete head: O(1)<br>Delete tail: O(n)<br>Delete middle: O(n) | Insert: O(1)<br>Delete head: O(1)<br>Delete tail: O(1)<br>Delete middle: O(n) | XORList 在刪除尾節點時更快 |
| **Walk (遍歷)**           | O(n)                 | O(n)               | XORList 每步多做一次 XOR 計算，常數時間略高 |
| **Reverse (反轉)**        | O(n)                 | O(1)               | XORList 只需改變走訪方向即可 |
| **Walk after reverse**    | O(n)                 | O(n)               | XORList 可天然支援反向走訪 |

---

## 實測結果 (μs)

| 操作 (Operation)         | SingleList (μs) | XORList (μs) | 說明 |
|---------------------------|-----------------|--------------|------|
| **Insert operations**     | 457,086         | 402,880      | XORList 稍快 |
| **Insert-delete**         | 165,542,035     | 216,422,859  | SingleList 明顯更快 |
| **Walk (遍歷)**           | 282,087         | 233,800      | XORList 略快 |
| **Reverse (反轉)**        | 5,362           | 0            | XORList O(1) 幾乎不耗時 |
| **Walk after reverse**    | 234,876         | 254,111      | SingleList 略快 |

---

## 📌 總結
- **插入效率**：XORList 略勝一籌。  
- **插入刪除混合操作**：SingleList 明顯更快，可能因為 XORList 在複雜操作中需要更多 XOR 計算。
- **遍歷操作**：XORList 稍快，但差距不大。
- **反轉操作**：XORList 壓倒性優勢，O(1) 時間複雜度只需交換頭尾指標。  
- **整體而言**：每種串列都有其優勢場景，XORList 在記憶體使用和特定操作上有優勢，但實作複雜度較高。  
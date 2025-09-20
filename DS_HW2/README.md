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
- `list_insert(int k)`: 在頭部插入新鍵值  
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
   - 測量操作的總執行時間

5. **測試函數**:
   - `slist_test()`: 測試 SingleList，包含 20萬次插入和 20萬次插入或刪除操作
   - `xlist_test()`: 測試 XORList，執行相同操作
   - 兩個函數都包含計時測量和輸出格式化 📊

## 編譯與執行 ⚙️
```bash
make all        # 編譯程式
./113511266_hw2 # 執行程式
make clean      # 移除執行檔
```

## 輸出格式 📝
程式會輸出：
1. 測試期間的插入確認訊息
2. 操作後的最終串列內容
3. 反轉後的串列內容  
4. 每個測試的執行時間

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
| **Insert operations**     | 498,525         | 436,460      | 幾乎相同，XORList 稍快 |
| **Insert-delete**         | 169,050,494     | 214,915,914  | 都很大，XORList 稍慢 |
| **Walk (遍歷)**           | 268,922         | 250,184      | 數值接近，XORList 略快 |
| **Reverse (反轉)**        | 5,318           | 0            | XORList O(1) 幾乎不耗時 |
| **Walk after reverse**    | 251,475         | 229,728      | XORList 輕微優勢 |

---

## 📌 總結
- 插入效率相近。  
- **刪除尾節點、反轉**：XORList 佔優勢。  
- **遍歷與中間刪除**：理論上相同，但 XORList coding 較複雜。  
- 實測數據大致符合理論，僅遍歷上 XORList 偶爾更快，可能與 CPU cache 或編譯器最佳化有關。  
# DFS for flow decomposition

以Depth-First Search深度優先搜尋法分解流量，共有X/Y/Z三種網絡，前二者為人流網絡，後者為車流網絡，人流網絡中的XE/YE調度節線**部分須由車輛協助移動**，故可能同時出現在車流網絡，示意圖如下。（XYZ三種網絡之流量求解方法以及其餘節線代表意義，此處不多作說明）
![時空網絡示意](https://github.com/woodwood0/DFS-for-flow-decomposition/assets/171545924/ce204b97-ca45-4458-b8e3-b5bb75856a47)
<br>

## 流程
1. **讀檔並建構圖形Graph**<br>
   根據數據添加邊到圖形 g1, g2, g3，每個Graph代表不同網絡。<br>

2. **對每個Graph分別執行DFS**<br>
   `DFS`初始化數據結構，並造訪未訪問過的起點。<br>
   `DFSVisit`遞歸訪問未訪問過的節點。<br>

3. **計算流量與輸出結果**<br>
    使用`buildAft`與`countFlow`計算流量，並將結果寫入文件。<br>

## 檔案說明
- 輸入`arc_flow_S.txt` : 編碼方式如圖，資料處理後輸出`arc_flow_S_after`。<br>
![檔案編碼](https://github.com/woodwood0/DFS-for-flow-decomposition/assets/171545924/24fa67ea-6f50-49a2-ac4c-e615a0865128)


- 輸出`count_flow_result` : 編碼方式如圖，說明如下，<br>
Array 列出30位人員在X網絡的作業路線<br>
Z Array 列出X網絡的人員同時在Z網絡的路線<br>
Z total Array 列出Z網絡此時累積的流量(X)<br>
Array 列出3位人員在Y網絡的作業路線<br>
Z Array 列出Y網絡的人員同時在Z網絡的路線<br>
Z total Array 列出Z網絡此時累積的流量(X+Y)<br>
![檔案編碼](https://github.com/woodwood0/DFS-for-flow-decomposition/assets/171545924/11fd878a-b798-4cb8-a0a2-df7d1431cd30)




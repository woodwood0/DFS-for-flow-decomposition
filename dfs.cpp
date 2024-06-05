#include <iostream> 
#include <vector>
#include <list>
#include <queue>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <utility>
#include <map>
using namespace std;



class Graph {
private:
    int num_vertex;
    std::vector< std::list<int> > adj;
    int* visit;


public:
    Graph() :num_vertex(0) {};
    Graph(int V) :num_vertex(V) {
        // initialize Adj List
        adj.resize(num_vertex);
    };


    void addEdge(int m, int n);
    void DFS(int Start, int all, int* arr[], int* aft[], int cnditn);
    void DFSVisit(int vertex, int all, int* arr[], int tmp, int* aft[], int cnditn);
    void buildAft(int nodebuild, int type, int* aft[], int c, int r, int all);
    void countFlow(int N, int Z, int* aft[], int* aftz[], FILE* fp3, int* aftmp[], int cnditn);
};

void Graph::addEdge(int m, int n)
{
    adj[m].push_back(n);                                // Add n to m’s list.
}

void Graph::DFS(int Start, int all, int* arr[], int* aft[], int cnditn) {
    visit = new int[num_vertex];                        // 配置記憶體位置


    for (int i = 0; i < num_vertex; i++) {
        visit[i] = 0;                                   // 初始化
    }
    for (int k = 100; k < 6100; k++)					// 開始前印出 arr[]
    {
        if (arr[k][0] > 0)
        {
            for (int u = 0; u < site; u++)
            {
                cout << arr[k][u] << " ";
            }
            cout << endl;
        }
    }

    int i = Start;
    for (int j = 0; j < num_vertex; j++) {              // 檢查所有Graph中的vertex都要被搜尋到

        if (visit[i] == 0 && arr[135][1] > 0) {
            int tmp = 135;                              // 從101開始搜尋 (101前一節點tmp==135)
            DFSVisit(i, all, arr, tmp, aft, cnditn);
        }
        i = j;                                          // j會把AdjList完整走過一遍, 確保所有vertex都被搜尋過
    }
}

void Graph::DFSVisit(int vertex, int all, int* arr[], int tmp, int* aft[], int cnditn) {
    // n7 暫存節線類型  // tmp為上游節點
    int n7 = 0;

    for (int k = 100; k < 6100; k++)
    {
        for (int u = 2; u < 180; u = u + 3)             // 以 tmp 出發搜尋下游節點
        {												// 將 k 點射至 u 點之流量減一
            if (arr[k][0] == tmp && arr[k][u - 1] == vertex && arr[k][u] > 0)
            {
                arr[k][u] = arr[k][u] - 1;
                n7 = arr[k][u + 1];						// 並暫存該節線類型至 n7
                //cout << tmp << " "<< vertex << "::" << arr[k][u]<<" ";
                break;
            }
        }
    }

    visit[vertex] = 1;                                  // 把vertex標記為已造訪
    cout << vertex << " -> ";

    int c = 1, r = 1;                                   // col & row of aft array
    c = (all - arr[135][2]);                            // c 紀錄第幾輛車或第幾位司機的路徑
    r = (vertex % 100);                                 // r 紀錄路徑各點
    buildAft(vertex, n7, aft, c, r, all);				// all為總車輛數或總司機數


    if (vertex == 135)
    {
        cout << " done!" << endl;
        cnditn = 0;
        for (int i = 0; i < num_vertex; i++) {          // 每分解完一次重置 visit[]
            visit[i] = 0;
        }
        if (arr[135][2] <= 0)                           // 檢查是否完成所有指派(循環節線)
        {
            for (int i = 0; i < num_vertex; i++) {
                visit[i] = 1;
            }
            for (int k = 1; k <= 2 * all; k++)          // 印出 aft[]
            {
                for (int u = 1; u <= 35; u++)
                {
                    //if (aft[k][u] > 0)
                    cout << aft[k][u] << " ";
                }
                cout << endl;
            }
        }
        //cin.get();
    }


    for (std::list<int>::iterator itr = adj[vertex].begin();     // for loop參數太長分成兩段
        itr != adj[vertex].end(); itr++) {
        if (visit[*itr] == 0)								   	 // 搜尋尚未造訪的 vertex
        {
            for (int k = 1; k < 180; k = k + 3)                  // 以 vertex 出發去搜尋 arr[] 下游流量 >0 的節點
            {
                //cout << "(" << *itr << arr[vertex][k] << "/" 
                //cout << vertex << "&" << arr[vertex][k + 1] << ")" << endl;
                if (arr[vertex][k + 1] > 0)
                {
                    if ((cnditn == 0) || (cnditn == 1 && arr[vertex][k + 2] != 91) ||
                        (cnditn == 2 && arr[vertex][k + 2] != 94 && arr[vertex][k + 2] != 91))
                    {                                            // if condition參數太長分成兩段
                        if (arr[vertex][k + 2] == 91)
                        {
                            cnditn = 1;
                        }
                        if (arr[vertex][k + 2] == 94)
                        {
                            cnditn = 2;
                        }
                        tmp = vertex;                            // tmp 存找到的節點並傳入 DFSVisit()
                        DFSVisit(arr[vertex][k], all, arr, tmp, aft, cnditn);
                        break;
                    }
                }
            }
        }
    }

}

void Graph::buildAft(int nodebuild, int type, int* aft[], int c, int r, int all) {
    int tmpa = 0; tmpa = all + c;
    int tmpb = 0; tmpb = 2 * all + c;
    if (aft[c][r] != 0)
    {
        r++;
        aft[c][r] = nodebuild;
        aft[tmpa][r] = type;
        //cout << "現在c是" << c << "r是" << r << endl;
    }
    if (aft[c][r] == 0)
    {
        aft[c][r] = nodebuild;
        aft[tmpa][r] = type;
        //cout << "現在c是" << c << "r是" << r << "type是" << type << endl;
    }

    if (nodebuild == 135 && aft[c][1] > 0)
    {
        c++;
    }
}

void Graph::countFlow(int N, int Z, int* aft[], int* aftz[], FILE* fp3, int* aftmp[]) {
    // 使用unordered_map來加速查找
    std::unordered_map<int, std::vector<std::pair<int, int>>> flow_map;

    // 構建flow_map以加速查找
    for (int q = 1; q <= Z; q++) {
        for (int p = 1; p < 50; p++) {
            if (aftz[q][p] > 0) {
                flow_map[aftz[q][p]].emplace_back(q, p);
            }
        }
    }

    // 更新aftz流量並計算aftmp
    for (int k = N + 1; k <= N * 2; k++) {
        for (int u = 1; u < 50; u++) {
            if (aft[k][u] == 91 || aft[k][u] == 94 || aft[k][u] == 95) {
                int tmpa = aft[k - N][u - 1];
                int tmpb = aft[k - N][u];
                aft[k][u] = 0;

                if (flow_map.find(tmpa) != flow_map.end()) {
                    for (auto& pair : flow_map[tmpa]) {
                        int q = pair.first;
                        int p = pair.second;

                        if (aftz[q][p + 1] == tmpb) {
                            if (aftz[q + 2 * Z][p + 1] < 7) {
                                aftz[q + 2 * Z][p + 1]++;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    // 計算aftmp
    for (int q = 1; q <= Z; q++) {
        for (int p = 1; p <= 35; p++) {
            aftmp[q][p] = aftz[q + 2 * Z][p] - aftmp[q][p];
        }
    }

    // 將結果寫入文件
    fprintf(fp3, "%s\n", "Array");
    for (int k = 1; k <= 2 * N; k++) {
        for (int u = 1; u <= 35; u++) {
            cout << aft[k][u] << " ";
            fprintf(fp3, "%d ", aft[k][u]);
        }
        fprintf(fp3, "\n ");
        cout << endl;
    }
    fprintf(fp3, "%s\n", "Z Array");
    for (int k = 1; k <= Z; k++) {
        for (int u = 1; u <= 35; u++) {
            cout << aftmp[k][u] << " ";
            fprintf(fp3, "%d ", aftmp[k][u]);
        }
        fprintf(fp3, "\n ");
        cout << endl;
    }
    fprintf(fp3, "%s\n", "Z total Array");
    for (int k = 1; k <= 3 * Z; k++) {
        for (int u = 1; u <= 35; u++) {
            cout << aftz[k][u] << " ";
            fprintf(fp3, "%d ", aftz[k][u]);
        }
        fprintf(fp3, "\n ");
        cout << endl;
    }
}

/*
void Graph::countFlow(int N, int Z, int* aft[], int* aftz[], FILE* fp3, int* aftmp[]) {
    int tmpa = 0; int tmpb = 0;
    for (int k = N + 1; k <= N * 2; k++)
    {
        for (int u = 1; u < 50; u++)
        {
            if (aft[k][u] == 91 || aft[k][u] == 94 || aft[k][u] == 95)
            {
                tmpa = aft[k - N][u - 1];
                tmpb = aft[k - N][u];
                aft[k][u] = 0;
                cout << tmpa << "現在搜尋" << tmpb << endl;

                for (int q = 1; q <= Z; q++)
                {
                    for (int p = 1; p < 50; p++)
                    {
                        if (aftz[q][p] == tmpa && aftz[q][p + 1] == tmpb)
                        {
                            //cout << "砍看我" << aftz[q][p] << aftz[q][p + 1] << endl;
                            if (aftz[q + 2 * Z][p + 1] < 7)
                            {
                                aftz[q + 2 * Z][p + 1]++;
                                break; break;
                            }
                            if (aftz[q + 2 * Z][p + 1] >= 7)
                            {
                                break;
                            }
                        }
                    }
                }
            }
        }
        cout << endl;
    }

    for (int q = 1; q <= Z; q++)
    {
        for (int p = 1; p <= 35; p++)
        {
            aftmp[q][p] = aftz[q + 2 * Z][p] - aftmp[q][p];
        }
    }

    fprintf(fp3, "%s\n", "Array");
    for (int k = 1; k <= 2 * N; k++)
    {
        for (int u = 1; u <= 35; u++)
        {
            cout << aft[k][u] << " ";
            fprintf(fp3, "%d ", aft[k][u]);
        }
        fprintf(fp3, "\n ");
        cout << endl;
    }
    fprintf(fp3, "%s\n", "Z Array");
    for (int k = 1; k <= Z; k++)
    {
        for (int u = 1; u <= 35; u++)
        {
            cout << aftmp[k][u] << " ";
            fprintf(fp3, "%d ", aftmp[k][u]);
        }
        fprintf(fp3, "\n ");
        cout << endl;
    }
    fprintf(fp3, "%s\n", "Z total Array");
    for (int k = 1; k <= 3 * Z; k++)
    {
        for (int u = 1; u <= 35; u++)
        {
            cout << aftz[k][u] << " ";
            fprintf(fp3, "%d ", aftz[k][u]);
        }
        fprintf(fp3, "\n ");
        cout << endl;
    }
}
*/

int main()
{
    int line = 0;
    cout << "arc_flow_S.txt的行數為??" << endl;
    cin >> line;

    Graph g1(6100);
    Graph g2(6100);
    Graph g3(6100);
    char s1[10], s6[10], s7[10], s2[10], s4[10];
    int n2[10000], n3[10000], n4[10000], n5[10000], flow[10000], n7;
    // file pointer
    FILE* fp; FILE* fp2;  FILE* fp3;
    int cnditn = 0;                                     // 0:default; 1:departed; 2:backed;

    char* net_type[10000];
    char* arc_type[10000];

    int** arrz = new int* [6100];                       // 開陣列 arr[][]
    int** arrx = new int* [6100];                       // [節點0101~6035][下游節點/流量/類型]
    int** arry = new int* [6100];						// [地點/時間]
    for (int i = 0; i < 6100; i++) {
        arrz[i] = new int[180];
        arrx[i] = new int[180];
        arry[i] = new int[180];
    }
    for (int i = 0; i < 6100; i++)                      // 初始化 arr[3100][180]
    {
        for (int j = 0; j < 180; j++) {
            arrz[i][j] = 0;
            arrx[i][j] = 0;
            arry[i][j] = 0;
        }
    }

    int** aftz = new int* [200];                        // 開陣列 aft[][]
    int** aftx = new int* [200];                        // [每單位路徑/路徑類型][路徑]
    int** afty = new int* [200];
    for (int i = 0; i < 200; i++) {
        aftz[i] = new int[50];
        aftx[i] = new int[50];
        afty[i] = new int[50];
    }
    for (int i = 0; i < 200; i++)                       // 初始化 aft[100][50]
    {
        for (int j = 0; j < 50; j++) {
            aftz[i][j] = 0;
            aftx[i][j] = 0;
            afty[i][j] = 0;
        }
    }

    // Open file securely
    fopen_s(&fp, "output/arc_flow_S.txt", "r");
    fopen_s(&fp2, "output/arc_flow_S_after.txt", "w+");
    fopen_s(&fp3, "output/count_flow_result.txt", "w+");

    rewind(fp);
    int i = 1; int Z = 0; int X = 0; int Y = 0;
    int m = 1; int n = 1;
    do {
        // Using fscanf_s
        fscanf_s(fp, "%1s", s1, sizeof(s1));
        fscanf_s(fp, "%4d", &n2[i], sizeof(n2[i]));
        // fscanf_s(fp, "%2d", &n3[i], sizeof(n3[i]));
        fscanf_s(fp, "%4d", &n4[i], sizeof(n4[i]));
        // fscanf_s(fp, "%2d", &n5[i], sizeof(n5[i]));
        fscanf_s(fp, "%1s", s6, sizeof(s6));
        fscanf_s(fp, "%1s", s7, sizeof(s6));
        fscanf_s(fp, "%3d", &flow[i], sizeof(flow[i]));

        //printf("String |%1s|\n", s1);
        //printf("Node |%4d|\n", n2[i]);
        // printf("Node |%2d|\n", n3[i]);
        //printf("Node |%4d|\n", n4[i]);
        // printf("Node |%2d|\n", n5[i]);
        //printf("String |%2s|\n", s6);
        //printf("Flow |%3d|\n", flow[i]);

        fprintf(fp2, "%1s %4d %4d %1s %1s %3d\n", s1, n2[i], n4[i], s6, s7, flow[i]);

        if (*s7 == 'A') n7 = 91;
        if (*s7 == 'B') n7 = 92;
        if (*s7 == 'C') n7 = 93;
        if (*s7 == 'P') n7 = 93;
        if (*s7 == 'D') n7 = 94;
        if (*s7 == 'E') n7 = 95;
        if (*s7 == 'F') n7 = 96;

        if (*s1 == 'z' && n2[i] == 101) Z = Z + flow[i];        // 計數總量
        if (*s1 == 'x' && n2[i] == 101) X = X + flow[i];
        if (*s1 == 'y' && n2[i] == 101) Y = Y + flow[i];


        if (*s1 == 'z') {                                // 建立節線
            g1.addEdge(n2[i], n4[i]);
            arrz[n2[i]][0] = n2[i];                      // n2[i] 射至 n4[i]

            int j = 0;
            while (arrz[n2[i]][j] > 0)
            {
                j++;
            }
            arrz[n2[i]][j] = n4[i];
            arrz[n2[i]][j + 1] = flow[i];
            arrz[n2[i]][j + 2] = n7;

        }
        if (*s1 == 'x') {                                // 建立節線
            g2.addEdge(n2[i], n4[i]);
            arrx[n2[i]][0] = n2[i];                      // n2[i] 射至 n4[i]

            int j = 0;
            while (arrx[n2[i]][j] > 0)
            {
                j++;
            }
            arrx[n2[i]][j] = n4[i];
            arrx[n2[i]][j + 1] = flow[i];
            arrx[n2[i]][j + 2] = n7;

        }
        if (*s1 == 'y') {                                // 建立節線
            g3.addEdge(n2[i], n4[i]);
            arry[n2[i]][0] = n2[i];                      // n2[i] 射至 n4[i]

            int j = 0;
            while (arry[n2[i]][j] > 0)
            {
                j++;
            }
            arry[n2[i]][j] = n4[i];
            arry[n2[i]][j + 1] = flow[i];
            arry[n2[i]][j + 2] = n7;
        }

        i++;

    } while (i <= line);                                 // 讀檔至記事本結尾

    arrz[135][0] = 135; arrz[135][1] = 101; arrz[135][2] = Z; arrz[135][3] = 90;    // 循環節線 (起迄,流量,類型)
    arrx[135][0] = 135; arrx[135][1] = 101; arrx[135][2] = X; arrx[135][3] = 90;
    arry[135][0] = 135; arry[135][1] = 101; arry[135][2] = Y; arry[135][3] = 90;
    fclose(fp);
    fclose(fp2);


    g1.addEdge(135, 101);                                // 循環節線 (迄空迄時,起空起時)
    cout << "共" << Z << "次Z DFS" << endl;
    g1.DFS(101, Z, arrz, aftz, cnditn);                  //從0101起空起時開始搜尋

    g2.addEdge(135, 101);                                //循環節線 (迄空迄時,起空起時)
    cout << "共" << X << "次X DFS" << endl;
    g2.DFS(101, X, arrx, aftx, cnditn);                  //從0101起空起時開始搜尋

    g3.addEdge(135, 101);                                //循環節線 (迄空迄時,起空起時)
    cout << "共" << Y << "次Y DFS" << endl;
    g3.DFS(101, Y, arry, afty, cnditn);                  //從0101起空起時開始搜尋


    int** aftmp = new int* [20];                         // 開陣列 aftmp[車輛][路徑] 暫存
    for (int i = 0; i < 20; i++) {
        aftmp[i] = new int[50];
    }
    for (int i = 0; i < 20; i++)                         // 初始化 aftmp[][]
    {
        for (int j = 0; j < 50; j++) {
            aftmp[i][j] = 0;
        }
    }

    g1.countFlow(X, Z, aftx, aftz, fp3, aftmp, cnditn);
    g1.countFlow(Y, Z, afty, aftz, fp3, aftmp, cnditn);


    return 0;
}

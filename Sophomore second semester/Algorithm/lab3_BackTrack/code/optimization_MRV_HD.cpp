#include <iostream>
#include <cstdio>
#include <vector>
#include <Windows.h>
#include <ctime>

using namespace std;

const int N = 455, M = 100005, C = 30;

int n, m, c;
bool right_test = true;
int ans;                 // the final ans
vector<int> edge[N];     // edges of vertex i
bool color_list[N][C];   // color_list[i][j] is false means the vertex i can use color j
int color_num[N];        // color_num[i] is the number of colors that vertex i can use
int cur_color[N];        // cur_color[i] means the current color of i(if curcolor[i] is 0, means we haven't painted i)
int d[N];                // the degree of vertex i 
vector<pair<int, int> > all_edge;
int pre[N][C];
int num;

LARGE_INTEGER nFreq;
LARGE_INTEGER st, et;

int get_next_vertex(int u)
{
    int res = n + 1, maxD = 0, minV = c;
    for (int i = 1; i <= n; i ++ ) 
    {
        if (i == u || cur_color[i]) continue;
        if ((color_num[i] < minV) || (color_num[i] == minV && d[i] > maxD))
        {
            res = i;
            maxD = d[i];
            minV = color_num[i];
        }
    }
    return res;
}

void dfs(int u, int depth)
{
    if (depth > n){
        ans ++;
        // QueryPerformanceCounter(&et);
        // printf("%.6fms", (double)(et.QuadPart - st.QuadPart)/(double)nFreq.QuadPart * 1000);
        // exit(0);
        return;
    }
    for (int i = 1; i <= c; i ++ )
    {
        if (color_list[u][i]) continue;
        cur_color[u] = i;
        color_num[u] --;
        color_list[u][i] = true;

        for (int j = 0; j < edge[u].size(); j ++ )
        {
            int v = edge[u][j];
            if (cur_color[v]) continue;
            d[v] --;
            if (!color_list[v][i])
            {
                color_num[v] --;
                color_list[v][i] = true;
                pre[v][i] = u;
            }
        }

        dfs(get_next_vertex(u), depth + 1);

        for (int j = 0; j < edge[u].size(); j ++ )
        {
            int v = edge[u][j];
            if (cur_color[v]) continue;
            d[v] ++;
            if (pre[v][i] == u)
            {
                color_num[v] ++;
                color_list[v][i] = false;
                pre[v][i] = 0;
            }
        }
        cur_color[u] = 0;
        color_num[u] ++;
        color_list[u][i] = false;
    }
}

int main()
{
    freopen("le450_5a.col", "r", stdin);
    cin >> n >> m >> c;
    cout << n << " " << m << " " << c << endl;
    for (int i = 1; i <= m; i ++ )
    {
        char ch;
        int u, v;
        cin >> ch >> u >> v;
        all_edge.push_back({u, v});
        // add(u, v);
        // add(v, u);
    }
    double tot_time = 0;
    int T = 20;

    // while (T --)
    // {
    //     cout << T << endl;
        for (int i = 1; i <= n; i ++ )
        {
            edge[i].clear();
            color_num[i] = c, d[i] = 0;
            for (int j = 1; j <= c; j ++ )
                color_list[i][j] = false;
        }

        for (auto t : all_edge)
        {
            edge[t.first].push_back(t.second);
            edge[t.second].push_back(t.first);
            d[t.first] ++;
            d[t.second] ++;
        }
            
        QueryPerformanceFrequency(&nFreq);
        QueryPerformanceCounter(&st);

        dfs(get_next_vertex(0), 1);

        QueryPerformanceCounter(&et);

        tot_time += (double)(et.QuadPart - st.QuadPart)/(double)nFreq.QuadPart;
    
    // }
    
    printf("average time: %.6fs\n", tot_time / 20);
    printf("%d\n", ans);


    // right test
    // if (right_test) puts("The result of the algorithm is right!");
    // else puts("The result of the algorithm is wrong!");

    return 0;
}
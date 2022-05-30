#include <iostream>
#include <cstdio>
#include <vector>
#include <Windows.h>
#include <ctime>

typedef long long LL;
using namespace std;

const int N = 455, M = 100005, C = 30;

int n;                   // the number of vertices
int m;                   // the number of edges
int c;                   // the number of colors
bool right_test = true;
int ans;                 // the final ans
vector<int> edge[N];     // edges of vertex i
bool color_list[N][C];   // color_list[i][j] is false means the vertex i can use color j
int color_num[N];        // color_num[i] is the number of colors that vertex i can use
int cur_color[N];        // cur_color[i] means the current color of i(if curcolor[i] is 0, means we haven't painted i)
int d[N];                // the degree of vertex i 
int color_unused;        // the number of colors unused
int color_time[C];       // times of color i used
int pre[N][C];          
int num;
LL pow = 1;

LARGE_INTEGER nFreq;
LARGE_INTEGER st, et;

int get_next_vertex()
{
    int res = n + 1, maxD = 0, minV = c;
    for (int i = 1; i <= n; i ++ ) 
    {
        if (cur_color[i]) continue;
        if ((color_num[i] < minV) || (color_num[i] == minV && d[i] > maxD))
        {
            res = i;
            maxD = d[i];
            minV = color_num[i];
        }
    }
    return res;
}

int get_next_vertex2()
{
    for (int i = 1; i <= n; i ++ )
        if (!cur_color[i]) return i;
    return n + 1;
}

void dfs(int u, int depth)
{
    // cout << depth << endl;
    if (depth > n) 
    {
        // exit(0);
        ans ++;
        QueryPerformanceCounter(&et);
        printf("%.6fms", (double)(et.QuadPart - st.QuadPart)/(double)nFreq.QuadPart * 1000);
        exit(0);
        return;
    }
    int temp = 0;
    for (int i = 1; i <= c; i ++ )
    {
        if (color_time[i] == 0)
        {
            if (temp) continue;
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

            temp = color_unused;
            color_time[i] ++, color_unused --;
            dfs(get_next_vertex(), depth + 1);
            color_time[i] --, color_unused ++;

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
        else
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

            dfs(get_next_vertex(), depth + 1);

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
    return;
}

int main()
{
    freopen("le450_5a.col", "r", stdin);
    cin >> n >> m;
    c = 22;
    cout << n << " " << m << " " << c << endl;
    for (int i = 1; i <= n; i ++ ) color_num[i] = c;
    color_unused = c;
    for (int i = 1; i <= c; i ++ ) pow *= i;
    for (int i = 1; i <= m; i ++ )
    {
        char ch;
        int u, v;
        cin >> ch >> u >> v;

        // add(u, v);
        // add(v, u);

        edge[u].push_back(v);
        edge[v].push_back(u);
        
        d[u] ++, d[v] ++;
    }
    double tot_time = 0;
    int T = 20;

    while (T --)
    {
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&st);

    // srand(time(0));
    dfs(get_next_vertex(), 1);
    // ans = dfs(rand() % n + 1, 1);

    QueryPerformanceCounter(&et);

    tot_time += (double)(et.QuadPart - st.QuadPart)/(double)nFreq.QuadPart;
    
    }
    
    printf("average time: %.6fms\n", tot_time * 1000 / 20);
    printf("%d\n", ans);


    // right test
    // if (right_test) puts("The result of the algorithm is right!");
    // else puts("The result of the algorithm is wrong!");

    return 0;
}
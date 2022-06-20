#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <Windows.h>
#include <ctime>
#include <vector>
#include <map>

using namespace std;

const int N = 10000005;

int n, m;
struct edge
{
    int from, to, next;
}e[N << 1];
int head[N], cnt = -1;
int dep[N], fa[N];
bool vis[N];
bool isTreeEdge[N << 1];
bool isInCircle[N << 1];
map<int, int> TreeAdj[N];
int f[N];

void add(int u, int v)
{
    e[++ cnt] = {u, v, head[u]};
    head[u] = cnt;
}

void dfs(int u, int ff)
{
    fa[u] = ff;
    dep[u] = dep[ff] + 1;
    vis[u] = true;
    for (int i = head[u]; ~i; i = e[i].next)
    {
        int v = e[i].to;
        if (vis[v]) continue;
        isTreeEdge[i] = true;
        isTreeEdge[i ^ 1] = true;
        TreeAdj[u][v] = i;
        TreeAdj[v][u] = i ^ 1;
        dfs(v, u);
    }
}

int getf(int x)
{
    return x == f[x] ? x : f[x] = getf(f[x]);
}

void Union(int x, int y)
{
    x = getf(x), y = getf(y);
    if (x == y) return;
    if (dep[x] < dep[y]) swap(x, y);
    f[x] = y;
}

int LCA()
{
    int Connect = 0;
    for (int i = 1; i <= n; i ++ )
        if (!vis[i])
            dfs(i, 0), Connect ++;

    for (int i = 1; i <= n; i ++ ) f[i] = i;

    for (int i = 0; i <= cnt; i += 2)
        if (!isTreeEdge[i])
        {
            int u = e[i].from, v = e[i].to;
            int x = getf(u), y = getf(v);

            vector<int> path;
            while (x != y)
            {
                if (dep[x] < dep[y]) swap(x, y);
                path.push_back(x);
                isInCircle[TreeAdj[x][fa[x]]] = true;
                isInCircle[TreeAdj[fa[x]][x]] = true;
                x = getf(fa[x]);
            }

            for (auto p : path)
                Union(p, x);
        }

    int ans = 0;
    for (int i = 0; i <= cnt; i ++ )
        if (isTreeEdge[i] && !isInCircle[i])
            ans ++;
            // printf("%dth Bridge Edge: %d %d\n", ++ans, e[i].from, e[i].to);

    return ans;
}

int main()
{
    freopen("5000_300000.txt", "r", stdin);

    memset(head, -1, sizeof head);
    scanf("%d%d", &n, &m);
    printf("%d %d\n", n, m);
    for (int i = 1; i <= m; i ++ )
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }

    LARGE_INTEGER nFreq;
    LARGE_INTEGER st, et;
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&st);

    int ans = LCA();

    QueryPerformanceCounter(&et);

    double tot_time = (double)(et.QuadPart - st.QuadPart)/(double)nFreq.QuadPart;

    printf("ans = %d  average = %.6fms\n", ans, tot_time * 1000);

    return 0;
}

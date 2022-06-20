#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <Windows.h>
#include <ctime>

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
        dfs(v, u);
    }
}

void dfs_(int u)
{
    for (int i = head[u]; ~i; i = e[i].next)
    {
        int v = e[i].to;
        if (fa[v] != u) continue;
        dfs_(v);
        f[u] += f[v];
    }
}

int Diff()
{
    for (int i = 1; i <= n; i ++ )
        if (!vis[i])
            dfs(i, 0);

    for (int i = 0; i <= cnt; i ++ )
        if (!isTreeEdge[i])
        {
            int u = e[i].from, v = e[i].to;
            if (dep[u] < dep[v]) swap(u, v);
            f[u] ++, f[v] --;
        }

    for (int i = 1; i <= n; i ++ )
        if (!fa[i])
            dfs_(i);

    int ans = 0;
    for (int i = 1; i <= n; i ++ )
        if (fa[i] && !f[i])
            ans ++;

    return ans;
}

int main()
{
    freopen("5000_500000.txt", "r", stdin);

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

    int ans = Diff();

    QueryPerformanceCounter(&et);

    double tot_time = (double)(et.QuadPart - st.QuadPart)/(double)nFreq.QuadPart;

    printf("ans = %d  average = %.6fms\n", ans, tot_time * 1000);

    return 0;
}

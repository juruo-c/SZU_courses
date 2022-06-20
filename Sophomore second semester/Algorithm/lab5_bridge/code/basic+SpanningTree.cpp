#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <ctime>
#include <Windows.h>

using namespace std;

const int N = 1000005, M = 10000005;

int n, m;
struct edge
{
	int from, to, next;
}e[M << 1];
int head[N], cnt = -1;
bool vis[N];
bool isDelete[M << 1];
bool isTreeEdge[M << 1];

void add(int u, int v)
{
	e[++ cnt] = {u, v, head[u]};
	head[u] = cnt;
}

void dfs(int u)
{	
	vis[u] = true;
	for (int i = head[u]; ~i; i = e[i].next)
	{
		if (isDelete[i]) continue;
		int v = e[i].to;
		if (!vis[v])
			dfs(v);
	}
}

int CountConections()
{
	int ans = 0;
	memset(vis, false, sizeof vis);
	for (int i = 1; i <= n; i ++ )
		if (!vis[i])
			dfs(i), ans ++;
	return ans;
}

int Basic1()
{
	int p = CountConections();

	int ans = 0;
	for (int i = 0; i <= cnt; i += 2 )
	{
		if (!isTreeEdge[i]) continue;
		isDelete[i] = isDelete[i ^ 1] = true;

		int p_ = CountConections();

		if (p_ > p) ans ++;

		isDelete[i] = isDelete[i ^ 1] = false;
	}

	return ans;
}

bool dfs_(int u, int tar)
{
	vis[u] = true;
	if (u == tar) return true;
	for (int i = head[u]; ~i; i = e[i].next)
	{
		if (isDelete[i]) continue;
		int v = e[i].to;
		bool fl = false;
		if (!vis[v])
			fl = dfs_(v, tar);
		if (fl) return true;
	}
	return false;
}

int Basic2()
{
	int ans = 0;
	for (int i = 0; i <= cnt; i += 2 )
	{
		if (!isTreeEdge[i]) continue;
		isDelete[i] = isDelete[i ^ 1] = true;

		memset(vis, false, sizeof vis);
		int u = e[i].from, v = e[i].to;
		if (!dfs_(u, v)) 
			ans ++;

		isDelete[i] = isDelete[i ^ 1] = false;
	}

	return ans;
}

void getTree(int u)
{
	vis[u] = true;
	for (int i = head[u]; ~i; i = e[i].next)
	{
		int v = e[i].to;
		if (!vis[v])
		{
			isTreeEdge[i] = isTreeEdge[i ^ 1] = true;
			getTree(v);
		}
	}
}

int Basic_Spanning_Tree()
{
	memset(vis, false, sizeof vis);
	for (int i = 1; i <= n; i ++ )
		if (!vis[i])
			getTree(i);
	return Basic1();
}

int main()
{
	freopen("10000_10000.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	printf("%d %d\n", n, m);

	memset(head, -1, sizeof head);
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

    int ans = Basic_Spanning_Tree();

    QueryPerformanceCounter(&et);

    double tot_time = (double)(et.QuadPart - st.QuadPart)/(double)nFreq.QuadPart;

    printf("ans = %d  average = %.6fms\n", ans, tot_time);

	return 0;
}
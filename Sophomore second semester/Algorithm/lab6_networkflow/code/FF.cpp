#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <queue>

using namespace std;

typedef long long LL;

const int N = 205, M = 5005;
const LL INF = 0xffffffff;

struct Edge
{
	int from, to, next;
	LL cap, flow;  // the from vertex, the to vertex, the capacity, the current flow
}e[M << 1];
int head[N], cnt = -1;

int n, k, c;		  // number of vertices and edges
int s, t;	      // source vertex and target vertex
LL f[N];		  // current maximum flow to vertex i
int pre[N];		  // the pre edge of vertex i

void add(int u, int v, int c)
{
	e[++ cnt] = {u, v, head[u], c, 0};
	head[u] = cnt;
	e[++ cnt] = {v, u, head[v], 0, 0};
	head[v] = cnt;
}

bool dfs(int u)
{
	bool fl = false;
	for (int i = head[u]; ~i; i = e[i].next)
	{
		int v = e[i].to;
		if (pre[v] != -1 || e[i].cap == 0) continue;
		f[v] = min(f[u], e[i].cap);
		pre[v] = i;
		if (v == t) return true;
		fl |= dfs(v);
		if (fl) return true;
	}
	return false;
}

void update()
{
	for (int i = t; i != s; i = e[pre[i]].from)
	{
		e[pre[i]].flow += f[t], e[pre[i] ^ 1].flow -= f[t];
		e[pre[i]].cap -= f[t], e[pre[i] ^ 1].cap += f[t];
	}
}

LL EK()
{
	LL ans = 0;
	while (true)
	{
		for (int i = 1; i <= n; i ++ ) pre[i] = -1, f[i] = INF;
		if (!dfs(s)) break;
		ans += f[t];
		update();
	}

	return ans;
}

int main()
{
	scanf("%d%d%d%d", &n, &m, &s, &t);
	memset(head, -1, sizeof head);
	for (int i = 1; i <= m; i ++ )
	{
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c);
		add(u, v, c);
	}

	printf("%lld\n", EK());

	return 0;
}
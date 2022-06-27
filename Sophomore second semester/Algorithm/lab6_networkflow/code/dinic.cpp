#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <queue>
#include <map>
#include <set>
#include <Windows.h>

using namespace std;

typedef long long LL;

const int N = 1005, M = 5000005;
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
int level[N];
int cur[N];
map<int, int> DateToHoliday;

void add(int u, int v, int c)
{
	e[++ cnt] = {u, v, head[u], c, 0};
	head[u] = cnt;
	e[++ cnt] = {v, u, head[v], 0, 0};
	head[v] = cnt;
}

bool bfs()
{
	for (int i = 1; i <= n; i ++ ) level[i] = -1;
	level[s] = 0;

	queue<int> q;
	q.push(s);
	while(!q.empty())
	{
		int u = q.front();
		q.pop();

		for (int i = head[u]; ~i; i = e[i].next){
			int v = e[i].to;
			if (level[v] != -1 || e[i].cap == 0) continue;
			level[v] = level[u] + 1;
			if (v == t) return true;
			q.push(v);
		}
	}
	return false;
}

LL dfs(int u, LL flow)
{
	if (u == t) return flow;
	LL left = flow;
	for (int& i = cur[u]; ~i; i = e[i].next)
	{
		int v = e[i].to;
		if (e[i].cap == 0 || level[v] != level[u] + 1) continue;
		LL f = dfs(v, min(left, e[i].cap));
		e[i].cap -= f, e[i].flow += f;
		e[i ^ 1].cap += f, e[i ^ 1].flow -= f;
		left -= f;
		if (!left) return flow;
	}
	return flow - left;
}

LL Dinic()
{
	LL ans = 0;
	while (bfs())
	{
		for (int i = 1; i <= n; i ++ ) cur[i] = head[i];
		ans += dfs(s, INF);
	}

	return ans;
}

int main()
{
	c = 5;
	freopen("100_50.txt", "r", stdin);
	scanf("%d%d", &n, &k);
	printf("%d %d %d\n", n, k, c);
	memset(head, -1, sizeof head);
	s = 0, t = n + n * k;
	for (int i = 1; i <= n; i ++ ) add(s, i, c);
	int dsum = 0;
	for (int i = 1; i <= k; i ++ )
	{
		int h;scanf("%d", &h);
		t += h;
		dsum += h;
		for (int j = 0; j < h; j ++ )
		{
			int d;
			scanf("%d", &d);
			DateToHoliday[d] = i;
		}
	}
	for (int i = 1; i <= n; i ++ )
	{
		int ki;scanf("%d", &ki);
		set<int> Holiday;
		vector<int> Date[N];
		for (int j = 0; j < ki; j ++ )
		{
			int d;scanf("%d", &d);
			Holiday.insert(DateToHoliday[d]);
			Date[DateToHoliday[d]].push_back(d);
		}
		for (auto holiday : Holiday)
		{
			add(i, n + (i - 1) * k + holiday, 1);
			for (auto date : Date[holiday])
				add(n + (i - 1) * k + holiday, n + n * k + date, 1);
		}
	}
	t ++;
	for (int i = 1; i <= dsum; i ++ )
		add(n + n * k + i, t, 1);

	LARGE_INTEGER nFreq;
    LARGE_INTEGER st, et;
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&st);

	LL ans = Dinic();

	QueryPerformanceCounter(&et);

    double tot_time = (double)(et.QuadPart - st.QuadPart)/(double)nFreq.QuadPart;

    printf("ans = %d  average = %.6fms\n", ans, tot_time * 1000);
	// path(dsum);

	return 0;
}
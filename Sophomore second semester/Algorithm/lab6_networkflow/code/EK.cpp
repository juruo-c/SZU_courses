#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <queue>
#include <map>
#include <set>
#include <Windows.h>
#include <ctime>

using namespace std;

typedef long long LL;

const int N = 1001, M = 1000005;
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
map<int, int> DateToHoliday;
map<int, int> Doctor;
bool vis[N];

void add(int u, int v, int c)
{
	e[++ cnt] = {u, v, head[u], c, 0};
	head[u] = cnt;
	e[++ cnt] = {v, u, head[v], 0, 0};
	head[v] = cnt;
}

bool bfs()
{
	for (int i = 0; i <= t; i ++ ) pre[i] = -1, f[i] = INF;
	
	queue<int> q;
	q.push(s);
	pre[s] = s;
	while(!q.empty())
	{
		int u = q.front(); q.pop();
		for (int i = head[u]; ~i; i = e[i].next)
		{
			int v = e[i].to;
			if (pre[v] != -1 || e[i].cap == 0) continue;
			pre[v] = i;
			f[v] = min(f[u], e[i].cap);
			if (v == t) return true;
			q.push(v);
		}
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
	while (bfs())
	{
		ans += f[t];
		update();
	}

	return ans;
}

void dfs_(int u, int doctor)
{
	vis[u] = true;
	if (u > n + n * k)
	{
		Doctor[u] = doctor;
		return;
	}
	for (int i = head[u]; ~i; i = e[i].next)
	{
		if (i & 1) continue;
		int v = e[i].to;
		if (vis[v] || !e[i].flow) continue;
		dfs_(v, doctor);
	}
}

void path(int dsum)
{
	for (int i = 1; i <= n; i ++ )
		dfs_(i, i);

	for (int i = 1; i <= dsum; i ++ )
		printf("duty doctor of date %d: Doctor %d\n", i, Doctor[n + n * k + i]);
}

int main()
{\
	// freopen("100_50.txt", "r", stdin);
	scanf("%d%d%d", &n, &k, &c);
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

	for (int i = 0; i <= cnt; i += 2)
		printf("%d %d %d\n", e[i].from, e[i].to, e[i].cap);

	LARGE_INTEGER nFreq;
    LARGE_INTEGER st, et;
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&st);

	LL ans = EK();

	QueryPerformanceCounter(&et);

    double tot_time = (double)(et.QuadPart - st.QuadPart)/(double)nFreq.QuadPart;

    printf("ans = %d  average = %.6fms\n", ans, tot_time * 1000);

    printf("%d\n", ans);
	path(dsum);

	return 0;
}

/*
3 2 2
2 1 2
1 3
2 1 3
1 3
2 1 2
*/
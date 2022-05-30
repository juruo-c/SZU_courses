// Using the Hungarian Algorithm to Solve the Bipartite Graph Maximum Matching Problem
// input: n --the number of vertices on left
//		  m --the number of vertices on right
//		  edges_cnt --the number of edges
//		  edges[i] -- the edges of vertex i
// ouput: ans -- the number of matches
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int N = 1005, M = 1000005;

int n; // the number of vertices on left
int m; // the number of vertices on right
int edges_cnt; // the number of edges

vector<int> edges[N]; // the edges of vertex i, use adjacency list to store

int match[N];
bool vis[N];

bool dfs(int u) // find extend road, if found return true, else return false
{
	if (vis[u]) return false;
	vis[u] = true;
	for (int i = 0; i < edges[u].size(); i ++ )
	{
		int v = edges[u][i];
		if (!match[v] || dfs(match[v]))
		{
			match[v] = u;
			return true;
		}	
	}
	return false;
}

int main()
{
	scanf("%d%d%d", &n, &m, &edges_cnt);
	for (int i = 1; i <= edges_cnt; i ++ )
	{
		int u, v;scanf("%d%d", &u, &v);
		edges[u].push_back(v + n);
		edges[v + n].push_back(u);	
	}
	int ans = 0;
	for (int i = 1; i <= n; i ++ )
	{
		memset(vis, false, sizeof vis);
		if (dfs(i)) ans ++;
	}
	printf("%d\n", ans);
	return 0;
}
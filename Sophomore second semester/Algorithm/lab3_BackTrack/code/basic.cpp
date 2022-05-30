#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <Windows.h>
#include <ctime>

using namespace std;

const int N = 100005;

int n;	// number of vertices
int m;  // number of edges
int c;	// number of colors
int Ans;
int ans;
bool right_test = true;
vector<int> edge[N];

int col[N];

void add(int u, int v)
{
	edge[u].push_back(v);
}

void dfs(int u)
{
	if (u > n) 
	{
		// right test
		// if (right_test)
		// {
		// 	for (int i = 1; i <= n; i ++ )
		// 		for (int j = 0; j < edge[i].size(); j ++ )
		// 		{
		// 			int v = edge[i][j];
		// 			if (col[i] == col[v])
		// 			{
		// 				right_test = false;
		// 				break;
		// 			}
		// 		}
		// }
		
		// record the solution
		ans ++;
		return;
	}
	for (int i = 1; i <= c; i ++ )
	{
		bool flag = true;
		for (int j = 0; j < edge[u].size(); j ++ )
		{
			int v = edge[u][j];
			if (col[v] == i) 
			{
				flag = false;
				break;
			}
		}
		if (flag)
		{
			col[u] = i;
			dfs(u + 1);
			col[u] = 0;
		}
	}
}

int main()
{
	freopen("le450_25a.txt", "r", stdin);
	scanf("%d%d%d", &n, &m, &c);
	cout << n << m << c << endl;
	for (int i = 1; i <= m; i ++ )
	{
		char e;
		int u, v;
		scanf("\n%c%d%d", &e, &u, &v);
		add(u, v);
		add(v, u);
	}
	// n = 9;
	// c = 4; 
	// add(1, 4);add(4, 1);
	// add(1, 3);add(3, 1);
	// add(1, 2);add(2, 1);
	// add(2, 4);add(4, 2);
	// add(2, 3);add(3, 2);
	// add(3, 4);add(4, 3);
	// add(4, 5);add(5, 4);
	// add(2, 5);add(5, 2);
	// add(4, 7);add(7, 4);
	// add(4, 6);add(6, 4);
	// add(5, 6);add(6, 5);
	// add(6, 7);add(7, 6);
	// add(5, 9);add(9, 5);
	// add(6, 9);add(9, 6);
	// add(7, 8);add(8, 7);
	// add(6, 8);add(8, 6);
	// add(8, 9);add(9, 8);

	double tot_time = 0;
	int T = 20;

	while (T --)
	{
		ans = 0;
		LARGE_INTEGER nFreq;
		LARGE_INTEGER st, et;
	  	QueryPerformanceFrequency(&nFreq);
	  	QueryPerformanceCounter(&st);

		dfs(1);
		
		QueryPerformanceCounter(&et);

		tot_time += (double)(et.QuadPart - st.QuadPart)/(double)nFreq.QuadPart;
	
	}
	
	printf("average time: %.6fms\n", tot_time / 20);
	printf("%d\n", ans);

	// right test
	// if (right_test) puts("The result of the algorithm is right!");
	// else puts("The result of the algorithm is wrong!");

	return 0;
}

// 450 5714 5

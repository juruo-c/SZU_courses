#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <Windows.h>
#include <ctime>

using namespace std;

const int N = 10005;

int n;
int golds[N];
int sum[N];
int f[N][N];
int nxt[N][N];

int dfs(int l, int r) 
{
	if (l == r) 
		return golds[l];
	if (f[l][r] != -1) return f[l][r];

	int lans = golds[l] + sum[r] - sum[l] - dfs(l + 1, r), rans = golds[r] + sum[r - 1] - sum[l - 1] - dfs(l, r - 1);
	if (lans > rans) 
	{
		nxt[l][r] = 0;
		f[l][r] = lans;
	}
	else 
	{
		nxt[l][r] = 1;
		f[l][r] = rans;
	}

	return f[l][r];
}

void printPath()
{
	int l = 1, r = n;
	int who = 0;
	while (nxt[l][r] != -1)
	{
		if (nxt[l][r] == 0)
		{
			if (!who)
				printf("%d ", l);
			l ++;
		}
		else
		{
			if (!who)
				printf("%d ", r);
			r --;
		}
		who ^= 1;
	}
	puts("");
}

int main()
{
	freopen("5000.txt", "r", stdin);
	scanf("%d", &n);
	double tot_time = 0;
	int T = 20;
	while (T --)
	{
		for (int i = 1; i <= n; i ++ )
			scanf("%d", &golds[i]);

		for (int i = 1; i <= n; i ++ )
			sum[i] = sum[i - 1] + golds[i];

		memset(nxt, -1, sizeof nxt);
		memset(f, -1, sizeof f);
		// printf("%d\n", dfs(1, n));

		LARGE_INTEGER nFreq;
		LARGE_INTEGER st, et;
		QueryPerformanceFrequency(&nFreq);
        QueryPerformanceCounter(&st);

		dfs(1, n);

		QueryPerformanceCounter(&et);

        tot_time += (double)(et.QuadPart - st.QuadPart)/(double)nFreq.QuadPart;

		// printPath();
	}
	printf("average time: %.6fms\n", tot_time * 1000 / 20);	
	// reverse(A.begin(), A.end());
	// for (auto a : A)
	// 	printf("%d ", a);
	// puts("");

	return 0;
}
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
int nxt[N][N];

int dfs(int l, int r) 
{
	if (l == r) 
		return golds[l];

	int lans = golds[l] + sum[r] - sum[l] - dfs(l + 1, r), rans = golds[r] + sum[r - 1] - sum[l - 1] - dfs(l, r - 1);
	if (lans > rans) 
	{
		nxt[l][r] = 0;
		return lans;
	}
	else 
	{
		nxt[l][r] = 1;
		return rans;
	}
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
	freopen("10.txt", "r", stdin);
	// freopen("brute_force_out.txt", "w", stdout);

	scanf("%d", &n);
	int T = 20;
	double tot_time = 0;
	while (T --)
	{
		for (int i = 1; i <= n; i ++ )
			scanf("%d", &golds[i]);

		for (int i = 1; i <= n; i ++ )
			sum[i] = sum[i - 1] + golds[i];

		memset(nxt, -1, sizeof nxt);

		LARGE_INTEGER nFreq;
		LARGE_INTEGER st, et;
		QueryPerformanceFrequency(&nFreq);
        QueryPerformanceCounter(&st);

		dfs(1, n);

		QueryPerformanceCounter(&et);

        tot_time += (double)(et.QuadPart - st.QuadPart)/(double)nFreq.QuadPart;

		// printf("%d\n", dfs(1, n));
		// printPath();
	}

	printf("average time: %.6fms\n", tot_time * 1000 / 20);

	
	// reverse(A.begin(), A.end());
	// for (auto a : A)
	// 	printf("%d ", a);
	// puts("");

	return 0;
}
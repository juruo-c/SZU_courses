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
int f[N][N];
int pre[N][N];
int sum[N];

int dp() // peo: the people who play the game now; 0: A, 1: B
{
	for (int i = 1; i <= n; i ++ )
		f[i][i] = golds[i];

	for (int i = 2; i <= n; i ++ )
		for (int l = 1; l + i - 1 <= n; l ++ )
		{
			int r = l + i - 1;
			int lans = golds[l] + sum[r] - sum[l] - f[l + 1][r];
			int rans = golds[r] + sum[r - 1] - sum[l - 1] - f[l][r - 1];
			if (lans > rans)
				f[l][r] = lans, pre[l][r] = 0;
			else f[l][r] = rans, pre[l][r] = 1;	
		}
}

void printPath()
{
	int l = 1, r = n;
	int who = 0;
	while (pre[l][r] != -1)
	{
		if (pre[l][r] == 0)
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
	freopen("1000.txt", "r", stdin);
	// freopen("dp_out.txt", "w", stdout);

	int T = 20;
	double tot_time = 0;
	scanf("%d", &n);
	while (T --)
	{
		memset(pre, -1, sizeof pre);
		for (int i = 1; i <= n; i ++ )
			sum[i] = sum[i - 1] + golds[i];
		for (int i = 1; i <= n; i ++ )
			scanf("%d", &golds[i]);

		LARGE_INTEGER nFreq;
		LARGE_INTEGER st, et;
		QueryPerformanceFrequency(&nFreq);
        QueryPerformanceCounter(&st);

		dp();

		QueryPerformanceCounter(&et);

        tot_time += (double)(et.QuadPart - st.QuadPart)/(double)nFreq.QuadPart;

		// printf("%d\n", f[1][n]);
		// printPath();
	}

	printf("average time: %.6fms\n", tot_time * 1000 / 20);

	return 0;
}
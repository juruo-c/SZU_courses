#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <Windows.h>
#include <ctime>

using namespace std;

const int N = 3000005;

int n;
int golds[N];
vector<int> A, B;
int f[N];
// int pre[N][N];
int sum[N];

int dp() // peo: the people who play the game now; 0: A, 1: B
{
	
	
	for (int i = 1; i <= n; i ++ )
		f[i] = golds[i];

	for (int i = 2; i <= n; i ++ )
		for (int l = n - i + 1; l >= 1; l -- )
		{
			int r = l + i - 1;
			int lans = golds[l] + sum[r] - sum[l] - f[r];
			int rans = golds[r] + sum[r - 1] - sum[l - 1] - f[r - 1];
			if (lans > rans)
				f[r] = lans;// pre[l][r] = 0;
			else f[r] = rans;// pre[l][r] = 1;	
		}
}

// void printPath()
// {
// 	int l = 1, r = n;
// 	int who = 0;
// 	while (pre[l][r] != -1)
// 	{
// 		if (pre[l][r] == 0)
// 		{
// 			if (!who)
// 				printf("%d ", l);
// 			l ++;
// 		}
// 		else
// 		{
// 			if (!who)
// 				printf("%d ", r);
// 			r --;
// 		}
// 		who ^= 1;
// 	}
// 	puts("");
// }

int main()
{
	freopen("3000000.txt", "r", stdin);

	int T = 1;
	scanf("%d", &n);
	double tot_time = 0;

	while (T --)
	{
		// memset(pre, -1, sizeof pre);
		
		for (int i = 1; i <= n; i ++ )
			scanf("%d", &golds[i]);
		for (int i = 1; i <= n; i ++ )
			sum[i] = sum[i - 1] + golds[i];
		LARGE_INTEGER nFreq;
		LARGE_INTEGER st, et;
		QueryPerformanceFrequency(&nFreq);
        QueryPerformanceCounter(&st);

		dp();

		QueryPerformanceCounter(&et);

        tot_time += (double)(et.QuadPart - st.QuadPart)/(double)nFreq.QuadPart;

		// printf("%d\n", f[n]);

		// printPath();
	}

	printf("average time: %.6fms\n", tot_time * 1000);

	return 0;
}
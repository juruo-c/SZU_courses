#include <iostream>
#include <vector>
#include <ctime>
#include <cstdio>
#include <windows.h>
#include <set>

using namespace std;

const int N = 10000000, L = -10000, R = 10000;

vector<int> a;

float random_data(float l, float r)
{
	return l + (float)(rand()) / RAND_MAX * (r - l);
}

void solve(float l, float r)
{
	set<pair<float, float> > S;
	for (int i = 1; i <= N; i ++ )
	{
		float x = random_data(l, r), y = random_data(l, r);
		if (S.count({x, y}) == 0)
		{
			printf("%.5f %.5f\n", x, y);
			S.insert({x, y});
		}
		else i --;
	}
}
	
int main()
{
   freopen("10000000.txt", "w", stdout);
   srand((unsigned) time(0));

   int T = 20;
   
   while (T --)
   {
   	printf("%d\n", N);
		solve(L, R);
		Sleep(1000);
   }
   return 0;
}

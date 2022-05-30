#include <iostream>
#include <cmath>
#include <ctime>
#include <Windows.h>
#include <cstdio>

using namespace std;

const int N = 1000005;
const float INF = 1e12;

int n;
struct Point
{
   float x, y;
}Points[N];

inline float dist(int i, int j)
{
   return sqrt((Points[i].x - Points[j].x) * (Points[i].x - Points[j].x) + (Points[i].y - Points[j].y) * (Points[i].y - Points[j].y));
}

inline float better_dist(int i, int j)
{ 
   return (Points[i].x - Points[j].x) * (Points[i].x - Points[j].x) + (Points[i].y - Points[j].y) * (Points[i].y - Points[j].y);
}

float brute_force()
{
   float ans = INF;
   for (int i = 1; i <= n; i ++ )
      for (int j = i + 1; j <= n; j ++ )
         // ans = min(ans, dist(i, j));
         ans = min(ans, better_dist(i, j));
   // return ans;
   return sqrt(ans);
}

int main()
{
   freopen("100000.txt", "r", stdin);
   
   int T = 20;
   double tot_time = 0;
   while (T --)
   {
      scanf("%d", &n);
      for (int i = 1; i <= n; i ++ )
         scanf("%f%f", &Points[i].x, &Points[i].y);

      LARGE_INTEGER nFreq;
      LARGE_INTEGER st, et;
      QueryPerformanceFrequency(&nFreq);
      QueryPerformanceCounter(&st);

      brute_force();

      QueryPerformanceCounter(&et);

      tot_time += (double)(et.QuadPart - st.QuadPart)/(double)nFreq.QuadPart;
      // printf("%.10f\n", brute_force());
   }

   printf("average time: %.6fms", tot_time * 1000 / 20);

   return 0;
}
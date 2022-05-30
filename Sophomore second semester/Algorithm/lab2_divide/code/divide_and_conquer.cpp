#include <iostream>
#include <cmath>
#include <ctime>
#include <Windows.h>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1000005;
const float INF = 1e12;

int n;
struct Point
{
   float x, y;
   bool operator < (const Point& p) const
   {
      return x < p.x;
   }
}Points[N], temp[N];

float dist(Point& pa, Point& pb)
{
   float dx = pa.x - pb.x, dy = pa.y - pb.y;
   return sqrt(dx * dx + dy * dy);
}

float brute_force()
{
   float ans = INF;
   for (int i = 1; i <= n; i ++ )
      for (int j = i + 1; j <= n; j ++ )
         ans = min(ans, dist(Points[i], Points[j]));
   return ans;
}

void solve(int l, int r, float midx, float& d)
{
   // merge sort by Points[].y
   {
      int mid = (l + r) / 2;
      int i = l, j = mid + 1, k = l;
      while (i <= mid && j <= r)
      {
         if (Points[i].y <= Points[j].y) temp[k ++] = Points[i ++];
         else temp[k ++] = Points[j ++];
      }
      while (i <= mid) temp[k ++] = Points[i ++];
      while (j <= r) temp[k ++] = Points[j ++];
      for (i = l; i <= r; i ++ ) Points[i] = temp[i];
   }

   // choose the points whose x >= midx - d && x <= midx + d
   int cnt = 0;
   for (int i = l; i <= r; i ++ )
      if (midx - d <= Points[i].x && Points[i].x <= midx + d)
         temp[++ cnt] = Points[i];

   // update d
   for (int i = 1; i <= cnt; i ++ )
      for (int j = i + 1; j <= cnt && temp[j].y - temp[i].y < d; j ++ )
         d = min(d, dist(temp[j], temp[i]));

}

float divide(int l, int r)
{
   if (l == r) return INF;
   if (l == r - 1) 
   {
      if (Points[l].y > Points[r].y) swap(Points[l], Points[r]);
      return dist(Points[l], Points[r]);
   }
   int mid = (l + r) / 2;
   float midx = Points[mid].x;
   float d1 = divide(l, mid);
   float d2 = divide(mid + 1, r);
   float d = min(d1, d2);
   solve(l, r, midx, d);
   return d;
}

float divide_and_conquer()
{
   sort(Points + 1, Points + 1 + n);
   return divide(1, n);
}

bool test_divide()
{
   float d1, d2;
   printf("BRUTE_FORCE: %.5f\n", (d1 = brute_force()));
   printf("DIVIDE_AND_CONQUER: %.5f\n", (d2 = divide_and_conquer()));
   if (d1 == d2) puts("RIGHT!!\n");
   else puts("WRONG~~~\n");

   return (d1 == d2);
}

int main()
{
   freopen("600000.txt", "r", stdin);
   
   int T = 20;
   double tot_time = 0;
   // bool flag = true;
   while (T --)
   {
      scanf("%d", &n);
      for (int i = 1; i <= n; i ++ )
         scanf("%f%f", &Points[i].x, &Points[i].y);

      // right test
      // flag &= test_divide();

      // time test
      LARGE_INTEGER nFreq;
      LARGE_INTEGER st, et;
      QueryPerformanceFrequency(&nFreq);
      QueryPerformanceCounter(&st);

      divide_and_conquer();

      QueryPerformanceCounter(&et);

      tot_time += (double)(et.QuadPart - st.QuadPart)/(double)nFreq.QuadPart;
   }

   // if (flag) puts("All the data pass the test!!");

   printf("average time: %.6fms", tot_time * 1000 / 20);

   return 0;
}
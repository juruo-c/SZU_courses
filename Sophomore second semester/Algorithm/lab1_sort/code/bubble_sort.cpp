#include <iostream>
#include <vector>
#include <ctime>
#include <Windows.h>

using namespace std;

const int N = 100005;

int a[N];

void bubble_sort(int n)
{
    for (int i = 1; i <= n - 1; i ++ )
        for (int j = 1; j <= n - i; j ++ )
            if (a[j] > a[j + 1])
                swap(a[j], a[j + 1]);
}

void better_bubble_sort(int n)
{
    int last = n;
    for (int i = 1; i <= n - 1; i ++ )
    {
        int t = last;
        last = 0;
        for (int j = 1; j <= t - 1; j ++ )
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
                last = j;
            }
    }
}

int main()
{
    freopen("100000.txt", "r", stdin);
    int T = 20;
    int n; scanf("%d", &n);


    double tot_time = 0;
    while (T --)
    {
        for (int i = 1; i <= n; i ++ )
            scanf("%d", &a[i]);
        LARGE_INTEGER nFreq;
        LARGE_INTEGER st, et;
        QueryPerformanceFrequency(&nFreq);
        QueryPerformanceCounter(&st);
//        bubble_sort(n);
        better_bubble_sort(n);
//        for (int i = 1; i <= n; i ++ )
//            cout << a[i] << " ";
//        cout << endl;
        QueryPerformanceCounter(&et);

        tot_time += (double)(et.QuadPart - st.QuadPart)/(double)nFreq.QuadPart;
    }

    printf("average time: %.6fms", tot_time * 1000 / 20);

    return 0;
}


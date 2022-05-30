#include <iostream>
#include <vector>
#include <ctime>
#include <Windows.h>

using namespace std;

const int N = 1000005;

int a[N];

int partition(int l, int r)
{
    int key = a[l];
    while (l < r)
    {
        while (l < r && a[r] >= key) r --;
        if (l < r) a[l] = a[r], l ++;
        while (l < r && a[l] <= key) l ++;
        if (l < r) a[r] = a[l], r --;
    }
    a[l] = key;
    return l;
}

void quick_sort(int l, int r)
{
    if (l < r)
    {
        int mid = partition(l, r);
        quick_sort(l, mid - 1);
        quick_sort(mid + 1, r);
    }
}

int main()
{
    freopen("1000000.txt", "r", stdin);
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
        quick_sort(1, n);
//        for (int i = 1; i <= n; i ++ )
//            cout << a[i] << " ";
//        cout << endl;
        QueryPerformanceCounter(&et);

        tot_time += (double)(et.QuadPart - st.QuadPart)/(double)nFreq.QuadPart;
    }

    printf("average time: %.10fms", tot_time * 1000 / 20);

    return 0;
}

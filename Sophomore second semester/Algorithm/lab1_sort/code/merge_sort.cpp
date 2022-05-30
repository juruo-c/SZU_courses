#include <iostream>
#include <vector>
#include <ctime>
#include <Windows.h>

using namespace std;

const int N = 1000005;

int a[N], b[N];

void merge(int l, int mid, int r)
{
    int i = l, j = mid + 1, k = l;
    while (i <= mid && j <= r)
    {
        if (a[i] <= a[j]) b[k ++] = a[i ++];
        else b[k ++] = a[j ++];
    }
    while (i <= mid) b[k ++] = a[i ++];
    while (j <= r) b[k ++] = a[j ++];
    for (int mh = l; mh <= r; mh ++ ) a[mh] = b[mh];
}

void merge_sort(int l, int r)
{
    if (l == r) return;
    int mid = l + r >> 1;
    merge_sort(l, mid);
    merge_sort(mid + 1, r);
    merge(l, mid, r);
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
        merge_sort(1, n);
//        for (int i = 1; i <= n; i ++ )
//            cout << a[i] << " ";
//        cout << endl;
        QueryPerformanceCounter(&et);

        tot_time += (double)(et.QuadPart - st.QuadPart)/(double)nFreq.QuadPart;
    }

    printf("average time: %.10fms", tot_time * 1000 / 20);

    return 0;
}


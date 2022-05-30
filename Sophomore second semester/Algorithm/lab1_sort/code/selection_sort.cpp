#include <iostream>
#include <vector>
#include <ctime>
#include <Windows.h>

using namespace std;

const int N = 100005;

int a[N];

void selection_sort(int n)
{
    for (int i = 1; i <= n - 1; i ++ )
    {
        int minval = a[i], k = i;
        for (int j = i + 1; j <= n; j ++ )
            if (a[j] < minval)
            {
                minval = a[j];
                k = j;
            }
        a[k] = a[i];
        a[i] = minval;
    }
}

int main()
{
    freopen("10000.txt", "r", stdin);
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
        selection_sort(n);
//        for (int i = 1; i <= n; i ++ )
//            cout << a[i] << " ";
//        cout << endl;
        QueryPerformanceCounter(&et);

        tot_time += (double)(et.QuadPart - st.QuadPart)/(double)nFreq.QuadPart;
    }

    printf("average time: %.10fms", tot_time * 1000 / 20);

    return 0;
}

#include <iostream>
#include <vector>
#include <ctime>
#include <Windows.h>

using namespace std;

const int N = 100005;

int a[N];

void insert_sort(int n)
{
    for (int i = 2; i <= n; i ++ )
    {
        int key = a[i];
        int j = i - 1;
        while (j >= 1 && key < a[j])
        {
            a[j + 1] = a[j];
            j --;
        }
        a[j + 1] = key;
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
        insert_sort(n);
//        for (int i = 1; i <= n; i ++ )
//            cout << a[i] << " ";
//        cout << endl;
        QueryPerformanceCounter(&et);

        tot_time += (double)(et.QuadPart - st.QuadPart)/(double)nFreq.QuadPart;
    }

    printf("average time: %.6fs", tot_time *1000 / 20);

    return 0;
}

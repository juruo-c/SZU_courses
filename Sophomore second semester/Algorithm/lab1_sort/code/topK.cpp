#include <iostream>
#include <ctime>
#include <Windows.h>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int N = 1000005;

int a[N];

void bubble_sort(int n, int k)
{
    for (int i = 1; i <= k; i ++ )
        for (int j = 2; j <= n - i + 1; j ++ )
            if (a[j - 1] > a[j])
                swap(a[j - 1], a[j]);
}

void heap_sort(int n, int k)
{
    priority_queue<int, vector<int>, greater<int> > q;
    for (int i = 1; i <= n; i ++ )
    {
        if (i <= k) q.push(a[i]);
        else if (q.top() < a[i])
        {
            q.pop();
            q.push(a[i]);
        }
    }

//    printf("The top %dth numbers: \n", k);
//    while(q.size())
//        printf("%d ", q.top()), q.pop();
//    puts("");
}

void Bubble_sort_test()
{
    srand((unsigned)time(false));
    int n = 100, k = 10;
    for (int i = 1; i <= n; i ++ )
        a[i] = i;
    for (int i = 1; i <= n; i ++ )
        swap(a[i], a[rand() % n + 1]);

    puts("Original data: ");
    for (int i = 1; i <= n; i ++ )
        printf("%d ", a[i]);
    puts("");

    bubble_sort(n, k);

    printf("The top %dth numbers: \n", k);
    for (int i = n - k + 1; i <= n; i ++)
        printf("%d ", a[i]);
    puts("");
}

void heap_sort_test()
{
    srand((unsigned)time(false));
    int n = 100, k = 10;
    for (int i = 1; i <= n; i ++ )
        a[i] = i;
    for (int i = 1; i <= n; i ++ )
        swap(a[i], a[rand() % n + 1]);

    puts("Original data: ");
    for (int i = 1; i <= n; i ++ )
        printf("%d ", a[i]);
    puts("");

    heap_sort(n, k);
}

int partition(int l, int r)
{
    int x = a[r];
    int j = l - 1;
    for (int i = l; i < r; i ++ )
        if (a[i] >= x)
        {
            j ++;
            swap(a[i], a[j]);
        }
    swap(a[j + 1], a[r]);
    return j + 1;
}

int quick_sort(int l, int r, int k)
{
    if (l == r) return l;
    int mid = partition(l, r);
    int num = mid - l + 1;
    if (num == k) return mid;
    else if (num > k) return quick_sort(l, mid - 1, k);
    else return quick_sort(mid + 1, r, k - num);
}

void quick_sort_test()
{
    srand((unsigned)time(false));
    int n = 100, k = 10;
    for (int i = 1; i <= n; i ++ )
        a[i] = i;
    for (int i = 1; i <= n; i ++ )
        swap(a[i], a[rand() % n + 1]);

    puts("Original data: ");
    for (int i = 1; i <= n; i ++ )
        printf("%d ", a[i]);
    puts("");

    quick_sort(1, n, k);

    printf("The top %dth numbers: \n", k);
    for (int i = 1; i <= k; i ++)
        printf("%d ", a[i]);
    puts("");
}

void insertion_sort(int l, int r)
{
    for (int i = l + 1; i <= r; i ++ )
    {
        int key = a[i];
        int j = i - 1;
        while (j >= l && key > a[j])
        {
            a[j + 1] = a[j];
            j --;
        }
        a[j + 1] = key;
    }
}

int patition(int l, int r, int pos)
{
    int x = a[pos], j = l - 1;
    swap(a[r], a[pos]);

    for (int i = l; i < r; i ++ )
        if (a[i] >= x)
        {
            j ++;
            if (j != i) swap(a[i], a[j]);
        }
    swap(a[j + 1], a[r]);
    return j + 1;
}

int select(int l, int r, int k)
{
//    cout << l << " " << r << endl;
    if (l == r) return l;
    int t = l - 1;
    for (int i = l; i <= r; i += 5)
    {
        int j = min(i + 4, r);
        insertion_sort(i, j);
//        cout << i << " " << j << endl;
//        for (int mh = i; mh <= j; mh ++ )
//            cout << a[mh] << " ";
//        cout << endl;
        swap(a[++ t], a[i + (j - i) / 2]);
    }
//    cout << "t = " << t << endl;
    int keypos = select(l, t, (t - l + 2) / 2 + 1);
    int pos = patition(l, r, keypos);

    int num = pos - l + 1;

    if (num == k) return pos;
    else if(num < k) return select(pos + 1, r, k - num);
    else return select(l, pos - 1, k);
}

void select_test()
{
    srand((unsigned)time(false));
    int n = 100, k = 10;
    for (int i = 1; i <= n; i ++ )
        a[i] = i;
    for (int i = 1; i <= n; i ++ )
        swap(a[i], a[rand() % n + 1]);

    puts("Original data: ");
    for (int i = 1; i <= n; i ++ )
        printf("%d ", a[i]);
    puts("");

    select(1, n, k);

    printf("The top %dth numbers: \n", k);
    for (int i = 1; i <= k; i ++)
        printf("%d ", a[i]);
    puts("");
}

int main()
{
//    Bubble_sort_test();
//    heap_sort_test();
//    quick_sort_test();
//    select_test();
    freopen("100000.txt", "r", stdin);
    int T = 20;
    int k = 10;
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

//        bubble_sort(n, k);
//        heap_sort(n, k);
//        quick_sort(1, n, k);
        select(1, n, k);

        QueryPerformanceCounter(&et);

        tot_time += (double)(et.QuadPart - st.QuadPart)/(double)nFreq.QuadPart;
    }

    printf("average time: %.6fms", tot_time * 1000 / 20);

    return 0;
}


#include <iostream>
#include <vector>
#include <ctime>
#include <windows.h>

using namespace std;

const int N = 1000000;

vector<int> a;

void random_data()
{
    srand((unsigned)time(0));

    a.clear();
    a.push_back(0);
    for (int i = 1; i <= N; i ++ )
        a.push_back((int)(((double)rand()/RAND_MAX)*1000000));

    for (int i = 1; i <= N; i ++ )
        swap(a[i], a[rand() % N + 1]);

    for (int i = 1; i <= N; i ++ )
        cout << a[i] << " ";
    cout << endl;
}

int main()
{
    freopen("1000000.txt", "w", stdout);

    int T = 20;
    cout << N << endl;
    while (T --)
    {
        random_data();
        Sleep(1000);
    }
    return 0;
}

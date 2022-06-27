#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <ctime>
#include <Windows.h>
#include <set>

using namespace std;

int main()
{
	freopen("1000_doctor.txt", "w", stdout);
	srand(time(false));
	puts("1000 7 3\n3 1 2 3\n7 4 5 6 7 8 9 10\n3 11 12 13\n3 14 15 16\n3 17 18 19\n3 20 21 22\n7 23 24 25 26 27 28 29");
	int n = 1000, m = 29;
	for (int i = 1; i <= n; i ++ )
	{
		int k = rand() * rand() % 5 + 1;
		set<int> s;
		for (int j = 0; j < k; j ++ )
		{
			int d = rand() * rand() % m + 1;
			if (!s.count(d)) s.insert(d);
			else j --;
		}
		printf("%d ", k);
		for (auto x : s) printf("%d ", x);
		puts("");
	}

	return 0;
}
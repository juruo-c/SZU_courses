#include <iostream>
#include <algorithm>
#include <cstring>
#include <ctime>
#include <set>

using namespace std;

typedef pair<int, int> PII;

const int N = 40, M = 400, C = 4;

set<PII> s;

int main()
{
	freopen("40_400.txt", "w", stdout);
	srand(time(0));

	cout << N << " " << M << endl;
	for (int i = 1; i < N; i ++ )
	{
		cout << "e " << i << " " << i + 1 << endl;
		s.insert({i, i + 1});
	}
	for (int i = N; i <= M; i ++ )
	{
		int u = (rand() * rand()) % N + 1;
		
		if (u == N) {
			i --;
			continue;
		}
		int v = (rand() * rand()) % (N - u) + u + 1;
		if (s.count({u, v}))
		{
			i --;
			continue;
		}
		cout << "e " << u << " " << v << endl;
		s.insert({u, v});
	}

	return 0;
}
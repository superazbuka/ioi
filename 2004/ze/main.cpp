#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cassert>

using namespace std;

#ifdef ONPC
const size_t MAXN = 100;
#else
const size_t MAXN = 1e5 * 1.5;
#endif

typedef unsigned int index;

int d[MAXN];

int main()
{
#ifdef ONPC
	assert(freopen("a.in", "r", stdin));
	assert(freopen("a.out", "w", stdout));
#else
#endif
	int n, cnt1, cnt2;
	cin >> n >> cnt1 >> cnt2;
	int cnt = 0;
	for (int io = 0; io < cnt1; ++io)
	{
		int di;
		cin >> di;
		for (int i = cnt; i >= 0; --i)
		{
			if (i + di <= n)
			{
				d[i + di] = max(d[i + di], d[i] + di);
			}
			else
			{
				d[n] = max(d[n], d[i] + n - i - 1);
			}
		}
		cnt = min(cnt + di, n);
	}
	for (int io = 0; io < cnt2; ++io)
	{
		int di;
		cin >> di;
		for (int i = n; i >= 0; --i)
		{
			if (i + di <= n)
			{
				d[i + di] = max(d[i + di], d[i] + di - 1);
			}
			else
			{
				d[n] = max(d[n], d[i] + n - i - 1);
			}
		}
	}
	cout << d[n];
	return 0;
}

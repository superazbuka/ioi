#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>

using namespace std;

pair<int, int> a[20005];
int sf[20005];
int ss[20005];
int fx[20005];
int fy[20005];
int f[20005];

bool les_second(const int &_a, const int &_b)
{
	return a[_a].second < a[_b].second;
}

bool les_first(const int &_a, const int &_b)
{
	return a[_a].first < a[_b].first;
}

int main()
{
	int n, t;
	scanf("%d%d", &n, &t);
	for (int i = 0; i < n; ++i)
	{
		scanf("%d%d", &a[i].first, &a[i].second);
		ss[i] = i;
		sf[i] = i;
	}
	sort(sf, sf + n, les_first);
	sort(ss, ss + n, les_second);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
		{
			if (a[i].first < a[j].first and a[i].second < a[j].second)
			f[j]++;
		}
	int ans = 1e9;
	int ansl = 0, ansr = 0;
	for (int i = 0; i < n; ++i)
	{
		int tx = 0;
		int ty = 0;
		for (int j = 0; j < n; ++j)
		{
			if (a[ss[j]].first < a[i].first)
				++tx;
			if (a[sf[j]].second < a[i].second)
				++ty;
			fx[ss[j]] = tx;
			fy[sf[j]] = ty;
		}
		for (int j = 0; j < n; j++)
		{
			int cnt = abs(f[i] + f[j] - fx[j] - fy[j]) + 1;
			if (cnt >= t and cnt < ans)
			{
				ans = cnt;
				ansl = i;
				ansr = j;
			}
		}
	}
	cout << ansl + 1 << " " << ansr + 1 << endl;
}

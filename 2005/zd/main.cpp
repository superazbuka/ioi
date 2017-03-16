#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cassert>

using namespace std;

#ifdef ONPC
const size_t MAXN = 100;
#else
const size_t MAXN = 3e6;
#endif

typedef unsigned int index;

int cntu[MAXN];
int cntd[MAXN];
int up[MAXN];

int dist(int a, int b, int n)
{
	if (b < a)
	{
		return n - (a - b);
	}
	else
	{
		return b - a;
	}
}

template <class X>
int solve(X a, X b)
{
	int pu, pd;
	pu = 0;
	pd = MAXN - 1;
	for (index i = 0; i < MAXN; i++)
	{
		cntu[i] = 0;
		cntd[i] = 0;
		up[i] = 0;
	}
	size_t n = b - a;
	for (auto i = a; i != b; i++)
	{
		int cur = *i;
		size_t dist1 = dist(i - a, cur, n), dist2 = dist(cur, i - a, n);
		if (dist1 < n / 2 + n % 2)
		{
			cntu[dist1]++;
		}
		else
		{
			cntd[pd - (int)n / 2 - (int)n % 2 + (int)dist2]++;
		}
	}
	int topu = 0;
	int topd = 0;
	int last = 0;
	for (index i = 0; i < n / 2 + n % 2 + 1; i++)
	{
		if (cntu[i] > 0)
			topu = (int)i;
		if (cntd[pd - (int)n / 2 - (int)n % 2 + (int)i] > 0)
		{
			up[pd - (int)n / 2 - (int)n % 2 + (int)i] = (int)topd;
			topd = (pd - (int)n / 2 - (int)n % 2 + (int)i);
		}
		if (last == 0 and cntd[pd - (int)n / 2 - (int)n % 2 + (int)i] > 0)
		{
			last = (pd - (int)n / 2 - (int)n % 2 + (int)i);
		}
	}
	int ans = (int)(max(topu - pu, (int)(topd - pd + (int)n / 2 + (int)n % 2)));
	for (index i = 0; i < n - 1; i++)
	{
		if (cntu[pu] > 0)
		{
			up[last] = pd - (int)n / 2 - (int)n % 2;
			last = pd - (int)n / 2 - (int)n % 2;
		}
		if (cntd[pd] > 0)
		{
			topd = up[pd];
			topu = ((int)n / 2 + (int)pu);
		}
		if (topd == 0 and last < pd)
			topd = last;
		cntu[pu + (int)n / 2] += cntd[pd];
		cntd[pd - (int)n / 2 - (int)n % 2] += cntu[pu];
		pd--, pu++;
		ans = min(ans, (int)(max(topu - pu, (int)(topd - pd + (int)n / 2 + (int)n % 2))));
	}
	return ans;
}


int main()
{
#ifdef ONPC
	assert(freopen("a.in", "r", stdin));
	assert(freopen("a.out", "w", stdout));
#else
#endif
	size_t n;
	cin >> n;
	vector<int> a(n);
	for (index i = 0; i < n; i++)
	{
		cin >> a[i];
		a[i]--;
	}
	cout << min(solve(a.begin(), a.end()), solve(a.rbegin(), a.rend())) << endl;
}

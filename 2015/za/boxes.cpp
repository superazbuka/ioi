#include "boxes.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <climits>

using namespace std;
typedef unsigned int index;

long long delivery(int N, int K, int l, int p[]) {
	size_t n = (size_t)N, k = (size_t)K;
	long long *pref = new long long[n + 1],
		*suf = new long long[n + 1];
	pref[0] = 0;
	for (index i = 0; i < n; i++)
	{
		pref[i + 1] = pref[i + 1 >= k ? i - k + 1 : 0] + (p[i]);
	}
	suf[0] = 0;
	for (index i = 0; i < n; i++)
	{
		suf[i + 1] = suf[i + 1 >= k ? i - k + 1 : 0] + (l - p[n - i - 1]);
	}
	long long ans = LLONG_MAX;
	for (index i = 0; i <= n; i++)
	{
		ans = min(ans, 2 * pref[i] + 2 * suf[n - i]);
	}
	for (index i = 0; i <= n - k; i++)
	{
		ans = min(ans, 2 * pref[i] + 2 * suf[n - i - k] + l);
	}
    return ans;
}

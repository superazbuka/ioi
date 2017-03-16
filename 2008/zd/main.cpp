#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cassert>

using namespace std;

typedef unsigned int index;

int main()
{
#ifdef ONPC
	assert(freopen("a.in", "r", stdin));
	assert(freopen("a.out", "w", stdout));
#else
#endif
	ios::sync_with_stdio(false);
	size_t n;
	int module;
	string s;
	cin >> n >> module >> s;
	vector<vector<int>> d(n + 1, vector<int>(9));
	d[0][0] = 1;
	for (index i = 0; i < n; i++)
	{
		for (index j = 0; j < 3; j++)
			for (index k = 0; k < 3; k++)
			{
				d[i][j * 3 + k] %= module;
				if (j != 2)
				{
					d[i + 1][(j + 1) * 3 + (index)max((int)k - 1, 0)] += d[i][j * 3 + k];
				}
				if (k != 2)
				{
					d[i + 1][(index)max((int)j - 1, 0) * 3 + k + 1] += d[i][j * 3 + k];
				}
			}
	}
	index j = 0, k = 0;
	int ans = 1;
	for (index i = 0; i < n; i++)
	{
		if (s[i] == 'L')
		{
			j++;
			k = (index)max((int)k - 1, 0);
		}
		else
		{
			if (j < 2)
			{
				index nj = j + 1, nk = (index)max((int)k - 1, 0);
				for (index sj = 0; sj < 3; sj++)
					for (index sk = 0; sk < 3; sk++)
					{
						if (sj + nj < 3 and sk + nk < 3)
						{
							ans += d[n - i - 1][sj * 3 + sk];
						}
					}
			}
			j = (index)max((int)j - 1, 0);
			k = k + 1;
			ans %= module;
		}
	}
	cout << ans << endl;
}

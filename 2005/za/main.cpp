#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

int fld[255][255];
int psum[255][255];
int minr[255];
int minl[255];
int mint[255];
int minb[255];
int n, ts;

int get(int i, int j)
{
	if (i >= 0 and j >= 0)
		return psum[i][j];
	return 0;
}

int main()
{
	#ifdef ONPC
		freopen("a.in", "r", stdin);
		freopen("a.out", "w", stdout);
	#endif
	int w, h;
	cin >> w >> h;
	cin >> n >> ts;
	for (int i = 0; i < n; i++)
	{
		int x, y;
		cin >> x >> y;
		fld[x][y]++;
	}
	for (int i = 0; i < 255; i++)
	{
		minl[i] = 1e9;
		minr[i] = 1e9;
		minb[i] = 1e9;
		mint[i] = 1e9;
		for (int j = 0; j < 255; j++)
		{
			psum[i][j] = get(i - 1, j) + get(i, j - 1) - get(i - 1, j - 1) + fld[i][j];
		}
	}
	for (int i = 0; i < 255; i++)
	{
		for (int j = 0; j <= i; j++)
			for (int k = 0; k < 255; k++)
			{
				int l = 0, r = k + 1;
				while (r - l > 1)
				{
					int m = (l + r) / 2;
					int sum = get(i, k) - get(j - 1, k) - get(i, m - 1) + get(j - 1, m - 1);
					if (sum < ts)
					{
						r = m;
					}
					else
					{
						l = m;
					}
				}
				int sum = get(i, k) - get(j - 1, k) - get(i, l - 1) + get(j - 1, l - 1);
				int pr = 2 * (i - j + 1 + k - l + 1);
				if (sum == ts)
				{
					mint[i] = min(pr, mint[i]);
					minb[j] = min(pr, minb[j]);
					minr[k] = min(pr, minr[k]);
					minl[l] = min(pr, minl[l]);
				}
			}
	}
	int ans = 1e9;
	for (int i = 0; i < 255; i++)
	{
		for (int j = i + 1; j < 255; j++)
		{
			ans = min(ans, minr[i] + minl[j]);
			ans = min(ans, mint[i] + minb[j]);
		}
	}
	if (ans < 1e9)
	{
		cout << ans << endl;
	}
	else
	{
		cout << "NO" << endl;
	}
}


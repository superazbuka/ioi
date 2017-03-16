#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <climits>

using namespace std;

const int MAXN = 2010;
const int ADD = 1000;
const int INF = 1e9;

int x[MAXN];
int y[MAXN];
int cx, cy;
int mx[MAXN];
int ox[MAXN];
int my[MAXN];
int oy[MAXN];

void build()
{
	for (int i = 0; i < MAXN; i++)
	{
		mx[i] = min((i > 0 ? mx[i - 1] : INF), x[i] - i + ADD);
		my[i] = min((i > 0 ? my[i - 1] : INF), y[i] - i + ADD);
	}
	for (int i = MAXN - 1; i >= 0; i--)
	{
		ox[i] = min((i + 1 < MAXN ? ox[i + 1] : INF), x[i] + i - ADD);
		oy[i] = min((i + 1 < MAXN ? oy[i + 1] : INF), y[i] + i - ADD);
	}
}

int go(int x, int y)
{
	int ans = abs(x - cx) + min(oy[y + ADD] - y, my[y + ADD] + y);
	ans = min(ans, abs(y - cy) + min(ox[x + ADD] - x, mx[x + ADD] + x));
	return ans;
}

int main()
{
	#ifdef ONPC
		freopen("a.in", "r", stdin);
		freopen("a.out", "w", stdout);
	#endif
	int n;
	cin >> n;
	for (int i = 0; i < MAXN; i++)
	{
		x[i] = INF;
		y[i] = INF;
	}
	x[ADD] = 0;
	y[ADD] = 0;
	cx = 0, cy = 0;
	build();
	for (int i = 0; i < n; i++)
	{
		int nx, ny;
		cin >> nx >> ny;
		for (int i = 0; i < MAXN; i++)
		{
			x[i] = go(i - ADD, ny);
			y[i] = go(nx, i - ADD);
		}
		build();
		cx = nx;
		cy = ny;
	}
	int ans = INF;
	for (int i = 0; i < MAXN; i++)
	{
		ans = min(ans, x[i]);
		ans = min(ans, y[i]);
	}
	cout << ans << endl;
}


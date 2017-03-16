#include <iostream>
#include <set>
#include <cstdio>
#include <cstdlib>
#include <climits>

using namespace std;

int fld[1000][1000];
int ps[1000][1000];
int nf[1000][1000];
pair<int, int> my[1000][1000];
pair<int, int> mm[1000][1000];
int logs[2001];

int get(int i, int j, int mass[1000][1000])
{
	if (i >= 1000 or j >= 1000 or i < 0 or j < 0)
		return 0;
	return mass[i][j];
}

int get(pair<int, int> pos, int mass[1000][1000])
{
	if (pos.first >= 1000 or pos.second >= 1000 or pos.first < 0 or pos.second < 0)
		return 0;
	return mass[pos.first][pos.second];
}

int sum(int xl, int yl, int xr, int yr)
{
	return get(xr, yr, ps) - get(xr, yl - 1, ps) - get(xl - 1, yr, ps) + get(xl - 1, yl - 1, ps);
}

void build(int n, int m, int c, int d, int a, int b)
{
	//cout << n << " " << m << " " << a << " " << b << " " << c << " " << d << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			ps[i][j] = get(i, j - 1, ps) + get(i - 1, j, ps) - get(i - 1, j - 1, ps) + fld[i][j];
		}
	}
	for (int i = 0; i < n - a + 1; i++)
	{
		for (int j = 0; j < m - b + 1; j++)
		{
			nf[i][j] = sum(i, j, i + a - 1, j + b - 1);
		}
	}
	int len1 = c - a - 1, len2 = d - b - 1;
	for (int i = 0; i < n; i++)
	{
		multiset<pair<int, pair<int, int> > > mi;
		for (int j = 0; j < len2 - 1; j++)
		{
			mi.insert({nf[i][j], {i, j}});
		}
		for (int j = 0; j < m - d + 2; j++)
		{
			mi.insert({nf[i][j + len2 - 1], {i, j + len2 - 1}});
			my[i][j] = mi.begin()->second;
			mi.erase({nf[i][j], {i, j}});
		}
	}
	for (int i = 0; i < m - d + 2; i++)
	{
		multiset<pair<int, pair<int, int> > > mi;
		for (int j = 0; j < len1 - 1; j++)
		{
			mi.insert({get(my[j][i], nf), my[j][i]});
		}
		for (int j = 0; j < n - c + 2; j++)
		{
			mi.insert({get(my[j + len1 - 1][i], nf), my[j + len1 - 1][i]});
			mm[j][i] = mi.begin()->second;
			mi.erase({get(my[j][i], nf), my[j][i]});
		}
	}
	pair<pair<int, int>, pair<int, int> > ans;
	int zn = -1e9;
	for (int i = 0; i < n - c + 1; i++)
		for (int j = 0; j < m - d + 1; j++)
		{
			int cur = sum(i, j, i + c - 1, j + d - 1) - get(mm[i + 1][j + 1], nf);
			if (zn < cur)
			{
				zn = cur;
				ans = {{i, j}, mm[i + 1][j + 1]};
			}
		}
	cout <<ans.first.second + 1 << " " << ans.first.first + 1 << endl << ans.second.second + 1 << " " << ans.second.first + 1 << endl;
}


int main()
{
	#ifdef ONPC
		freopen("a.in", "r", stdin);
		freopen("a.out", "w", stdout);
	#endif
	int n, m, a, b, c, d;
	cin >> n >> m >> a >> b >> c >> d;
	swap(n, m);
	swap(a, b);
	swap(c, d);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			cin >> fld[i][j];
		}
	build(n, m, a, b, c, d);
	return 0;
}



#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <climits>

using namespace std;

int d[1000][1000][2];
int g[1000][1000];
int n, m;

int mod(int k)
{
	k = k % n;
	if (k >= 0)
		return k;
	else
		return k + n;
}

int main()
{
	#ifdef ONPC
		freopen("a.in", "r", stdin);
		freopen("a.out", "w", stdout);
	#endif
	cin >> n >> m;
	for (int j = 0; j < m; j++)
	{
		int l, r;
		cin >> l >> r;
		l--, r--;
		g[l][r] = 1;
		g[r][l] = 1;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			d[i][j][0] = -1;
			d[i][j][1] = -1;
		}
		d[i][i][0] = -100;
		d[i][i][1] = -100;
	}
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int j1 = mod(j + 1);
			int ji = mod(j + i);
			if (g[j][j1] and (d[j1][ji][0] != -1))
			{
				d[j][ji][0] = j1;
			}
			if (g[j][ji] and (d[j1][ji][1] != -1))
			{
				d[j][ji][0] = ji;
			}
			if (g[ji][j] and (d[j][mod(ji - 1)][0] != -1))
			{
				d[j][ji][1] = j;
			}
			if (g[ji][mod(ji - 1)] and (d[j][mod(ji - 1)][1] != -1))
			{
				d[j][ji][1] = mod(ji - 1);
			}
		}
	}
	int pos1 = -1, pos2, ty;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (d[i][mod(i - 1)][j] != -1)
			{
				pos1 = i;
				pos2 = mod(i - 1);
				ty = j;
				break;
			}
		}
	}
	if (pos1 == -1)
	{
		cout << -1 << endl;
	}
	else
	{
		while (true)
		{
			//cout << pos1 << " " << pos2 << " " << ty << " " <<  d[pos1][pos2][ty] << endl;
			if (ty == 0)
			{
				cout << pos1 + 1 << endl;
				if (pos1 == pos2)
					break;
				if (d[pos1][pos2][ty] == mod(pos1 + 1))
					ty = 0;
				else
					ty = 1;
				pos1 = mod(pos1 + 1);
			}
			else
			{
				cout << pos2 + 1 << endl;
				if (pos1 == pos2)
					break;
				if (d[pos1][pos2][ty] == mod(pos2 - 1))
					ty = 1;
				else
					ty = 0;
				pos2 = mod(pos2 - 1);
			}
		}
	}
	return 0;
}

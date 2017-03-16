nclude <iostream>
#include <vector>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cassert>

using namespace std;

#ifdef ONPC
const size_t MAXN = 100;
const size_t MAXK = 50;
#else
const size_t MAXN = 105;
const size_t MAXK = 55;
#endif

typedef unsigned int index;

int d[MAXN][MAXK][MAXN];

struct Edge
{
	int len, prod;
	index to;
	Edge(): len(0), prod(0), to(0){};
	Edge(int s_len, int s_prod, index s_to): len(s_len), prod(s_prod), to(s_to){}
};

int ans(index v, size_t left, int add, int sum_add, int my_w, const vector<vector<Edge> > &g)
{
	if (d[v][left][add] != -1)
	{
		return d[v][left][add];
	}
	vector<vector<int> > tmp_d(g[v].size() + 1, vector<int>(left + 1, (int)2e9 + 7));
	tmp_d[0][0] = my_w * sum_add;
	for (index i = 0; i < g[v].size(); i++)
	{
		for (index j = 0; j <= left; j++)
		{
			for (index s = 0; j + s <= left; s++)
			{
				tmp_d[i + 1][j + s] = min(tmp_d[i][j] +
					+ ans(g[v][i].to, s, add + 1, sum_add + g[v][i].len, g[v][i].prod, g), tmp_d[i + 1][j + s]);
			}
			for (index s = 1; j + s <= left; s++)
			{
				tmp_d[i + 1][j + s] = min(tmp_d[i][j]
					+ ans(g[v][i].to, s - 1, 0, 0, g[v][i].prod, g), tmp_d[i + 1][j + s]);
			}
		}
	}
	int mmin = (int)2e9 + 7;
	for (index i = 0; i <= left; i++)
		mmin = min(mmin, tmp_d[g[v].size()][i]);
	d[v][left][add] = mmin;
	return d[v][left][add];
}

int main()
{
#ifdef ONPC
	assert(freopen("a.in", "r", stdin));
	assert(freopen("a.out", "w", stdout));
#else
#endif
	size_t n, k;
	cin >> n >> k;
	n++;
	vector<vector<Edge> > g(n);
	for (index i = 0; i < n - 1; i++)
	{
		int len, prod;
		index from;
		cin >> prod >> from >> len;
		g[from].push_back({len, prod, i + 1});
	}
	for (index i = 0; i <= n; i++)
		for (index j = 0; j <= k; j++)
			for (index s = 0; s <= n; s++)
				d[i][j][s] = -1;
	cout << ans(0, k, 0, 0, 0, g) << endl;
}


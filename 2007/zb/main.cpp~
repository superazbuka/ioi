#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib>
#include <climits>
#include <cstdio>
#include <cassert>

using namespace std;

typedef unsigned int index;

struct Edge
{
	index from, to, my_part, num;
	Edge *pair;
	Edge(index new_from, index new_to, index new_num): from(new_from), to(new_to), my_part((index)-1), num(new_num), pair(NULL){}
};

index dir(const vector<pair<int, int>> &pts, Edge *cur)
{
	int x = pts[cur->to].first - pts[cur->from].first,
		y = pts[cur->to].second - pts[cur->from].second;
	if (x > 0)
		return 0;
	if (y < 0)
		return 1;
	if (x < 0)
		return 2;
	if (y > 0)
		return 3;
	assert(false);
}
		
bool find(const vector<pair<int, int>> &pts, const vector<vector<Edge*>> &g, index i, index j, index last)
{
	long long sum = 0;
	index sv = i;
	do
	{
		g[i][j]->my_part = last;
		auto f = pts[g[i][j]->from];
		auto t = pts[g[i][j]->to];
		sum += (long long)f.first * t.second - (long long)f.second * t.first;
		i = g[i][j]->to;
		j = (j + 1) % 4;
		while (g[i][j] == NULL)
			j = (j - 1) % 4;
	} while (i != sv);
	return sum >= 0;
}

vector<int> bfs(const vector<vector<index>> &g, const vector<bool> &st)
{
	vector<int> d(g.size(), INT_MAX);
	queue<index> q;
	for (index i = 0; i < d.size(); i++)
	{
		if (st[i])
		{
			d[i] = 0;
			q.push(i);
		}
	}
	while (!q.empty())
	{
		index next = q.front();
		q.pop();
		for (auto io: g[next])
		{
			if (d[io] == INT_MAX)
			{
				d[io] = d[next] + 1;
				q.push(io);
			}
		}
	}
	return d;
}

int func(const vector<pair<int, int>> &pts, const vector<pair<int, int>> &mn, Edge *cur)
{
	return pts[cur->from].first * mn[dir(pts, cur)].first + pts[cur->from].second * mn[dir(pts, cur)].second;
}

int main()
{
#ifdef ONPC
	assert(freopen("a.in", "r", stdin));
	assert(freopen("a.out", "w", stdout));
#else
#endif
	ios::sync_with_stdio(false);
	size_t n;
	cin >> n;
	vector<pair<int, int>> pts(n);
	for (index i = 0; i < n; i++)
	{
		cin >> pts[i].first >> pts[i].second;
	}
	size_t m;
	cin >> m;
	vector<vector<Edge*>> g(n, vector<Edge*>(4, NULL));
	for (index i = 0; i < m; i++)
	{
		index l, r;
		cin >> l >> r;
		l--, r--;
		Edge *first = new Edge(l, r, i), *second = new Edge(r, l, i);
		first->pair = second;
		second->pair = first;
		g[l][dir(pts, first)] = first;
		g[r][dir(pts, second)] = second;
	}
	vector<vector<index>> ng;
	vector<bool> st;
	for (index i = 0; i < n; i++)
	{
		for (index j = 0; j < 4; j++)
		{
			if (g[i][j] != NULL and g[i][j]->my_part == (index)-1)
			{
				st.push_back(find(pts, g, i, j, ng.size()));
				ng.push_back({});
			}
		}
	}
	for (index i = 0; i < n; i++)
	{
		for (index j = 0; j < 4; j++)
		{
			if (g[i][j] != NULL)
			{
				ng[g[i][j]->my_part].push_back(g[i][j]->pair->my_part);
			}
		}
	}
	auto x = bfs(ng, st);
	vector<index> ans;
	for (index i = 0; i < n; i++)
	{
		for (index j = 0; j < 4; j++)
		{
			if (g[i][j] != NULL and g[i][j]->from < g[i][j]->to and x[g[i][j]->my_part] == x[g[i][j]->pair->my_part])
			{
				ans.push_back(g[i][j]->num);
			}
		}
	}
	cout << ans.size() << '\n';
	for (index i = 0; i < ans.size(); i++)
	{
		cout << ans[i] + 1 << '\n';
	}
}

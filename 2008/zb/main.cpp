#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib>
#include <climits>
#include <cstdio>
#include <cassert>

using namespace std;

typedef unsigned int index;


struct Edge/*{{{*/
{
	index to;
	long long sz;
	Edge(){}
	Edge(index new_to, const long long &new_sz): to(new_to), sz(new_sz){}
};/*}}}*/

vector<vector<Edge>> g;

void parse_dfs(vector<int> &color, int c_color, index v)/*{{{*/ { if (color[v] == c_color)
		return;
	color[v] = c_color;
	for (auto &i: g[v])
		parse_dfs(color, c_color, i.to);
}/*}}}*/

size_t parse(vector<int> &color)/*{{{*/
{
	int c_color = 0;
	size_t n = g.size();
	for (index i = 0; i < n; i++)
	{
		if (color[i] == INT_MAX)
		{
			parse_dfs(color, c_color, i);
			c_color++;
		}
	}
	return (size_t)c_color;
}/*}}}*/

enum Type {WHITE, GRAY, BLACK};

index fc_dfs(vector<index> &ans, index v, index p, vector<Type> &used)/*{{{*/
{
	if (used[v] == GRAY)
		return v;
	else if (used[v] == BLACK)
		return (index)-1;
	else
	{
		used[v] = GRAY;
		index anss = (index)-1;
		for (auto &i: g[v])
		{
			if (i.to != p)
				anss = min(anss, fc_dfs(ans, i.to, v, used));
		}
		if (anss != (index)-1)
			ans.push_back(v);
		used[v] = BLACK;
		if (anss != v)
			return anss;
		else
			return (index)-1;
	}
}/*}}}*/

void find_cycle(const vector<index> &comp, vector<index> &ans, vector<Edge> &eans, vector<Type> &used)/*{{{*/
{
	fc_dfs(ans, comp[0], (index)-1, used);
	if (ans.size() != 0)
	{
		for (index i = 0; i < ans.size(); i++)
		{
			for (auto &j: g[ans[i]])
				if (j.to == ans[(i + 1) % ans.size()])
					eans.push_back(j);
		}
	}
	else
	{
		for (auto i: comp)
		{
			bool flag = false;
			index i_ans = (index)-1;
			for (auto &j: g[i])/*{{{*/
			{
				if (used[j.to] == WHITE)
				{
					flag = true;
					i_ans = j.to;
					break;
				}
				used[j.to] = WHITE;
			}/*}}}*/
			if (flag)/*{{{*/
			{
				ans = {i, i_ans};
				eans.resize(2);
				flag = false;
				for (auto &j: g[i])
				{
					if (j.to == i_ans)
					{
						if (flag)
						{
							eans[1] = {i, j.sz};
						}
						else
						{
							flag = true;
							eans[0] = j;
						}
					}
				}
				return;
			}/*}}}*/
			for (auto &j: g[i])/*{{{*/
		{
				used[j.to] = BLACK;
			}/*}}}*/
		}
	}
}/*}}}*/

struct MaxStack/*{{{*/
{
	vector<pair<long long, long long>> arr;
	MaxStack(size_t){}
	
	pair<long long, long long> get()
	{
		return arr.back();
	}

	void pop()
	{
		arr.pop_back();
	}

	void push(const long long &a)
	{
		if (arr.size() == 0)
		{
			arr.push_back({a, a});
		}
		else
		{
			arr.push_back({a, max(a, arr.back().second)});
		}
	}

	size_t size()
	{
		return arr.size();
	}
};/*}}}*/

struct MaxOrder/*{{{*/
{
	MaxStack left, right;
	MaxOrder(size_t save): left(save), right(save){}

	long long get()
	{
		long long ans = LLONG_MIN;
		if (left.size() > 0)
			ans = max(ans, left.get().second);
		if (right.size() > 0)
			ans = max(ans, right.get().second);
		assert(ans > LLONG_MIN);
		return ans;
	}

	void push(const long long &a)
	{
		left.push(a);
	}

	void pop()
	{
		if (right.size() == 0)
		{
			while (left.size() > 0)
			{
				right.push(left.get().first);
				left.pop();
			}
		}
		right.pop();
	}
	
};/*}}}*/

long long fnl_dfs(vector<Type> &used, index v, long long &ans) /*{{{*/
{
	long long fmax = 0, smax = 0;
	for (auto &i: g[v])
	{
		if (used[i.to] == WHITE)
		{
			used[i.to] = BLACK;
			long long sv = fnl_dfs(used, i.to, ans) + i.sz;
			if (sv > fmax)
			{
				smax = fmax;
				fmax = sv;
			}
			else if (sv > smax)
			{
				smax = sv;
			}
			used[i.to] = WHITE;
		}
	}
	ans = max(ans, fmax + smax);
	return fmax;
}/*}}}*/

void dfs(index v, vector<index> &ans, vector<int> &used)/*{{{*/
{
	if (used[v] == -1)
		return;
	used[v] = -1;
	ans.push_back(v);
	for (auto &i: g[v])
		dfs(i.to, ans, used);
}/*}}}*/

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
	g.resize(n);
	for (index i = 0; i < n; i++)
	{
		index to;
		long long sz;
		cin >> to >> sz;
		to--;
		g[i].push_back({to, sz});
		g[to].push_back({i, sz});
	}
	vector<int> comps(n, INT_MAX);
	size_t cnt_comp = parse(comps);
	vector<index> head(cnt_comp);
	for (index i = 0; i < n; i++)
	{
		head[(index)comps[i]] = i;
	}
	long long gans = 0;
	vector<index> ccycle;
	vector<Edge> ecycle;
	vector<index> cmp;
	vector<Type> used(n, WHITE);
	for (index iter = 0; iter < cnt_comp; iter++)
	{
		cmp.resize(0);
		dfs(head[iter], cmp, comps);
		ccycle.resize(0);
		ecycle.resize(0);
		ccycle.reserve(cmp.size());
		ecycle.reserve(cmp.size());
		find_cycle(cmp, ccycle, ecycle, used);
		long long sum = 0;
		for (auto &i: ecycle)
		{
			sum += i.sz;
		}
		for (index i: cmp)
			used[i] = WHITE;
		for (index i: ccycle)
			used[i] = BLACK;
		long long lans = LLONG_MIN;
		MaxOrder mo(ccycle.size() - 1);
		for (index i = 0; i < ccycle.size() - 1; i++)
		{
			sum -= ecycle[i].sz;
			mo.push(sum + fnl_dfs(used, ccycle[i + 1], lans));
		}
		long long add = 0;
		long long sv;
		for (index i = 0; i < ccycle.size(); i++)
		{
			sv = fnl_dfs(used, ccycle[i], lans);
			lans = max(lans, mo.get() + add + sv);
			mo.pop();
			mo.push(-add + sv);
			add += ecycle[i].sz;
		}
		gans += lans;
	}
	cout << gans << endl;
}

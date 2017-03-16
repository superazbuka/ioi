#include "sorting.h" 
#include <vector>
#include <iostream>
#include <functional>

using namespace std;

typedef unsigned int index;

size_t cnt_cycles(const vector<index> &me)/*{{{*/
{
	vector<bool> used(me.size());
	std::function<void (index)> rec = [&used, &me, &rec](index v) -> void
	{
		if (used[v])
			return;
		used[v] = true;
		rec(me[v]);
	};
	size_t ans = 0;
	for (index i = 0; i < me.size(); i++)
	{
		if (!used[i])
		{
			ans++;
			rec(i);
		}
	}
	return ans;
}/*}}}*/

vector<index> use(const vector<index> &me, const vector<pair<index, index>> &swaps, size_t cnt)/*{{{*/
{
	vector<index> ans(me.begin(), me.end());
	for (index i = 0; i < cnt; i++)
	{
		swap(ans[swaps[i].first], ans[swaps[i].second]);
	}
	return ans;
}/*}}}*/

int findSwapPairs(int N, int S[], int M, int X[], int Y[], int p[], int q[]) {
	size_t n = (size_t)N, m = (size_t)M;
	vector<index> start(n);
	for (index i = 0; i < n; i++)
		start[i] = (index)S[i];
	vector<pair<index, index>> swps(m);
	for (index i = 0; i < m; i++)
		swps[i] = {(index)X[i], (index)Y[i]};
	index l = 0;
	size_t r = m + 1;
	while (r - l > 1)
	{
		size_t middle = (l + r) / 2;
		if (n - cnt_cycles(use(start, swps, m - middle)) <= m - middle)
			l = (index)middle;
		else
			r = (index)middle;
	}
	size_t ans_size = m - l;
	vector<pair<index, index>> end(n);
	vector<index> link(n);
	auto after = use(start, swps, ans_size);
	for (index i = 0; i < n; i++)
	{
		end[i] = {after[i], i};
		link[i] = i;
	}
	index yk = (index)ans_size - 1;
	for (index i = 0; i < n; i++)
	{
		while (end[i].first != i)
		{
			index j = end[i].first;
			p[yk] = (int)end[i].second;
			q[yk] = (int)end[j].second;
			swap(end[i], end[j]);
			swap(link[end[i].second], link[end[j].second]);
			swap(link[swps[yk].first], link[swps[yk].second]);
			swap(end[link[swps[yk].first]].second, end[link[swps[yk].second]].second);
			yk--;
		}
	}
	return (int)ans_size;
}

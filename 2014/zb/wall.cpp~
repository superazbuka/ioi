#include "grader.h"
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iostream>

using namespace std;

typedef unsigned int index;

pair<int, int> merge(pair<int, int> first, pair<int, int> second)
{
	if (second.second < first.first)
		return {second.second, second.second};
	else if (second.first > first.second)
		return {second.first, second.first};
	else
		return {max(first.first, second.first), min(first.second, second.second)};
}

void build(index v, index tl, size_t tr, pair<int, int> *tree)
{
	tree[v] = {0, 1e9};
	if (tr - tl == 1)
		return;
	size_t tm = (tl + tr) / 2;
	build(2 * v + 1, tl, tm, tree);
	build(2 * v + 2, (index)tm, tr, tree);
}

void push(index v, pair<int, int> *tree)
{
	tree[2 * v + 1] = merge(tree[2 * v + 1], tree[v]);
	tree[2 * v + 2] = merge(tree[2 * v + 2], tree[v]);
	tree[v] = {0, 1e9};
}

void add(index v, index tl, size_t tr, index l, size_t r, pair<int, int> x, pair<int, int> *tree)
{
	if (l >= tr or r <= tl)
		return;
	if (tl >= l and tr <= r)
	{
		tree[v] = merge(tree[v], x);
		return;
	}
	push(v, tree);
	size_t tm = (tl + tr) / 2;
	add(2 * v + 1, tl, tm, l, r, x, tree);
	add(2 * v + 2, (index)tm, tr, l, r, x, tree);
}

void ans(index v, index tl, size_t tr, pair<int, int> *tree, int *finalHeight)
{
	if (tr - tl == 1)
	{
		finalHeight[tl] = tree[v].first;
		return;
	}
	push(v, tree);
	size_t tm = (tl + tr) / 2;
	ans(2 * v + 1, tl, tm, tree, finalHeight);
	ans(2 * v + 2, (index)tm, tr, tree, finalHeight);
}

void buildWall(int N, int K, int op[], int left[], int right[], int height[], int finalHeight[])
{
	size_t n = N, k = K;
	pair<int, int> *tree = new pair<int, int>[4 * n - 1];
	build(0, 0, n, tree);
	for (index i = 0; i < n; i++)
	{
		add(0, 0, n, i, i + 1, {0, 0}, tree);
	}
	for (index i = 0; i < k; i++)
	{
		if (op[i] == 1)
		{
			add(0, 0, n, (index)left[i], (size_t)right[i] + 1, {height[i], 1e9}, tree);
		}
		else
		{
			add(0, 0, n, (index)left[i], (size_t)right[i] + 1, {0, height[i]}, tree);
		}
	}
	ans(0, 0, n, tree, finalHeight);
	return;
}


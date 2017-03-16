#include "horses.h"
#include <cmath>
#include <climits>
#include <cassert>
#include <cstdlib>
#include <iostream>

using namespace std;

typedef unsigned int index;
typedef double FloatType;

const int MOD = (int)1e9 + 7;

struct ElementOfTree/*{{{*/
{
	int prodx;
	FloatType sum, max_suf;
	ElementOfTree(){}

	ElementOfTree(int new_prodx, FloatType new_sum, FloatType new_max_suf): prodx(new_prodx), sum(new_sum), max_suf(new_max_suf){}
};/*}}}*/

void upd(index v, ElementOfTree *tree)/*{{{*/
{
	tree[v] = {(int)(((long long)tree[2 * v + 1].prodx * tree[2 * v + 2].prodx) % MOD), tree[2 * v + 1].sum + tree[2 * v + 2].sum,
		max(tree[2 * v + 1].max_suf, tree[2 * v + 1].sum + tree[2 * v + 2].max_suf)
	};
}/*}}}*/

void build(index v, index tl, size_t tr, ElementOfTree *tree, int *x, int *y)/*{{{*/
{
	if (tr - tl == 1)
	{
		tree[v] = {x[tl], log((FloatType)x[tl]), log((FloatType)x[tl]) + log((FloatType)y[tl])};
		return;
	}
	size_t tm = (tl + tr) / 2;
	build(2 * v + 1, tl, tm, tree, x, y);
	build(2 * v + 2, (index)tm, tr, tree, x, y);
	upd(v, tree);
}/*}}}*/

int ans(index v, index tl, size_t tr, ElementOfTree *tree, int *y)/*{{{*/
{
	if (tr - tl == 1)
	{
		return (int)(((long long)tree[v].prodx * y[tl]) % MOD);
	}
	if (tree[2 * v + 1].max_suf > tree[2 * v + 1].sum + tree[2 * v + 2].max_suf)
		return ans(2 * v + 1, tl, (tl + tr) / 2, tree, y);
	else
		return (int)(((long long)ans(2 * v + 2, (index)(tl + tr) / 2, tr, tree, y) * tree[2 * v + 1].prodx) % MOD);
}/*}}}*/

void upd(index v, index tl, size_t tr, index pos, ElementOfTree *tree, int *x, int *y)/*{{{*/
{
	if (pos < tl or pos >= tr)
		return;
	if (tr - tl == 1)
	{
		tree[v] = {x[tl], log((FloatType)x[tl]), log((FloatType)x[tl]) + log((FloatType)y[tl])};
		return;
	}
	size_t tm = (tl + tr) / 2;
	upd(2 * v + 1, tl, tm, pos, tree, x, y);
	upd(2 * v + 2, (index)tm, tr, pos, tree, x, y);
	upd(v, tree);
}/*}}}*/

ElementOfTree *tree;
int *x, *y;
size_t n;

int init(int N, int X[], int Y[]) /*{{{*/
{
	n = (size_t)N;
	x = new int[n];
	y = new int[n];
	for (index i = 0; i < n; i++)
	{
		x[i] = X[i];
		y[i] = Y[i];
	}
	tree = new ElementOfTree[4 * n];
	build(0, 0, n, tree, x, y);
	return ans(0, 0, n, tree, y);
}/*}}}*/

int updateX(int pos, int val) /*{{{*/
{
	x[(index)pos] = val;
	upd(0, 0, n, (index)pos, tree, x, y);
	return ans(0, 0, n, tree, y);
}/*}}}*/

int updateY(int pos, int val)/*{{{*/
{
	y[(index)pos] = val;
	upd(0, 0, n, (index)pos, tree, x, y);
	return ans(0, 0, n, tree, y);
}/*}}}*/

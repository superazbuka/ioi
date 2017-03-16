#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cassert>

using namespace std;

typedef unsigned int index;

struct Item/*{{{*/
{
	Item *l, *r;
	size_t size;
	int prior, zn, sum;
	Item(int new_zn): l(NULL), r(NULL), size(1), prior(rand()), zn(new_zn), sum(new_zn){}
};/*}}}*/

typedef Item* Pitem;

void upd(Pitem t)/*{{{*/
{
	if (t == NULL)
		return;
	t->sum = t->zn +
		(t->l != NULL ? t->l->sum : 0) +
		(t->r != NULL ? t->r->sum : 0);
	t->size = (t->l != NULL ? t->l->size : 0) +
		(t->r != NULL ? t->r->size : 0) + 1;
}/*}}}*/

size_t get_size(Pitem t)/*{{{*/
{
	if (t == NULL)
		return 0;
	else
		return t->size;
}/*}}}*/

int get_sum(Pitem t)/*{{{*/
{
	if (t == NULL)
		return 0;
	else
		return t->sum;
}/*}}}*/

void upd(Pitem t, index i, int add)/*{{{*/
{
	if (get_size(t->l) == i)
	{
		t->zn += add;
	}
	else
	{
		if (get_size(t->l) > i)
			upd(t->l, i, add);
		else
			upd(t->r, i - (index)get_size(t->l) - 1, add);
	}
	upd(t);
}/*}}}*/

void split(Pitem t, Pitem &l, Pitem &r, int mn)/*{{{*/
{
	if (!t)
	{
		l = NULL;
		r = NULL;
	}
	else
	{
		if (get_sum(t->l) >= mn)
		{
			split(t->l, l, t->l, mn);
			r = t;
			upd(r);
		}
		else
		{
			split(t->r, t->r, r, mn - get_sum(t->l) - t->zn);
			l = t;
			upd(l);
		}
	}
}/*}}}*/

void merge(Pitem &t, Pitem l, Pitem r)/*{{{*/
{
	if (l == NULL)
		t = r;
	else if (r == NULL)
		t = l;
	else
	{
		if (l->prior < r->prior)
		{
			merge(l->r, l->r, r);
			t = l;
		}
		else
		{
			merge(r->l, l, r->l);
			t = r;
		}
	}
	upd(t);
}/*}}}*/

void push_left(Pitem &t, Item *l)/*{{{*/
{
	if (t == NULL)
		t = l;
	else if (t->prior > l->prior)
	{
		l->r = t;
		t = l;
	}
	else
	{
		push_left(t->l, l);
	}
	upd(t);
}/*}}}*/

int pop_left(Pitem &t)/*{{{*/
{
	int ans;
	if (t->l == NULL)
	{
		ans = t->zn;
		t = t->r;
	}
	else
	{
		ans = pop_left(t->l);
	}
	upd(t);
	return ans;
}/*}}}*/

long long ans(Pitem t, index &pos)
{
	if (t == NULL)
		return 0;
	long long cans = 0;
	cans += ans(t->l, pos);
	cans += (long long)pos * ((long long)pos - 1) * t->zn;
	pos++;
	cans += ans(t->r, pos);
	return cans;
}

void out(Pitem t)
{
	if (t == NULL)
		return;
	out(t->l);
	cout << t->zn << " ";
	out(t->r);
}

int main()
{
#ifdef ONPC
	assert(freopen("a.in", "r", stdin));
	assert(freopen("a.out", "w", stdout));
#else
#endif
	size_t n;
	cin >> n;
	vector<pair<int, int>> sails(n);
	for (auto &i: sails)
		cin >> i.first >> i.second;
	sort(sails.begin(), sails.end());
	Pitem root = new Item(0);
	for (index i = 0; i < n; i++)
	{
		upd(root, 0, sails[i].first - root->sum);
		Pitem l, r;
		split(root, l, r, sails[i].second);
		int over = get_sum(l) - sails[i].second;
		push_left(l, new Item(0));
		upd(l, (index)get_size(l) - 1, -over);
		upd(l, (index)get_size(l) - 2, +over);
		if (r != NULL)
		{
			upd(l, (index)get_size(l) - 1, pop_left(r));
		}
		merge(root, l, r);
	}
	index pos = 0;
	cout << ans(root, pos) / 2 << endl;
}

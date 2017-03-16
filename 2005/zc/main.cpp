#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

struct item
{
	int cur, sum;
	int maxt;
	item *l, *r;
	bool f;
	item()
	{
		f = false;
		sum = 0;
		cur = 0;
		l = NULL;
		r = NULL;
		maxt = 0;
	}
};

typedef item * pitem;

void push(pitem &it, int tl, int tr)
{
	if (it->f)
	{
		int tm = (tl + tr) / 2;
		if (it->l == NULL)
		{
			it->l = new item();
		}
		if (it->r == NULL)
		{
			it->r = new item();
		}
		it->l->cur = it->cur;
		it->l->sum = it->cur * (tm - tl + 1);
		it->l->maxt = max(0, it->l->sum);
		it->r->cur = it->cur;
		it->r->sum = it->cur * (tr - tm );
		it->r->maxt = max(0, it->r->sum);
		it->l->f = true;
		it->r->f = true;
		it->f = false;
	}
	else
	{
		if (it->l == NULL)
		{
			it->l = new item();
		}
		if (it->r == NULL)
		{
			it->r = new item();
		}
	}
}

void rav(pitem &v, int tl, int tr, int l, int r, int x)
{
	if (tr < l or tl > r)
		return;
	if (tl >= l and tr <= r)
	{
		v->f = true;
		v->cur = x;
		v->sum = (tr - tl + 1) * x;
		v->maxt = max(v->sum, 0);
		return;
	}
	push(v, tl, tr);
	int tm = (tl + tr) / 2;
	rav(v->l, tl, tm, l, r, x), rav(v->r, tm + 1, tr, l, r, x);
	v->sum = v->l->sum + v->r->sum;
	v->maxt = max(v->l->maxt, v->r->maxt + v->l->sum);
}

int pos(pitem v, int tl, int tr, int k)
{
	push(v, tl, tr);
	if (tl == tr)
	{
		if (k >= v->sum)
			return tl;
		else
			return tl - 1;
	}
	int suml = v->l->sum;
	int maxl = v->l->maxt;
	int tm = (tl + tr) / 2;
	if (maxl <= k)
	{
		return pos(v->r, tm + 1, tr, k - suml);
	}
	else
	{
		return pos(v->l, tl, tm, k);
	}
}

int main()
{
	#ifdef ONPC
		freopen("a.in", "r", stdin);
		freopen("a.out", "w", stdout);
	#endif
	int n;
	cin >> n;
	char t;
	pitem root = new item();
	while (cin >> t and t != 'E')
	{
		if (t == 'I')
		{
			int l, r, d;
			cin >> l >> r >> d;
			l--, r--;
			rav(root, 0, n - 1, l, r, d);
		}
		else
		{
			int powe;
			cin >> powe;
			cout << pos(root, 0, n - 1, powe) + 1 << endl;
		}
	}
	return 0;
}

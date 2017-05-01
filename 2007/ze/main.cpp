#include <iostream>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned int index;

long long sol_1(vector<int> &d, int dist)/*{{{*/
{
	sort(d.begin(), d.end());
	index l = (index)-1;
	size_t n = d.size();
	long long ans = 0;
	for (index i = 0; i < n; i++)
	{
		while (l + 1 < n and d[i] - d[l + 1] > dist)
			l++;
		ans += (int)(i - l - 1);
	}
	return ans;
}/*}}}*/

template<class Element> class RangeTree/*{{{*/
{
	private:
		Element *elements;/*{{{*/
		std::pair<index, index> *childrens;
		size_t my_size;
		std::function<Element (const Element&, const Element&)> func;/*}}}*/

		index build(index tl, size_t tr, index &last)/*{{{*/
		{
			if (tr - tl == 1)
			{
				return my_size + tl - 1;
			}
			index v = last;
			last++;
			size_t tm = (tl + tr) / 2;
			childrens[v] = {build(tl, tm, last), build(tm, tr, last)};
			elements[v] = func(elements[childrens[v].first], elements[childrens[v].second]); 
			return v;
		}/*}}}*/

		Element get(index v, index tl, size_t tr, index l, size_t r)/*{{{*/
		{
			if (l <= tl and tr <= r)
			{
				return elements[v];
			}
			size_t tm = (tl + tr) / 2;
			if (tm <= l)
			{
				return get(childrens[v].second, (index)tm, tr, l, r);
			}
			else if (tm >= r)
			{
				return get(childrens[v].first, tl, tm, l, r);
			}
			else
			{
				return func(get(childrens[v].first, tl, tm, l, r), get(childrens[v].second, (index)tm, tr, l, r));
			}
		}/*}}}*/

		void set(index v, index tl, size_t tr, index pos, const Element &el)/*{{{*/
		{
			if (pos < tl or pos >= tr)
				return;
			if (tr - tl == 1)
			{
				elements[v] = el;
				return;
			}
			size_t tm = (tl + tr) / 2;
			set(childrens[v].first, tl, tm, pos, el);
			set(childrens[v].second, (index)tm, tr, pos, el);
			elements[v] = func(elements[childrens[v].first], elements[childrens[v].second]); 
		}/*}}}*/

	public:
		template<class T> RangeTree(const T &begin, const T &end, const std::function<Element (const Element&, const Element&)> &new_func): my_size(0), func(new_func)/*{{{*/
		{
			for (T i = begin; i != end; i++)
				my_size++;
			assert(my_size > 0);
			elements = new Element[my_size * 2 - 1];
			childrens = new std::pair<index, index>[my_size - 1];
			index j = 0;
			for (T i = begin; i != end; i++, j++)
			{
				elements[j + my_size - 1] = *i;
			}
			index last = 0;
			build(0, my_size, last);
		}/*}}}*/

		Element get(index l, size_t r)/*{{{*/
		{
			return get(0, 0, my_size, l, r);
		}/*}}}*/

		size_t size()/*{{{*/
		{
			return my_size;
		}/*}}}*/
		
		void set(index pos, const Element &el)/*{{{*/
		{
			set(0, 0, my_size, pos, el);
		}/*}}}*/

};/*}}}*/

long long sol_2(vector<vector<int>> &d, int dist)/*{{{*/
{
	size_t n = d.size();
	const int PLUS = 75000;
	vector<int> emp(PLUS * 2 + 1);
	RangeTree<long long> rt(emp.begin(), emp.end(), [](long long a, long long b) -> long long {return a + b;});
	vector<vector<int>> c(n);
	function<bool (vector<int>, vector<int>)> les = [](const vector<int> &a, const vector<int> &b){return a[0] + a[1] < b[0] + b[1];};
	sort(d.begin(), d.end(), les);
	for (index i = 0; i < n; i++)
	{
		c[i] = {d[i][0] + dist / 2 + dist % 2, d[i][1] + dist / 2};
	}
	index l = (index)-1;
	long long ans = 0;
	for (index i = 0; i < n; i++)
	{
		while (l + 1 < n and les(c[l + 1], d[i]))
		{
			index cns = (index)(c[l + 1][0] - c[l + 1][1] + PLUS);
			rt.set(cns, rt.get(cns, cns + 1) - 1);
			l++;
		}
		{
			index cns = (index)(c[i][0] - c[i][1] + PLUS);
			index le = (index)max(0, ((int)cns - dist));
			size_t re = min((index)PLUS * 2 + 1, (cns + (index)dist + 1));
			ans += rt.get(le, re);
			rt.set(cns, rt.get(cns, cns + 1) + 1);
		}
	}
	return ans;
}/*}}}*/

int get(const vector<vector<int>> &ps, index lx, index ly, index rx, index ry)
{
	return ps[rx][ry] - ps[lx][ry] - ps[rx][ly] + ps[lx][ly];
}

void rcnt(vector<vector<int>> &ps, index x, index y)
{
	x++, y++;
	ps[x][y] = ps[x][y] + ps[x - 1][y] + ps[x][y - 1] - ps[x - 1][y - 1];
}

long long sol_3(vector<vector<int>> &d, int dist)
{
	const size_t n = 75;
	vector<vector<vector<int>>> ps(n + 1, vector<vector<int>>(2 * n + 2, vector<int>(2 * n + 2, 0)));
	for (auto &i: d)
	{
		i = {i[0], i[1] - i[2] + (int)n, i[1] + i[2]};
	}
	sort(d.begin(), d.end());
	long long ans = 0;
	vector<int> cp = {0, 0, 0};
	for (index i = 0; i < d.size(); i++)
	{
		while (cp <= vector<int>{(int)n, 2 * (int)n + 1, 2 * (int)n + 1} and cp < d[i])
		{
			rcnt(ps[(index)cp[0]], (index)cp[1], (index)cp[2]);
			cp[2]++;
			if (cp[2] == 2 * n + 1)
			{
				cp[2] = 0;
				cp[1]++;
				if (cp[1] == 2 * n + 1)
				{
					cp[1] = 0;
					cp[0]++;
				}
			}
		}
		index cx = (index)d[i][1];
		index cy = (index)d[i][2];
		for (int j = 0; j <= d[i][0]; j++)
		{
			int cdist = dist - (d[i][0] - (int)j);
			if (cdist < 0)
				continue;
			index lx = (index)max((int)cx - cdist, 0);
			index ly = (index)max((int)cy - cdist, 0);
			index rx = (index)min((int)cx + cdist + 1, 2 * (int)n + 1);
			index ry = (index)min((int)cy + cdist + 1, 2 * (int)n + 1);
			if (j == d[i][0])
			{
				ans += get(ps[(index)j], lx, ly, cx, ry);
				ans += get(ps[(index)j], cx, ly, cx + 1, cy);
				ans += ps[(index)d[i][0]][cx + 1][cy + 1];
			}
			else
			{
				ans += get(ps[(index)j], lx, ly, rx, ry);
			}
		}
		ps[(index)d[i][0]][cx + 1][cy + 1]++;
	}
	return ans;
}

int main()
{
#ifdef ONPC
	assert(freopen("a.in", "r", stdin));
	assert(freopen("a.out", "w", stdout));
#else
#endif
	size_t b;
	cin >> b;
	if (b == 1)
	{
		size_t n;
		cin >> n;
		int d, m;
		cin >> d >> m;
		vector<int> c(n);
		for (auto &i: c)
			cin >> i;
		cout << sol_1(c, d) << endl;
	}
	if (b == 2)
	{
		size_t n;
		cin >> n;
		int d, m;
		cin >> d >> m;
		vector<vector<int>> c(n, vector<int>(2));
		for (auto &i: c)
			cin >> i[0] >> i[1];
		cout << sol_2(c, d) << endl;
	}
	if (b == 3)
	{
		size_t n;
		cin >> n;
		int d, m;
		cin >> d >> m;
		vector<vector<int>> c(n, vector<int>(3));
		for (auto &i: c)
			cin >> i[0] >> i[1] >> i[2];
		cout << sol_3(c, d) << endl;
	}
}

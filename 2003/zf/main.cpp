#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <functional>

using namespace std;

typedef unsigned int index;
typedef long long FloatType;

struct Point
{
	FloatType x, y;
	Point(){};
	Point(FloatType new_x, FloatType new_y): x(new_x), y(new_y){}
};

struct Vector
{
	FloatType x, y;
	Vector(FloatType new_x, FloatType new_y): x(new_x), y(new_y){}
};

Vector operator -(const Point &a, const Point &b)
{
	return {a.x - b.x, a.y - b.y};
}

FloatType cross_product(const Vector &a, const Vector &b)
{
	return a.x * b.y - a.y * b.x;
}

enum LinePositions {IN_ONE, NORMAL, ANOMAL};

LinePositions get(const Point &a, const Point &b)
{
	bool fu = (a.x >= a.y),
		 su = (b.x >= b.y);
	if (fu != su)
	{
		if (!fu)
			return ANOMAL;
		else
			return NORMAL;
	}
	else
		return IN_ONE;
}

struct NCmp
{
	Point center;
	NCmp(Point new_center): center(new_center){}
	bool operator ()(const Point &a, const Point &b)
	{
		return cross_product(a - center, b - center) > 0;
	}
};

struct Cmp
{
	Point center;
	Cmp(Point new_center): center(new_center){}
	bool operator ()(const Point &a, const Point &b)
	{
		LinePositions al = get(a, b);
		if (al == ANOMAL)
			return false;
		if (al == NORMAL)
			return true;
		return cross_product(a - center, b - center) > 0;
	}
};

enum QType {OPEN = 0, CLOSE = 1};
struct PairCmp
{
	Point center;
	PairCmp(Point new_center): center(new_center){}
	bool operator ()(const pair<Point, QType> &fa, const pair<Point, QType> &fb)
	{
		Point a = fa.first, b = fb.first;
		if (cross_product(a - center, b - center) == 0)
		{
			return (fa.second == OPEN and fb.second == CLOSE);
		}
		LinePositions al = get(a, b);
		if (al == ANOMAL)
			return false;
		if (al == NORMAL)
			return true;
		return cross_product(a - center, b - center) > 0;
	}
};


int main()
{
#ifdef ONPC
	assert(freopen("a.in", "r", stdin));
	assert(freopen("a.out", "w", stdout));
#else
#endif
	size_t n, k;
	cin >> n >> k;
	vector<pair<Point, QType>> otr;
	Point center;
	cin >> center.x >> center.y;
	Cmp comp(center);
	PairCmp p_comp(center);
	NCmp n_comp(center);
	for (index i = 0; i < k; i++)
	{
		size_t cs;
		cin >> cs;
		vector<Point> cur(cs);
		for (auto &j: cur)
			cin >> j.x >> j.y;
		sort(cur.begin(), cur.end(), n_comp);
		otr.push_back({cur[0], OPEN});
		otr.push_back({cur[cur.size() - 1], CLOSE});
	}
	sort(otr.begin(), otr.end(), p_comp);
	size_t bal = 0;
	size_t ans = 0;
	index pos = 0;
	vector<function<Point (index)>> tps = {
		[n](index i) -> Point {return {i, 0};},
		[n](index i)-> Point {return {(long long)n, (long long)i};},
		[n](index i)-> Point {return {(long long)n - i, (long long)n};},
		[n](index i)-> Point {return {(long long)0, (long long)n - i};},
	};
	for (auto fnc: tps)
	{
		for (index i = 0; i < n; i++)
		{
			Point cur_point = fnc(i);
			while (pos < otr.size() and (comp(otr[pos].first, cur_point) or (cross_product(otr[pos].first - center, cur_point - center) == 0 and otr[pos].second == OPEN)))
			{
				if (otr[pos].second == OPEN)
					bal++;
				else
					bal--;
				pos++;
			}
			if (bal == 0)
			{
				ans++;
			}
		}
	}
	cout << ans << endl;
}

#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cassert>

using namespace std;

typedef unsigned int index;

enum TurnType/*{{{*/
{
	HEAVIEST,
	LIGHTEST,
	MEDIAN,
	NEXT_LIGHTEST
};/*}}}*/

struct Turn/*{{{*/
{
	TurnType t;
	index a, b, c, d;
	Turn(TurnType new_t, index new_a, index new_b, index new_c): t(new_t), a(new_a), b(new_b), c(new_c){}

	Turn(TurnType new_t, index new_a, index new_b, index new_c, index new_d): t(new_t), a(new_a), b(new_b), c(new_c), d(new_d){}
};/*}}}*/

struct Permutation/*{{{*/
{
	index *array;
	static const size_t SIZE = 5;
	Permutation(const vector<index> na)
	{
		array = new index[SIZE];
		for (index i = 0; i < SIZE; i++)
			array[i] = na[i];
	}

	index operator [](index i) const
	{
		return array[i];
	}
};/*}}}*/

index use(const Permutation &a, const Turn &b)/*{{{*/
{
	if (b.t == HEAVIEST)
	{
		index max = b.a;
		if (a[b.b] > a[max])
			max = b.b;
		if (a[b.c] > a[max])
			max = b.c;
		return max;
	}
	else if (b.t == LIGHTEST)
	{
		index min = b.a;
		if (a[b.b] < a[min])
			min = b.b;
		if (a[b.c] < a[min])
			min = b.c;
		return min;
	}
	else if (b.t == MEDIAN)
	{
		if ((a[b.a] > a[b.b] and a[b.a] < a[b.c]) or (a[b.a] < a[b.b] and a[b.a] > a[b.c]))
			return b.a;
		else if ((a[b.b] > a[b.a] and a[b.b] < a[b.c]) or (a[b.b] < a[b.a] and a[b.b] > a[b.c]))
			return b.b;
		else
			return b.c;
	}
	else
	{
		index min = b.a;
		if (a[b.b] < a[min])
			min = b.b;
		if (a[b.c] < a[min])
			min = b.c;
		if (a[b.b] < a[min] and a[b.b] > a[b.d])
			min = b.b;
		if (a[b.c] < a[min] and a[b.c] > a[b.d])
			min = b.c;
		return min;
	}
}/*}}}*/

size_t gen(const vector<index> &possible, const vector<Permutation> &all_perm, const vector<Turn> &all_turns, map<vector<index>, size_t> &mp)
{
	auto tmp = mp.find(possible);
	if (tmp != mp.end())
		return tmp->second;
	else
	{
		if (possible.size() == 1)
			mp[possible] = 1;
		else
		{
			size_t bans = 20;
			size_t best = 0;
			size_t st = 1;
			while (st < possible.size())
			{
				best++;
				st *= 3;
			}
			for (index i = 0; i < all_turns.size() and bans > best; i++)
			{
				vector<index> a, b, c;
				for (auto j: possible)
				{
					index sv = use(all_perm[j], all_turns[i]);
					if (sv == all_turns[i].a)
						a.push_back(j);
					else if (sv == all_turns[i].b)
						b.push_back(j);
					else
						c.push_back(j);
				}
				if (a.size() == possible.size() or b.size() == possible.size() or c.size() == possible.size())
					continue;
				size_t mmax = 0;
				if (a.size() > 0)
					mmax = max(gen(a, all_perm, all_turns, mp), mmax);
				if (b.size() > 0 and mmax + 1 < bans)
					mmax = max(gen(b, all_perm, all_turns, mp), mmax);
				if (c.size() > 0 and mmax + 1 < bans)
					mmax = max(gen(c, all_perm, all_turns, mp), mmax);
				bans = min(bans, mmax + 1);
			}
			mp[possible] = bans;
		}
	}
	return mp[possible];
}

int main()
{
#ifdef ONPC
	assert(freopen("generated.cpp", "w", stdout));
#else
#endif
	ios::sync_with_stdio(false);
	const size_t SIZE = 5;
	vector<index> a;
	for (index i = 0; i < SIZE; i++)
		a.push_back(i);
	vector<index> posibble;
	vector<Permutation> perms;
	index i = 0;
	do
	{
		perms.push_back({a});
		posibble.push_back(i);
		i++;
	}
	while (next_permutation(a.begin(), a.end()));
	vector<TurnType> types = {LIGHTEST, MEDIAN, HEAVIEST};
	vector<Turn> all_turns;
	
	for (auto type: types)
	{
		for (index i1 = 0; i1 < SIZE; i1++)
			for (index i2 = i1; i2 < SIZE; i2++)
				for (index i3 = i2; i3 < SIZE; i3++)
					all_turns.push_back({type, i1, i2, i3});
	}
	for (index i1 = 0; i1 < SIZE; i1++)
		for (index i2 = i1; i2 < SIZE; i2++)
			for (index i3 = i2; i3 < SIZE; i3++)
				for (index d = 0; d < SIZE; d++)
					if (d != i1 and d != i2 and d != i3)
						all_turns.push_back({NEXT_LIGHTEST, i1, i2, i3, d});
	map<vector<index>, size_t> mp;
	cerr << gen(posibble, perms, all_turns, mp) << endl;
}

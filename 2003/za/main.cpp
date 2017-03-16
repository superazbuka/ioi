#include <iostream>
#include <set>
#include <cstdio>
#include <cstdlib>
#include <climits>

using namespace std;

int dsu[205];

void build()
{
	for (int i = 0; i < 205; i++)
	{
		dsu[i] = i;
	}
}

int get(int a)
{
	if (dsu[a] != a)
	{
		dsu[a] = get(dsu[a]);
	}
	return dsu[a];
}

void unite(int a, int b)
{
	a = get(a);
	b = get(b);
	if (a == b)
		return;
	if (rand() % 2)
		swap(a, b);
	dsu[a] = b;
}

set<pair<int, pair<int, int> > > rel;

int main()
{
	#ifdef ONPC
		freopen("a.in", "r", stdin);
		freopen("a.out", "w", stdout);
	#endif
	
	int n, w;
	cin >> n >> w;
	for (int i = 0; i < w; i++)
	{
		int l, r, w;
		cin >> l >> r >> w;
		l--, r--;
		rel.insert({w, {l, r}});
		build();
		int cnt = 0;
		int ans = 0;
		for (auto i : rel)
		{
			if (cnt == n - 1)
				break;
			if (get(i.second.first) != get(i.second.second))
			{
				cnt++;
				ans += i.first;
				unite(i.second.first, i.second.second);
			}
		}
		if (cnt == n - 1)
			cout << ans << endl;
		else
			cout << -1 << endl;
	}
}

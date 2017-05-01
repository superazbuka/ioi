#include <iostream>
#include <functional>
#include <set>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cassert>

using namespace std;

typedef unsigned int index;

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
	vector<index> arr(n);
	for (auto &i: arr)
		cin >> i;
	set<index, function<bool (const index&, const index&)>> rz([&arr](const index &a, const index &b) ->bool
			{
				return arr[a] - a < arr[b] - b or (arr[a] - a == arr[b] - b and a > b);
			});
	vector<index> ds;
	vector<index> up;
	vector<index> as(n, (index)-1);
	for (index i = 0; i < n; i++)
	{
		while (ds.size() and arr[ds.back()] < arr[i])
			ds.pop_back();
		index from = 0;
		if (ds.size())
			from = ds.back();
		ds.push_back(i);
		while (up.size() and arr[up.back()] > arr[i])
		{
			rz.erase(up.back());
			up.pop_back();
		}
		up.push_back(i);
		auto x = rz.lower_bound(i);
		if (x != rz.end())
		{
			index cur = *x;
			if (arr[cur] - cur == arr[i] - i)
			{
				if (cur >= from)
				{
					as[i] = cur;
					rz.erase(cur);
				}
			}
		}
		rz.insert(i);
	}
	vector<pair<index, index>> ans;
	index ls = 0;
	for (index i = 0; i < n; i++)
	{
		if (as[i] != (index)-1 and as[i] >= ls)
		{
			ls = i;
			ans.push_back({as[i], i});
		}
	}
	cout << ans.size() << '\n';
	for (auto i: ans)
	{
		cout << i.first + 1 << " " << i.second + 1 << '\n';
	}
}

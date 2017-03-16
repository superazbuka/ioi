#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <map>
#include <set>
#include <vector>


using namespace std;

#ifdef ONPC
const size_t CNTT = 1e7;
#else
const size_t CNTT = 7e4;
#endif

typedef unsigned int index;

struct ans_t
{
	int cnt;
	index q, t;
	ans_t(){}
	ans_t(int s_cnt, index s_q, index s_t): cnt(s_cnt), q(s_q), t(s_t){}
};

vector<vector<char> > cws;
map<long long, ans_t> mem;
vector<set<char> > q = {{'X'}, {'Y'}, {'Z'}, {'X', 'Y'}, {'Y', 'Z'}, {'X', 'Z'}, {'X', 'Y', 'Z'}};
index cnt = 0;

ans_t pe(const vector<index> &sp, long long p)
{
	if (cnt >= CNTT)
		return {(int)1e9, 0, 0};
	if (sp.size() == 1)
		return {0, 0, 0};
	if (mem.find(p) != mem.end())
		return mem[p];
	cnt++;
	int ans = 1e9;
	pair<index, index> best;
	vector<index> y, n;
	for (index i = 0; i < cws[0].size(); i++)
	{
		for (index j = 0; j < q.size() and cnt < CNTT; j++)
		{
			y.resize(0);
			n.resize(0);
			long long yp = 0, np = 0;
			for (index k = 0; k < sp.size(); k++)
			{
				if (q[j].count(cws[sp[k]][i]) == 1)
				{
					y.push_back(sp[k]);
					yp += (1ll << (sp[k]));
				}
				else
				{
					n.push_back(sp[k]);
					np += (1ll << (sp[k]));
				}
			}
			if (y.size() and n.size())
			{
				int cur = max(pe(y, yp).cnt, pe(n, np).cnt) + 1;
				if (cur < ans)
				{
					ans = cur;
					best = {i, j};
				}
			}
		}
	}
	mem[p] = {ans, best.second, best.first};
	return mem[p];
}

vector<index> er(const vector<index> &sp, pair<index, index> qs, bool a)
{
	vector<index> ans;
	for (index k = 0; k < sp.size(); k++)
	{
		if ((q[qs.second].count(cws[sp[k]][qs.first]) == 1) xor !a)
			ans.push_back(sp[k]);
	}
	return ans;
}

int main()
{
#ifdef ONPC
	//assert(freopen("a.in", "r", stdin));
	//assert(freopen("a.out", "w", stdout));
#else
#endif
	size_t ns, p;
	cin >> ns >> p;
	cws.resize(ns);
	vector<index> q1;
	long long p1 = (1 << ns) - 1;
	for (index i = 0; i < ns; i++)
	{
		cws[i].resize(p);
		for (index j = 0; j < p; j++)
		{
			cin >> cws[i][j];
		}
		q1.push_back(i);
	}
	pe(q1, p1);
	while (q1.size() != 1)
	{
		set<char> cur = q[mem[p1].q];
		cout << "Q " << mem[p1].t + 1 << " ";
		for (auto i: cur)
			cout << i << " ";
		cout << endl;
		bool c;
		cin >> c;
		q1 = er(q1, {mem[p1].t, mem[p1].q}, c);
		p1 = 0;
		for (index i = 0; i < q1.size(); i++)
			p1 += (1ll << q1[i]);
	}
	cout << "C " << q1[0] + 1 << endl;
}


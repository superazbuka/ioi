#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <climits>

using namespace std;

int a[256];
int b[256];
int diff = 0;
string s;

void out()
{
	#ifdef ONPC
		int cnt = 0;
		for (int i = 0; i < 256; i++)
		{
			if (a[i] - b[i] != 0)
				cnt++;
		}
		cout << diff << " " << cnt << endl;
	#endif
}

void refa(int i, int num)
{
	if (a[i] - b[i] == 0)
	{
		diff++;
	}
	a[i] += num;
	if (a[i] - b[i] == 0)
	{
		diff--;
	}
}

void refb(int i, int num)
{
	if (a[i] - b[i] == 0)
	{
		diff++;
	}
	b[i] += num;
	if (a[i] - b[i] == 0)
	{
		diff--;
	}
}


int main()
{
	#ifdef ONPC
		freopen("a.in", "r", stdin);
		freopen("a.out", "w", stdout);
	#else
		//freopen("writing.in", "r", stdin);
		//freopen("writing.out", "w", stdout);
	#endif
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		char x;
		cin >> x;
		refa(x, 1);
	}
	cin >> s;
	for (int i = 0; i < n - 1; i++)
	{
		out();
		refb(s[i], 1);
	}
	int ans = 0;
	for (int i = n - 1; i < m; i++)
	{
		out();
		refb(s[i], 1);
		if (diff == 0)
			ans++;
		refb(s[i - n + 1], -1);
	}
	cout << ans << endl;
	return 0;
}

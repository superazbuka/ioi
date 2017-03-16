#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <climits>

using namespace std;

int main()
{
	#ifdef ONPC
		freopen("a.in", "r", stdin);
		freopen("a.out", "w", stdout);
	#endif
	int n, k;
	cin >> k >> n;
	cout << "FILE reverse " << k << endl;
	int turn = n / 8 + (n % 8 > 0 ? 1 : 0)  + (n == 0 ? 1 : 0);
	for (int i = 0; i < 8; i++)
	{
		cout << turn * i << " ";
	}
	cout << 0 << endl;
	int tec = 7;
	for (int q = n; q >= 0; q--)
	{
		while (turn * tec > q)
			tec--;
		int cur = turn * tec;
		if (cur == q)
		{
			cout << "P " << tec + 1 << endl;
			continue;
		}
		cout << "S " << tec + 1 << " " << 9 << endl;
		cur++;
		while (cur < q)
		{
			cout << "S 9 9" << endl;
			cur++;
		}
		cout << "P 9" << endl;
	}
	return 0;
}

